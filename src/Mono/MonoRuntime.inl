#include "Mono/MonoRuntime.hpp"

namespace monoscript
{
/**
	@brief Add a native callback to the Mono Runtime (C# to C++)
	@tparam T The type signature of the method
	@param inScopedName The name of the method, including the scope
	@param inMethod A pointer to the method
*/
template <typename T>
void MonoRuntime::addCallback(const std::string& inScopedName, const T inMethod)
{
	mono_add_internal_call(inScopedName.data(), (const void*)inMethod);
}
}