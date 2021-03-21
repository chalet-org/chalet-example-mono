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

	/**
		@brief Initialize The Mono Runtime
		@return bool true if it was initialized, false otherwise
	 */
	bool initialize();

	template <typename T>
	void addCallback(const std::string& inScopedName, const T inMethod);

	/**
		@brief Open the domain assembly for a Mono / C# binary
		@param inBinary The path to the executable
		@return bool True if it was opened successfully. False if the domain is either already open, or the file was not found
	 */
	bool openDomainAssembly(const std::string& inBinary);

	/**
		@brief Call a non-standard static Main function that takes no paramaeters and returns an int, from a dynamic library for example
		@param inClass The name of the class
		@param inMethodName The name of the static method
		@return int The result of the method
	 */
	int callNonStandardMain(const std::string& inClass, const std::string& inMethodName);

	/**
		@brief Call a non-standard static Main function that takes no paramaeters and returns an int, from a dynamic library for example
		@param inNamespace The namespace of the class / method
		@param inClass The name of the class
		@param inMethodName The name of the static method
		@return int The result of the method
	 */
	int callNonStandardMain(const std::string& inNamespace, const std::string& inClass, const std::string& inMethodName);

	/**
		@brief Run an executable with the default Main entry point build with Mono / C#
		@param inBinary The path to the executable
		@return int The program result
	 */
	int runMain(const std::string& inBinary);

private:
	std::string m_domainName;

	MonoDomain* m_domain = nullptr;
	MonoAssembly* m_assembly = nullptr;
	MonoImage* m_assemblyImage = nullptr;

	bool m_initialized = false;
};
}

#include "Mono/MonoRuntime.inl"

#endif // MONOSCRIPT_MONO_RUNTIME_HPP
