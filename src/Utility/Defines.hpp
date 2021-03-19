#ifndef MONOSCRIPT_DEFINES_HPP
#define MONOSCRIPT_DEFINES_HPP

#if defined(_DEBUG) || defined(DEBUG)
	#ifndef MONOSCRIPT_DEBUG
		#define MONOSCRIPT_DEBUG
	#endif
#endif

#if defined(__APPLE__)
	#ifndef MONOSCRIPT_MACOS
		#define MONOSCRIPT_MACOS
	#endif
#elif defined(__linux__)
	#ifndef MONOSCRIPT_LINUX
		#define MONOSCRIPT_LINUX
	#endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#ifndef MONOSCRIPT_WIN32
		#define MONOSCRIPT_WIN32
	#endif
#else
static_assert(false, "Unknown platform");
#endif

#endif // MONOSCRIPT_DEFINES_HPP