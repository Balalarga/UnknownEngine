#pragma once

#include <fmt/core.h>
#include <chrono>


class Log
{
public:
	Log() = delete;
	Log(const Log&) = delete;

	template<class... Args>
	static void Print(const std::string& verbosity, const std::string& message, Args&&... args)
	{
		using namespace std::chrono;
		fmt::print(PrintTemplate,
			duration_cast<milliseconds>(system_clock::now() - AppStartTime).count() / 1000.f,
			verbosity,
			fmt::format(message, args...));
	}
	
	template<class... Args>
	static void Info(const std::string& message, Args&&... args)
	{
		Print("Info ", message, args...);
	}
	
	template<class... Args>
	static void Debug(const std::string& message, Args&&... args)
	{
		Print("Debug", message, args...);
	}
	
	template<class... Args>
	static void Error(const std::string& message, Args&&... args)
	{
		Print("Error", message, args...);
	}

	static const std::string& GetPrintTemplate() { return PrintTemplate; }
	static void SetPrintTemplate(const std::string& newTemplate) { PrintTemplate = newTemplate; }

	
private:
	static std::chrono::time_point<std::chrono::system_clock> AppStartTime;
	static std::string PrintTemplate;
};
