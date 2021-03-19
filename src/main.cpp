#include "Mono/MonoRuntime.hpp"

#include "Callbacks/TestCallback.hpp"

int main(/*const int argc, const char* const argv[]*/)
{
	const std::string file = "cs-test.out";
	std::string cmd = "mcs -out:" + file + " src_cs/Test.cs";
	std::system(cmd.data());

	const std::string domain = "monoscript";
	monoscript::MonoRuntime runtime(domain);
	runtime.initialize();
	runtime.addCallback("MonoEmbed::gimme", MonoEmbed::gimme);

	int result = runtime.run(file);

	return result;
}
