#include "Log.h"


std::chrono::time_point<std::chrono::system_clock> Log::AppStartTime = std::chrono::system_clock::now();
std::string Log::PrintTemplate = "[{:.3f} s] [{}]\t{}\n";