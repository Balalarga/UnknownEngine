#pragma once

#include "Log.h"

#define CheckReturn(contition, returnValue) \
	if (!contition) return returnValue;

#define CheckMsg(condition, msg, ...) \
if (!condition) Log::Error(msg, __VA_ARGS__)

#define CheckMsgReturn(condition, msg, returnValue) \
if (!condition) { Log::Error(msg); return returnValue; }