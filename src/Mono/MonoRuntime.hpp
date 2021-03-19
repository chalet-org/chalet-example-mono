#ifndef MONOSCRIPT_MONO_RUNTIME_HPP
#define MONOSCRIPT_MONO_RUNTIME_HPP

#include "Libraries/Mono.hpp"

namespace monoscript
{
struct MonoRuntime
{
	MonoRuntime() = delete;
	explicit MonoRuntime(const std::string& inDomainName);
	MONOSCRIPT_DEFAULT_COPY_MOVE(MonoRuntime);
	~MonoRuntime();

	void initialize();

	template <typename T>
	void addCallback(const std::string& inScopedName, const T inMethod);

	int run(const std::string& inEntryPoint);

private:
	std::string m_domainName;

	MonoDomain* m_domain = nullptr;

	bool m_initialized = false;
};
}

#include "Mono/MonoRuntime.inl"

#endif // MONOSCRIPT_MONO_RUNTIME_HPP
