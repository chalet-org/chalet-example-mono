#ifndef MONOSCRIPT_TEST_CALLBACK_HPP
#define MONOSCRIPT_TEST_CALLBACK_HPP

#include "Libraries/Mono.hpp"

namespace MonoEmbed
{
static MonoString* gimme()
{
	return mono_string_new(mono_domain_get(), "This is some C++ called from C#!");
}
}
#endif // MONOSCRIPT_TEST_CALLBACK_HPP
