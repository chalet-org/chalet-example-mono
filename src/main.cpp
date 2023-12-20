#include "Mono/MonoRuntime.hpp"

#include "Callbacks/TestCallback.hpp"

std::string getCsFilePath(const std::string exePath)
{
	auto end = exePath.find_last_of('/');
	auto path = end != std::string::npos ? exePath.substr(0, end) : "";
	path += '/';
	path += "cs-test.dll";
	return path;
}

int main(const int argc, const char* const argv[])
{
	auto csFile = getCsFilePath(std::string(argv[0]));
	if (csFile.empty())
	{
		std::cerr << "Error resolving cs dll" << std::endl;
		return 1;
	}

	const std::string domain = "monoscript";
	monoscript::MonoRuntime runtime(domain);
	if (!runtime.initialize())
	{
		std::cerr << "The Mono Runtime couldn't initialize." << std::endl;
		return 1;
	}

	runtime.addCallback("MonoEmbed::gimme", MonoEmbed::gimme);

	if (!runtime.openDomainAssembly(csFile))
	{
		std::cerr << "The Mono domain assembly for " << csFile << " couldn't be opened." << std::endl;
		return 1;
	}

	int result = runtime.callNonStandardMain("MonoEmbed", "Main()");

	return result;
}
