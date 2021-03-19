#include "Mono/MonoRuntime.hpp"

namespace monoscript
{
/*****************************************************************************/
MonoRuntime::MonoRuntime(const std::string& inDomainName) :
	m_domainName(inDomainName)
{
	m_domain = mono_jit_init(m_domainName.c_str());

	// Probably safer to explicitly define a framework version
	// .NET v4.7.x = C# v7.0,
	// m_domain = mono_jit_init_version(m_domainName.c_str(), "v4.0.30319");
}

/*****************************************************************************/
MonoRuntime::~MonoRuntime()
{
	mono_jit_cleanup(m_domain);
	m_domain = nullptr;
}
}
