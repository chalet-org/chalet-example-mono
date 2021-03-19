#include "Mono/MonoRuntime.hpp"

namespace monoscript
{
namespace
{
static int malloc_count = 0;

static void* custom_malloc(size_t bytes)
{
	++malloc_count;
	return ::malloc(bytes);
}
}
/*****************************************************************************/
MonoRuntime::MonoRuntime(const std::string& inDomainName) :
	m_domainName(inDomainName)
{
}

/*****************************************************************************/
MonoRuntime::~MonoRuntime()
{
	mono_jit_cleanup(m_domain);
	m_domain = nullptr;

	LOG("custom malloc calls = ", malloc_count);
}

/*****************************************************************************/
void MonoRuntime::initialize()
{
	if (m_initialized)
	{
		std::cerr << "MonoRuntime::initialize() called twice" << std::endl;
		std::exit(2);
	}

	MonoAllocatorVTable mem_vtable = { MONO_ALLOCATOR_VTABLE_VERSION, custom_malloc, NULL, NULL, NULL };
	// MonoAllocatorVTable mem_vtable;
	// mem_vtable.version = MONO_ALLOCATOR_VTABLE_VERSION;
	// mem_vtable.malloc = custom_malloc;
	// mem_vtable.realloc = NULL;
	// mem_vtable.free = NULL;
	// mem_vtable.calloc = NULL;

	mono_set_allocator_vtable(&mem_vtable);

	mono_config_parse(NULL);

	m_domain = mono_jit_init(m_domainName.data());

	// Probably safer to explicitly define a framework version
	// .NET v4.7.x = C# v7.0,
	// m_domain = mono_jit_init_version(m_domainName.c_str(), "v4.0.30319");

	m_initialized = true;
}

/*****************************************************************************/
int MonoRuntime::run(const std::string& inEntryPoint)
{
	m_assembly = mono_domain_assembly_open(m_domain, inEntryPoint.data());
	if (!m_assembly)
	{
		std::cerr << "Big ol' error" << std::endl;
		return 2;
	}

	mono_jit_exec(m_domain, m_assembly, 0, nullptr);

	int ret = mono_environment_exitcode_get();
	return ret;
}
}
