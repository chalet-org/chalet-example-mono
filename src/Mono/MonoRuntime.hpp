#ifndef MONOSCRIPT_MONO_RUNTIME_HPP
#define MONOSCRIPT_MONO_RUNTIME_HPP

#include "Libraries/Mono.hpp"

namespace monoscript
{
struct MonoRuntime
{
	MonoRuntime() = delete;
	explicit MonoRuntime(const std::string& inDomainName);
	~MonoRuntime();

private:
	std::string m_domainName;

	MonoDomain* m_domain = nullptr;
};
}

#endif // MONOSCRIPT_MONO_RUNTIME_HPP
