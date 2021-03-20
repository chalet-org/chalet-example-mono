#include "Mono/MonoRuntime.hpp"

#include "Callbacks/TestCallback.hpp"

int main(/*const int argc, const char* const argv[]*/)
{

#if defined(MONOSCRIPT_DEBUG)
	const std::string file = "cs-test-d.dll";
	// #if defined(MONOSCRIPT_WIN32)
	// int buildResult = std::system("msbuild.exe");
	// #else
	// int buildResult = std::system("msbuild");
	// #endif
	// if (buildResult != EXIT_SUCCESS)
	// {
	// 	std::cerr << "Build failed. See output above." << std::endl;
	// 	return buildResult;
	// }
#else
	const std::string file = "cs-test.dll";
#endif

	const std::string domain = "monoscript";
	monoscript::MonoRuntime runtime(domain);
	runtime.initialize();
	runtime.addCallback("MonoEmbed::gimme", MonoEmbed::gimme);

	int result = runtime.run(file);

	return result;
}
