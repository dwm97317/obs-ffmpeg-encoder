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

#pragma once
#include "utility.hpp"

#define S_STATE_DEFAULT "State.Default"
#define S_STATE_DISABLED "State.Disabled"
#define S_STATE_ENABLED "State.Enabled"
#define S_STATE_AUTOMATIC "State.Automatic"
#define S_STATE_MANUAL "State.Manual"

#define S_RATECONTROL "RateControl"
#define S_RATECONTROL_MODE "RateControl.Mode"
#define S_RATECONTROL_MODE_(x) "RateControl.Mode." D_VSTR(x)
#define S_RATECONTROL_BITRATE_TARGET "RateControl.Bitrate.Target"
#define S_RATECONTROL_BITRATE_MINIMUM "RateControl.Bitrate.Minimum"
#define S_RATECONTROL_BITRATE_MAXIMUM "RateControl.Bitrate.Maximum"
#define S_RATECONTROL_BUFFERSIZE "RateControl.BufferSize"
#define S_RATECONTROL_QUALITY_TARGET "RateControl.Quality.Target"
#define S_RATECONTROL_QUALITY_MINIMUM "RateControl.Quality.Minimum"
#define S_RATECONTROL_QUALITY_MAXIMUM "RateControl.Quality.Maximum"
#define S_RATECONTROL_QP_I "RateControl.QP.I"
#define S_RATECONTROL_QP_P "RateControl.QP.P"
#define S_RATECONTROL_QP_B "RateControl.QP.B"
#define S_RATECONTROL_QP_I_INITIAL "RateControl.QP.I.Initial"
#define S_RATECONTROL_QP_P_INITIAL "RateControl.QP.P.Initial"
#define S_RATECONTROL_QP_B_INITIAL "RateControl.QP.B.Initial"

#define S_KEYFRAMES "KeyFrames"
#define S_KEYFRAMES_INTERVALTYPE "KeyFrames.IntervalType"
#define S_KEYFRAMES_INTERVALTYPE_(x) "KeyFrames.IntervalType." D_VSTR(x)
#define S_KEYFRAMES_INTERVAL "KeyFrames.Interval"
#define S_KEYFRAMES_INTERVAL_SECONDS "KeyFrames.Interval.Seconds"
#define S_KEYFRAMES_INTERVAL_FRAMES "KeyFrames.Interval.Frames"
