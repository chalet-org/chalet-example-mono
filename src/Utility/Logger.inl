#include "Utility/Logger.hpp"

namespace monoscript
{
namespace priv
{
/*****************************************************************************/
// This voodoo allows you to write: LOG("first", second, third)
//
template <typename... Args>
Logger::Logger(const char* const inFile, const std::string& inFunction, Args&&... args) :
	Logger(inFile, inFunction)
{
	stream.precision(std::numeric_limits<double>::digits);
	((stream << std::forward<Args>(args) << ' '), ...);
}
}
}