#include "Mono/MonoRuntime.hpp"

int main(/*const int argc, const char* const argv[]*/)
{
	std::string domain = "monoscript";
	monoscript::MonoRuntime runtime(domain);

	LOG("Hello world?");

	return 0;
}
