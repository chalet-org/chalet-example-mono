#ifndef MONOSCRIPT_LOGGER_HPP
#define MONOSCRIPT_LOGGER_HPP

// #ifdef _DEBUG
#define LOG(...) monoscript::priv::Logger(__FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_CLASS_METHOD() monoscript::priv::Logger(priv::Logger::classMethod(__FILE__, __FUNCTION__))
#define LOG_LEVEL_NORMAL() monoscript::priv::logNormal()
#define LOG_LEVEL_DETAILED() monoscript::priv::logDetailed()
// #else
// 	#define LOG(...)
// 	#define LOG_CLASS_METHOD()
// 	#define LOG_LEVEL_NORMAL()
// 	#define LOG_LEVEL_DETAILED()
// #endif

// #ifdef _DEBUG

namespace monoscript
{
namespace priv
{
void logNormal();
void logDetailed();

struct Logger
{
	explicit Logger(const std::string& inString);
	explicit Logger(const char* const inFile, const std::string& inFunction);
	~Logger();

	template <typename... Args>
	explicit Logger(const char* const inFile, const std::string& inFunction, Args&&... args);

	static std::string classMethod(const std::string& inFile, const std::string& inFunction);

private:
	std::stringstream stream;
	int uncaught = std::uncaught_exceptions();
};
}
}

#include "Utility/Logger.inl"

// #endif

#endif // MONOSCRIPT_LOGGER_HPP