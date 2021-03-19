#include "Mono/MonoRuntime.hpp"

#include "Callbacks/TestCallback.hpp"

int main(/*const int argc, const char* const argv[]*/)
{
	const std::string file = "cs-test.dll";

#if defined(MONOSCRIPT_DEBUG)
	int buildResult = std::system("msbuild");
	if (buildResult != EXIT_SUCCESS)
	{
		std::cerr << "Build failed. See output above." << std::endl;
		return buildResult;
	}
#endif

	const std::string domain = "monoscript";
	monoscript::MonoRuntime runtime(domain);
	runtime.initialize();
	runtime.addCallback("MonoEmbed::gimme", MonoEmbed::gimme);

	int result = runtime.run(file);

	return result;
}
