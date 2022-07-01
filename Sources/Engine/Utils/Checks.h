#pragma once

#include "Log.h"

#define CheckReturn(condition, returnValue) \
	if (!(condition)) { Log::Error("{}({}): {} = false", __FILE__, __LINE__, #condition); return returnValue; }

#define CheckMsg(condition, msg, ...) \
if (!(condition)) Log::Error(msg, __VA_ARGS__);

#define CheckMsgReturn(condition, msg, returnValue) \
if (!(condition)) { Log::Error(msg); return returnValue; }

#define CheckReturnFunc(condition, func, returnValue) \
if (!(condition)) { func; return returnValue; }