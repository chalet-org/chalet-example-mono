#include "Mono/MonoRuntime.hpp"

#include <array>

namespace monoscript
{
namespace
{
static std::size_t malloc_count = 0;
static std::size_t calloc_count = 0;
static std::size_t realloc_count = 0;
static std::size_t free_count = 0;

static void* custom_malloc(std::size_t bytes)
{
	++malloc_count;
	return ::malloc(bytes);
}
static void* custom_calloc(std::size_t count, std::size_t bytes)
{
	++calloc_count;
	return ::calloc(count, bytes);
}
static void* custom_realloc(void* ptr, std::size_t bytes)
{
	++realloc_count;
	return ::realloc(ptr, bytes);
}
static void custom_free(void* mem)
{
	++free_count;
	return ::free(mem);
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
	// Note: Not sure yet if deleters are needed for these.
	//   Bad things seemed to happen with close/free related mono_ functions
	m_assemblyImage = nullptr;
	m_assembly = nullptr;

	// Do the main cleanup here
	if (m_domain != nullptr)
	{
		mono_jit_cleanup(m_domain);
		m_domain = nullptr;
	}

	LOG("----------------------------------------");
	LOG("native malloc calls = ", malloc_count);
	LOG("native calloc calls = ", calloc_count);
	LOG("native realloc calls = ", realloc_count);
	LOG("native free calls = ", free_count);
	LOG("----------------------------------------");
}

/*****************************************************************************/
bool MonoRuntime::initialize()
{
	if (m_initialized)
		return false;

	MonoAllocatorVTable mem_vtable;
	mem_vtable.version = MONO_ALLOCATOR_VTABLE_VERSION;
	mem_vtable.malloc = custom_malloc;
	mem_vtable.calloc = custom_calloc;
	mem_vtable.realloc = custom_realloc;
	mem_vtable.free = custom_free;

	mono_set_allocator_vtable(&mem_vtable);

	mono_config_parse(NULL);

	m_domain = mono_jit_init(m_domainName.data());

	// Probably safer to explicitly define a framework version
	// .NET v4.7.x = C# v7.0,
	// m_domain = mono_jit_init_version(m_domainName.c_str(), "v4.0.30319");

	m_initialized = true;

	return true;
}

/*****************************************************************************/
bool MonoRuntime::openDomainAssembly(const std::string& inBinary)
{
	if (m_assembly != nullptr)
		return false;

	LOG("----------------------------------------");
	LOG("");

	m_assembly = mono_domain_assembly_open(m_domain, inBinary.data());
	if (!m_assembly)
		return false;

	m_assemblyImage = mono_assembly_get_image(m_assembly);

	return true;
}

/*****************************************************************************/
int MonoRuntime::callNonStandardMain(const std::string& inClass, const std::string& inMethodName)
{
	return callNonStandardMain("", inClass, inMethodName);
}

/*****************************************************************************/
int MonoRuntime::callNonStandardMain(const std::string& inNamespace, const std::string& inClass, const std::string& inMethodName)
{
	int ret = 0;

	// TODO: Caching of methods & classes

	MonoClass* entryClass = mono_class_from_name(m_assemblyImage, inNamespace.data(), inClass.data());

	std::string methodName;
	if (inClass.empty())
		methodName = inMethodName;
	else
		methodName = inClass + ":" + inMethodName;

	MonoMethodDesc* mainDesc = mono_method_desc_new(methodName.data(), !inNamespace.empty());
	MonoMethod* mainMethod = mono_method_desc_search_in_class(mainDesc, entryClass);

	// static method, so no need to pass an object
	MonoObject* result = mono_runtime_invoke(mainMethod, NULL, NULL, NULL);
	ret = *(int*)mono_object_unbox(result);

	mono_free_method(mainMethod);
	mono_method_desc_free(mainDesc);

	LOG("");
	LOG("----------------------------------------");
	LOG(inMethodName, "exited with code:", ret);

	return ret;
}

/*****************************************************************************/
int MonoRuntime::runMain(const std::string& inEntryPoint)
{
	std::array<char*, 1> args{ const_cast<char*>(inEntryPoint.data()) };

	mono_jit_exec(m_domain, m_assembly, static_cast<int>(args.size()), args.data());
	int ret = mono_environment_exitcode_get();

	LOG("");
	LOG("----------------------------------------");
	LOG(inEntryPoint, "exited with code:", ret);

	return ret;
}
}
