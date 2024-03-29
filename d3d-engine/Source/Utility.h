#pragma once 

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "pch.h"

namespace Utility
{
	inline void Print(const char* msg) { printf(msg); }
	inline void Print(const wchar_t* msg) { wprintf(msg); }

	inline void Printf(const char* format, ...) {
		char buffer[256];
		va_list ap;
		va_start(ap, format);
		vsprintf_s(buffer, 256, format, ap);
		Print(buffer);
	}

	inline void Printf(const wchar_t* format, ...) {
		wchar_t buffer[256];
		va_list ap;
		va_start(ap, format);
		vswprintf(buffer, 256, format, ap);
		Print(buffer);
	}

#ifndef RELEASE
	inline void PrintSubMessage(const char* format, ...) {
		Print("--> ");
		char buffer[256];
		va_list ap;
		va_start(ap, format);
		vsprintf_s(buffer, 256, format, ap);
		Print(buffer);
		Print("\n");
	}
	inline void PrintSubMessage(const wchar_t* format, ...) {
		Print("--> ");
		wchar_t buffer[256];
		va_list ap;
		va_start(ap, format);
		vswprintf(buffer, 256, format, ap);
		Print(buffer);
		Print("\n");
	}
	inline void PrintSubMessage(void) {}
#endif

}

#ifndef INLINE
#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#define INLINE __forceinline
#else
#define INLINE __inline
#endif
#else
#ifdef __cplusplus
#define INLINE inline
#else
#define INLINE
#endif
#endif
#endif

#ifdef ERROR
#undef ERROR
#endif
#ifdef ASSERT
#undef ASSERT
#endif
#ifdef HALT
#undef HALT
#endif
#define HALT( ... ) ERROR( __VA_ARGS__ ) __debugbreak();

#ifdef RELEASE

#define ASSERT( isTrue, ... ) (void)(isTrue)
#define WARN_ONCE_IF( isTrue, ... ) (void)(isTrue)
#define WARN_ONCE_IF_NOT( isTrue, ... ) (void)(isTrue)
#define ERROR( msg, ... )
#define DEBUGPRINT( msg, ... ) do {} while(0)
#define ASSERT_SUCCEEDED( hr, ... ) (void)(hr)

#else
// !RELEASE

#define STRINGIFY(x) #x
#define STRINGIFY_BUILTIN(x) STRINGIFY(x)
#define ASSERT( isFalse, ... ) \
		if (!(bool)(isFalse)) { \
			Utility::Print("\nAssertion failed in " STRINGIFY_BUILTIN(__FILE__) " @ " STRINGIFY_BUILTIN(__LINE__) "\n"); \
			Utility::PrintSubMessage("\'" #isFalse "\' is false"); \
			Utility::PrintSubMessage(__VA_ARGS__); \
			Utility::Print("\n"); \
			__debugbreak(); \
						}

#define ASSERT_SUCCEEDED( hr, ... ) \
		if (FAILED(hr)) { \
			Utility::Print("\nHRESULT failed in " STRINGIFY_BUILTIN(__FILE__) " @ " STRINGIFY_BUILTIN(__LINE__) "\n"); \
			Utility::PrintSubMessage("hr = 0x%08X", hr); \
			Utility::PrintSubMessage(__VA_ARGS__); \
			Utility::Print("\n"); \
			__debugbreak(); \
						}


#define WARN_ONCE_IF( isTrue, ... ) \
		{ \
		static bool s_TriggeredWarning = false; \
		if ((bool)(isTrue) && !s_TriggeredWarning) { \
			s_TriggeredWarning = true; \
			Utility::Print("\nWarning issued in " STRINGIFY_BUILTIN(__FILE__) " @ " STRINGIFY_BUILTIN(__LINE__) "\n"); \
			Utility::PrintSubMessage("\'" #isTrue "\' is true"); \
			Utility::PrintSubMessage(__VA_ARGS__); \
			Utility::Print("\n"); \
						} \
		}

#define WARN_ONCE_IF_NOT( isTrue, ... ) WARN_ONCE_IF(!(isTrue), __VA_ARGS__)

#define ERROR( ... ) \
		Utility::Print("\nError reported in " STRINGIFY_BUILTIN(__FILE__) " @ " STRINGIFY_BUILTIN(__LINE__) "\n"); \
		Utility::PrintSubMessage(__VA_ARGS__); \
		Utility::Print("\n");

#define DEBUGPRINT( msg, ... ) \
	Utility::Printf( msg "\n", ##__VA_ARGS__ );


#define BreakIfFailed( hr ) if (FAILED(hr)) __debugbreak()

std::wstring MakeWStr(const std::string& str);

#endif
