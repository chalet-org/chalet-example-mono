#include "Mono/MonoRuntime.hpp"

namespace monoscript
{
template <typename T>
void MonoRuntime::addCallback(const std::string& inScopedName, const T inMethod)
{
	mono_add_internal_call(inScopedName.data(), (const void*)inMethod);
}
}