// FFMPEG Video Encoder Integration for OBS Studio
// Copyright (c) 2019 Michael Fabian Dirks <info@xaymar.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "plugin.hpp"
#include <memory>
#include "encoders/generic.hpp"
#include "encoders/prores_aw.hpp"
#include "ui/debug_handler.hpp"
#include "ui/handler.hpp"
#include "utility.hpp"

extern "C" {
#include <obs-module.h>
#include <obs.h>
#pragma warning(push)
#pragma warning(disable : 4244)
#include <libavcodec/avcodec.h>
#pragma warning(pop)
}

// Initializers and finalizers.
std::list<std::function<void()>> obsffmpeg::initializers;

std::list<std::function<void()>> obsffmpeg::finalizers;

// Codec to Handler mapping.
static std::map<std::string, std::shared_ptr<obsffmpeg::ui::handler>> codec_to_handler_map;
static std::shared_ptr<obsffmpeg::ui::handler> debug_handler = std::make_shared<obsffmpeg::ui::debug_handler>();

void obsffmpeg::register_codec_handler(std::string const codec, std::shared_ptr<obsffmpeg::ui::handler> const handler)
{
	codec_to_handler_map.emplace(codec, handler);
}

std::shared_ptr<obsffmpeg::ui::handler> obsffmpeg::find_codec_handler(std::string const codec)
{
	auto found = codec_to_handler_map.find(codec);
	if (found == codec_to_handler_map.end())
		return debug_handler;
	return found->second;
}

bool obsffmpeg::has_codec_handler(std::string const codec)
{
	auto found = codec_to_handler_map.find(codec);
	return (found != codec_to_handler_map.end());
}

static std::map<AVCodec*, std::shared_ptr<encoder::generic_factory>> generic_factories;

MODULE_EXPORT bool obs_module_load(void)
try {
	// Initialize avcodec.
	avcodec_register_all();

	// Run all initializers.
	for (auto const func : obsffmpeg::initializers) {
		func();
	}

	// Register all codecs.
	AVCodec* cdc = nullptr;
	while ((cdc = av_codec_next(cdc)) != nullptr) {
		if (!av_codec_is_encoder(cdc))
			continue;

		if ((cdc->type == AVMediaType::AVMEDIA_TYPE_AUDIO) || (cdc->type == AVMediaType::AVMEDIA_TYPE_VIDEO)) {
			auto ptr = std::make_shared<encoder::generic_factory>(cdc);
			ptr->register_encoder();
			generic_factories.emplace(cdc, ptr);
		}
	}

	obsffmpeg::encoder::prores_aw::initialize();
	return true;
} catch (std::exception const& ex) {
	PLOG_ERROR("Exception during initalization: %s.", ex.what());
	return false;
} catch (...) {
	PLOG_ERROR("Unrecognized exception during initalization.");
	return false;
}

MODULE_EXPORT void obs_module_unload(void)
try {
	obsffmpeg::encoder::prores_aw::finalize();

	// Run all finalizers.
	for (auto const func : obsffmpeg::finalizers) {
		func();
	}
} catch (std::exception const& ex) {
	PLOG_ERROR("Exception during finalizing: %s.", ex.what());
} catch (...) {
	PLOG_ERROR("Unrecognized exception during finalizing.");
}
