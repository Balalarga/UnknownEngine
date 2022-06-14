#pragma once

#include <fmt/core.h>
#include <chrono>


struct Log
{
	Log() = delete;
	Log(const Log&) = delete;
	
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
	static void Error(const std:cd ..:string& message, Args&&... args)
	{
		Print("Error", message, args...);
	}

	template<class... Args>
	static void Print(const std::string& verbosity, const std::string& message, Args&&... args)
	{
		using namespace std::chrono;
		fmt::print(PrintTemplate,
			duration_cast<milliseconds>(system_clock::now() - AppStartTime).count() / 1000.f,
			verbosity,
			fmt::format(message, args...));
	}

#define ScopedLog(msg, ...) ScopedMessage ScopMsg##__LINE__(msg, ##__VA_ARGS__)
	template<class... Args>
	struct ScopedMessage
	{
		ScopedMessage(const std::string& message, Args&&... args):
			fullMessage(fmt::format(message, args...))
		{
			Print("ScopedStart", fullMessage);
		}
		ScopedMessage(ScopedMessage&&) = delete;
		ScopedMessage(const ScopedMessage&) = delete;
		ScopedMessage& operator=(ScopedMessage&&) = delete;
		ScopedMessage& operator=(const ScopedMessage&) = delete;
		
		~ScopedMessage()
		{
			Print("ScopedEnd", fullMessage);
		}
		
	private:
		const std::string fullMessage;
	};

	static const std::string& GetPrintTemplate() { return PrintTemplate; }
	/**
	 *  {0} - time from app start, 
	 *	{1} - verbosity, 
	 *	{2} - formatted message
	 */
	static void SetPrintTemplate(const std::string& newTemplate) { PrintTemplate = newTemplate; }

	
private:
	static std::chrono::time_point<std::chrono::system_clock> AppStartTime;
	static std::string PrintTemplate;
};
