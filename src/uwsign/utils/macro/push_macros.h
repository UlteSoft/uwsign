/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author MacroModel
 * @version 2.0.0
 * @date 2025-03-23
 * @copyright APL-2.0 License
 */

/// @brief The following are the macros used by uwsign.
/// @details Use `push_macro` to avoid side effects on existing macros. Please use `pop_macro` in conjunction.

// #pragma once

/// @brief This file defines those header files that can only be imported once in push_macro.h
#include "push_macros_include_header_pragma_once.h"

/// @brief std and windows.h macro

#pragma push_macro("erase")
#undef erase

#pragma push_macro("interface")
#undef interface

#pragma push_macro("max")
#undef max

#pragma push_macro("min")
#undef min

#pragma push_macro("move")
#undef move

#pragma push_macro("new")
#if __GNUC__ >= 16
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wpragmas"
# pragma GCC diagnostic ignored "-Wkeyword-macro"
# undef new
# pragma GCC diagnostic pop
#else
# undef new
#endif

#pragma push_macro("refresh")
#undef refresh

/// @brief        uwsign macros

/// @brief        __has_cpp_attribute
/// @details      __has_cpp_attribute is not provided by standard cpp, avoid using __has_cpp_attribute on unsupport compiler
#pragma push_macro("UWSIGN_HAS_CPP_ATTRIBUTE")
#undef UWSIGN_HAS_CPP_ATTRIBUTE
#ifdef __has_cpp_attribute
# define UWSIGN_HAS_CPP_ATTRIBUTE(...) __has_cpp_attribute(__VA_ARGS__)
#else
# define UWSIGN_HAS_CPP_ATTRIBUTE(...) 0
#endif

/// @brief        import func from dll
/// @details      on msvc: __declspec(dllimport)
///               on gcc, clang [[__gnu__::__dllimport__]]
#pragma push_macro("UWSIGN_DLLIMPORT")
#undef UWSIGN_DLLIMPORT
#if defined(_MSC_VER) && !defined(__clang__)
# define UWSIGN_DLLIMPORT __declspec(dllimport)
#elif UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__dllimport__) && !defined(__WINE__) && !defined(__arm64ec__)
# define UWSIGN_DLLIMPORT [[__gnu__::__dllimport__]]
#else
# define UWSIGN_DLLIMPORT
#endif

/// @brief        import function from dll under the premise of having a `_DLL` macro
/// @details      same as `UWSIGN_DLLIMPORT`
#pragma push_macro("UWSIGN_DLL_DLLIMPORT")
#undef UWSIGN_DLL_DLLIMPORT
#if defined(_DLL) && !defined(__WINE__)
# define UWSIGN_DLL_DLLIMPORT UWSIGN_DLLIMPORT
#else
# define UWSIGN_DLL_DLLIMPORT
#endif

/// @brief        stdcall
/// @details      On x86-32 targets, the stdcall attribute causes the compiler to assume
///               that the called function pops off the stack space used to pass arguments,
///               unless it takes a variable number of arguments.
/// @details      on msvc: __stdcall
///               on gcc, clang: __attribute__((__stdcall__))
#pragma push_macro("UWSIGN_STDCALL")
#undef UWSIGN_STDCALL
#if defined(_MSC_VER) && (!UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWSIGN_STDCALL __stdcall
#elif (UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWSIGN_STDCALL __attribute__((__stdcall__))
#else
# define UWSIGN_STDCALL
#endif

/// @brief        stdcall attribute, same as UWSIGN_STDCALL
/// @see          UWSIGN_STDCALL
#pragma push_macro("UWSIGN_WINSTDCALL")
#undef UWSIGN_WINSTDCALL
#if defined(_MSC_VER) && (!UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWSIGN_WINSTDCALL __stdcall
#elif (UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWSIGN_WINSTDCALL __attribute__((__stdcall__))
#else
# define UWSIGN_WINSTDCALL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWSIGN_WINSTDCALL
/// @note         Need to include <climit> (SIZE_MAX) and <cstdint> (UINT_LEAST32_MAX) before
#pragma push_macro("UWSIGN_WINSTDCALL_RENAME")
#undef UWSIGN_WINSTDCALL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWSIGN_WINSTDCALL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWSIGN_WINSTDCALL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWSIGN_WINSTDCALL_RENAME(name, count) __asm__(#name "@" #count)
#  else
#   define UWSIGN_WINSTDCALL_RENAME(name, count) __asm__("_" #name "@" #count)
#  endif
# else
#  define UWSIGN_WINSTDCALL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWSIGN_WINSTDCALL_RENAME(name, count)
#endif

/// @brief        cdecl
/// @details      On the x86-32 targets, the cdecl attribute causes the compiler to assume that the calling function pops
///               off the stack space used to pass arguments. This is useful to override the effects of the -mrtd switch.
/// @details      on msvc: __cdecl
///               on gcc, clang: __attribute__((__cdecl__))
#pragma push_macro("UWSIGN_WINCDECL")
#undef UWSIGN_WINCDECL
#if defined(_MSC_VER) && (!UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__cdecl__) && !defined(__WINE__))
# define UWSIGN_WINCDECL __cdecl
#elif (UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__cdecl__) && !defined(__WINE__))
# define UWSIGN_WINCDECL __attribute__((__cdecl__))
#else
# define UWSIGN_WINCDECL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWSIGN_WINCDECL
#pragma push_macro("UWSIGN_WINCDECL_RENAME")
#undef UWSIGN_WINCDECL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWSIGN_WINCDECL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWSIGN_WINCDECL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWSIGN_WINCDECL_RENAME(name, count) __asm__(#name)
#  else
#   define UWSIGN_WINCDECL_RENAME(name, count) __asm__("_" #name)
#  endif
# else
#  define UWSIGN_WINCDECL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWSIGN_WINCDECL_RENAME(name, count)
#endif

/// @brief        fastcall
/// @details      On x86-32 targets, the fastcall attribute causes the compiler to pass the first argument
///               (if of integral type) in the register ECX and the second argument (if of integral type)
///               in the register EDX. Subsequent and other typed arguments are passed on the stack.
///               The called function pops the arguments off the stack. If the number of arguments is variable
///               all arguments are pushed on the stack.
/// @details      on msvc: __fastcall
///               on gcc, clang: __attribute__((__fastcall__))
#pragma push_macro("UWSIGN_WINFASTCALL")
#undef UWSIGN_WINFASTCALL
#if defined(_MSC_VER) && (!UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__fastcall__) && !defined(__WINE__))
# define UWSIGN_WINFASTCALL __fastcall
#elif (UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__fastcall__) && !defined(__WINE__))
# define UWSIGN_WINFASTCALL __attribute__((__fastcall__))
#else
# define UWSIGN_WINFASTCALL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWSIGN_WINFASTCALL
#pragma push_macro("UWSIGN_WINFASTCALL_RENAME")
#undef UWSIGN_WINFASTCALL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWSIGN_WINFASTCALL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWSIGN_WINFASTCALL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWSIGN_WINFASTCALL_RENAME(name, count) __asm__("@" #name "@" #count)
#  else
#   define UWSIGN_WINFASTCALL_RENAME(name, count) __asm__("_@" #name "@" #count)
#  endif
# else
#  define UWSIGN_WINFASTCALL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWSIGN_WINFASTCALL_RENAME(name, count)
#endif

/// @brief        [[gnu::const]] is an attribute that can be applied to functions to indicate that they are pure in a specific way.
/// @details      on gcc, clang: [[__gnu__::__const__]]
#pragma push_macro("UWSIGN_GNU_CONST")
#undef UWSIGN_GNU_CONST
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__const__)
# define UWSIGN_GNU_CONST [[__gnu__::__const__]]
#else
# define UWSIGN_GNU_CONST
#endif

/// @brief        [[gnu::pure]] is an attribute that can be applied to functions that have no observable effects on the state of the program other than to
///               return a value may lend themselves to optimizations such as common subexpression elimination.
/// @details      on gcc, clang: [[__gnu__::__pure__]]
#pragma push_macro("UWSIGN_GNU_PURE")
#undef UWSIGN_GNU_PURE
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__pure__)
# define UWSIGN_GNU_PURE [[__gnu__::__pure__]]
#else
# define UWSIGN_GNU_PURE
#endif

/// @brief        forceinline
/// @details      After C++17, the `inline` keyword no longer indicates forced inlining;
///               instead, it serves to prevent ODR violations. Forced inlining should be achieved using the forceinline attribute.
/// @details      on gcc, clang: [[__gnu__::__always_inline__]]
///               on msvc: [[msvc::forceinline]]
#pragma push_macro("UWSIGN_ALWAYS_INLINE")
#undef UWSIGN_ALWAYS_INLINE
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__always_inline__)
# define UWSIGN_ALWAYS_INLINE [[__gnu__::__always_inline__]]
#elif UWSIGN_HAS_CPP_ATTRIBUTE(msvc::forceinline)
# define UWSIGN_ALWAYS_INLINE [[msvc::forceinline]]
#else
# define UWSIGN_ALWAYS_INLINE
#endif

/// @brief        Marking a function with [[gnu::artificial]] hints to debuggers that it is not
///               a user-defined function, reducing unnecessary debug info.
/// @details      on gcc, clang: [[__gnu__::__artificial__]]
#pragma push_macro("UWSIGN_GNU_ARTIFICIAL")
#undef UWSIGN_GNU_ARTIFICIAL
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__artificial__)
# define UWSIGN_GNU_ARTIFICIAL [[__gnu__::__artificial__]]
#else
# define UWSIGN_GNU_ARTIFICIAL
#endif

/// @brief        UWSIGN_ALWAYS_INLINE + UWSIGN_GNU_ARTIFICIAL
/// @see          UWSIGN_ALWAYS_INLINE
/// @see          UWSIGN_GNU_ARTIFICIAL
#pragma push_macro("UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL")
#undef UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL
#define UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL UWSIGN_ALWAYS_INLINE UWSIGN_GNU_ARTIFICIAL

/// @brief        UWSIGN_ALWAYS_INLINE + UWSIGN_GNU_ARTIFICIAL + [[nodiscard]] + UWSIGN_GNU_CONST
/// @see          UWSIGN_ALWAYS_INLINE
/// @see          UWSIGN_GNU_ARTIFICIAL
/// @see          C++ attribute: [[nodiscard]]
/// @see          UWSIGN_GNU_CONST
#pragma push_macro("UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST")
#undef UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST
#define UWSIGN_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST UWSIGN_ALWAYS_INLINE [[nodiscard]] UWSIGN_GNU_ARTIFICIAL UWSIGN_GNU_CONST

/// @brief        This part refers to memory allocation functions, which are responsible for managing dynamic memory
///               (e.g., allocating and freeing memory).
/// @details      on gcc, clang: [[__gnu__::__malloc__]]
#pragma push_macro("UWSIGN_GNU_MALLOC")
#undef UWSIGN_GNU_MALLOC
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__malloc__)
# define UWSIGN_GNU_MALLOC [[__gnu__::__malloc__]]
#else
# define UWSIGN_GNU_MALLOC
#endif

/// @brief        Telling the compiler (and other developers) that the function will never return a null pointer
/// @details      on gcc, clang: [[__gnu__::__returns_nonnull__]]
#pragma push_macro("UWSIGN_GNU_RETURNS_NONNULL")
#undef UWSIGN_GNU_RETURNS_NONNULL
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__returns_nonnull__)
# define UWSIGN_GNU_RETURNS_NONNULL [[__gnu__::__returns_nonnull__]]
#else
# define UWSIGN_GNU_RETURNS_NONNULL
#endif

/// @brief        __has_builtin
/// @details      __has_builtin is not provided by standard cpp, avoid using __has_builtin on unsupport compiler
#pragma push_macro("UWSIGN_HAS_BUILTIN")
#undef UWSIGN_HAS_BUILTIN
#ifdef __has_builtin
# define UWSIGN_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
# define UWSIGN_HAS_BUILTIN(...) 0
#endif

/// @brief        Whether fast_io::native_thread is available on the current target.
/// @details      This is a define-only macro. Use `#ifdef UWSIGN_UTILS_HAS_FAST_IO_NATIVE_THREAD`.
#pragma push_macro("UWSIGN_UTILS_HAS_FAST_IO_NATIVE_THREAD")
#undef UWSIGN_UTILS_HAS_FAST_IO_NATIVE_THREAD
#if ((defined(_WIN32) && !defined(__WINE__)) && !defined(__CYGWIN__)) || (defined(__wasi__) && defined(__wasi_thread__)) ||                                    \
    (!defined(__SINGLE_THREAD__) && !defined(__NEWLIB__) && !defined(__MSDOS__) && !defined(__DJGPP__) && __has_include(<pthread.h>))
# define UWSIGN_UTILS_HAS_FAST_IO_NATIVE_THREAD
#endif

/// @brief        assert
/// @details      Avoid using C++26 contracts. Different modules including different handle_contract_violation
///               implementations may result in multiple handling approaches. If a module without handle_contract_violation
///               is included, std::terminate or std::abort will be used instead of the direct trap behavior we desire.
/// @details      on gcc, clang: __builtin_trap()
///               on msvc: abort()
#pragma push_macro("UWSIGN_ASSERT")
#undef UWSIGN_ASSERT
#if defined(_DEBUG) || defined(DEBUG)
# if (defined(_MSC_VER) && !defined(__clang__)) || !UWSIGN_HAS_BUILTIN(__builtin_trap)
#  define UWSIGN_ASSERT(x)                                                                                                                                       \
      if(!__builtin_is_constant_evaluated() && !(x)) ::std::abort()
# else
#  define UWSIGN_ASSERT(x)                                                                                                                                       \
      if(!__builtin_is_constant_evaluated() && !(x)) __builtin_trap()
# endif
#else
# define UWSIGN_ASSERT(x) ((void)0)
#endif

/// @brief        Specify that a type is replaceable if it meets certain conditions.
/// @see          replaceable_if_eligible
#pragma push_macro("UWSIGN_REPLACEABLE_IF_ELIGIBLE")
#if defined(__cpp_trivial_relocatability)
# undef UWSIGN_REPLACEABLE_IF_ELIGIBLE
# if defined(__clang__)
#  define UWSIGN_REPLACEABLE_IF_ELIGIBLE                                                                                                                         \
      _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wc++26-extensions\"") replaceable_if_eligible _Pragma("clang diagnostic pop")
# else  // ^^^ defined(__clang__) / vvv !defined(__clang__)
#  define UWSIGN_REPLACEABLE_IF_ELIGIBLE replaceable_if_eligible
# endif  // ^^^ !defined(__clang__)
#else
# define UWSIGN_REPLACEABLE_IF_ELIGIBLE
#endif

/// @brief        Indicates that the function will throw a Herbception exception.
/// @details      C++ exceptions are the worst historical feature of c++, this program uses only one exception
///               type which is fast_io::error, and fully replaces herbception after it enters the proposal.
/// @see          https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0709r4.pdf
#pragma push_macro("UWSIGN_THROWS")
#undef UWSIGN_THROWS
#if defined(__cpp_herbception)
# define UWSIGN_THROWS throws
#else
# define UWSIGN_THROWS
#endif

/// @brief        Indicates that a function is unlikely to be called frequently.
/// @details      on gcc, clang: [[__gnu__::__cold__]]
#pragma push_macro("UWSIGN_GNU_COLD")
#undef UWSIGN_GNU_COLD
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__cold__)
# define UWSIGN_GNU_COLD [[__gnu__::__cold__]]
#else
# define UWSIGN_GNU_COLD
#endif

/// @brief        Indicates that a function is likely to be called frequently.
/// @details      on gcc, clang: [[__gnu__::__hot__]]
#pragma push_macro("UWSIGN_GNU_HOT")
#undef UWSIGN_GNU_HOT
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__hot__)
# define UWSIGN_GNU_HOT [[__gnu__::__hot__]]
#else
# define UWSIGN_GNU_HOT
#endif

/// @brief        MSVC may not support if consteval, so macros are used to select the appropriate version.
/// @details      on gcc, clang: consteval
///               on msvc: (__builtin_is_constant_evaluated())
#pragma push_macro("UWSIGN_IF_CONSTEVAL")
#undef UWSIGN_IF_CONSTEVAL
#if __cpp_if_consteval >= 202106L
# define UWSIGN_IF_CONSTEVAL consteval
#else
# if UWSIGN_HAS_BUILTIN(__builtin_is_constant_evaluated)
#  define UWSIGN_IF_CONSTEVAL (__builtin_is_constant_evaluated())
# else
#  define UWSIGN_IF_CONSTEVAL (::std::is_constant_evaluated())
# endif
#endif

/// @brief        MSVC may not support if consteval, so macros are used to select the appropriate version.
/// @details      on gcc, clang: !consteval
///               on msvc: (!__builtin_is_constant_evaluated())
#pragma push_macro("UWSIGN_IF_NOT_CONSTEVAL")
#undef UWSIGN_IF_NOT_CONSTEVAL
#if __cpp_if_consteval >= 202106L
# define UWSIGN_IF_NOT_CONSTEVAL !consteval
#else
# if UWSIGN_HAS_BUILTIN(__builtin_is_constant_evaluated)
#  define UWSIGN_IF_NOT_CONSTEVAL (!__builtin_is_constant_evaluated())
# else
#  define UWSIGN_IF_NOT_CONSTEVAL (!::std::is_constant_evaluated())
# endif
#endif

/// @brief        You can specify the may_alias type attribute for a type so that lvalues of
///               the type can alias objects of any type, similar to a char type.
/// @details      on gcc, clang: [[__gnu__::__may_alias__]]
///               on msvc: MSVC does not enable strict aliasing rules by default, so aliasing between pointers of different types is usually allowed.
#pragma push_macro("UWSIGN_GNU_MAY_ALIAS")
#undef UWSIGN_GNU_MAY_ALIAS
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__may_alias__)
# define UWSIGN_GNU_MAY_ALIAS [[__gnu__::__may_alias__]]
#else
# define UWSIGN_GNU_MAY_ALIAS
#endif

/// @details      Determine whether the operating system supports getting the path to the program binary itself.
#pragma push_macro("UWSIGN_SUPPORT_INSTALL_PATH")
#undef UWSIGN_SUPPORT_INSTALL_PATH
#if (defined(__linux) || defined(__linux__) || defined(__gnu_linux__)) || defined(__CYGWIN__) || defined(__sun)
# define UWSIGN_SUPPORT_INSTALL_PATH
#elif defined(_WIN32)
# define UWSIGN_SUPPORT_INSTALL_PATH
#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(BSD) || defined(_SYSTYPE_BSD)
# define UWSIGN_SUPPORT_INSTALL_PATH
#elif defined(__OpenBSD__)
# define UWSIGN_SUPPORT_INSTALL_PATH
#elif defined(__APPLE__)
# define UWSIGN_SUPPORT_INSTALL_PATH
#endif

/// @details      Some platforms do not support special characters
#pragma push_macro("UWSIGN_NOT_SUPPORT_SPECIAL_CHAR")
#undef UWSIGN_NOT_SUPPORT_SPECIAL_CHAR
#if (defined(_WIN32) && defined(_WIN32_WINDOWS)) || defined(__MSDOS__) || defined(__DJGPP__)
# define UWSIGN_NOT_SUPPORT_SPECIAL_CHAR
#endif

/// @details     Sockets can be created using the Unix path
#pragma push_macro("UWSIGN_SUPPORT_UNIX_PATH_SOCKET")
#undef UWSIGN_SUPPORT_UNIX_PATH_SOCKET
#if ((defined(__linux) || defined(__linux__) || defined(__gnu_linux__)) || defined(__CYGWIN__) || defined(__sun) || defined(__DragonFly__) ||                  \
     defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(BSD) || defined(_SYSTYPE_BSD) || defined(__OpenBSD__) ||            \
     defined(__APPLE__)) &&                                                                                                                                    \
    !(defined(_WIN32) && !defined(__CYGWIN__) && !defined(__WINE__) && !defined(__BIONIC__))
# define UWSIGN_SUPPORT_UNIX_PATH_SOCKET
#endif

/// @details      __gnu__::__used__
#pragma push_macro("UWSIGN_GNU_USED")
#undef UWSIGN_GNU_USED
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__used__)
# define UWSIGN_GNU_USED [[__gnu__::__used__]]
#else
# define UWSIGN_GNU_USED
#endif

/// @see          https://gcc.gnu.org/legacy-ml/gcc-patches/2005-07/msg01969.html
/// @details      on gcc, clang: [[__gnu__::__nodebug__]]
#pragma push_macro("UWSIGN_GNU_NODEBUG")
#undef UWSIGN_GNU_NODEBUG
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__nodebug__)
# define UWSIGN_GNU_NODEBUG [[__gnu__::__nodebug__]]
#else
# define UWSIGN_GNU_NODEBUG
#endif

/// @details gnu's musttail does not require that the function must have the same prototype as the original function
///          clang is stricter than gnu, so clang's musttail attribute is not compatible with gnu's musttail.
///          Instead gnu is semantically compatible with clang's semantics, but gnu isn't intended to be compatible with clang's attribute, so clang is judged
///          in advance. Platforms that do not support musttail add a warning to indicate that the optimization must be turned on.
#pragma push_macro("UWSIGN_MUSTTAIL")
#undef UWSIGN_MUSTTAIL
#if UWSIGN_HAS_CPP_ATTRIBUTE(clang::musttail)
# define UWSIGN_MUSTTAIL [[clang::musttail]]
#elif UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__musttail__)
# define UWSIGN_MUSTTAIL [[__gnu__::__musttail__]]
#else
# define UWSIGN_MUSTTAIL

// Push warning pragmas for different platforms to suppress -Werror=cpp
# if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wcpp"
# elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wcpp"
# elif defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4068)  // unknown pragma
# endif

# warning "Please turn on optimization to ensure that tail calls are generated correctly, otherwise stack overflow behavior may occur."

// Pop warning pragmas
# if defined(__clang__)
#  pragma clang diagnostic pop
# elif defined(__GNUC__)
#  pragma GCC diagnostic pop
# elif defined(_MSC_VER)
#  pragma warning(pop)
# endif

#endif

/// @brief        __has_feature
/// @details      __has_feature is not provided by standard cpp, avoid using __has_feature on unsupport compiler
#pragma push_macro("UWSIGN_HAS_FEATURE")
#undef UWSIGN_HAS_FEATURE
#ifdef __has_feature
# define UWSIGN_HAS_FEATURE(...) __has_feature(__VA_ARGS__)
#else
# define UWSIGN_HAS_FEATURE(...) 0
#endif

/// @brief        Suppress All Sanitizers for a function
#pragma push_macro("UWSIGN_NO_SANITIZE")
#undef UWSIGN_NO_SANITIZE
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__no_sanitize__)  // Clang, GCC
# define UWSIGN_NO_SANITIZE [[__gnu__::__no_sanitize__("all")]]
#else
# define UWSIGN_NO_SANITIZE
#endif

#pragma push_macro("UWSIGN_CPP_RTTI")
#undef UWSIGN_CPP_RTTI
#if defined(_MSC_VER) && !defined(__clang__)
# if __cpp_rtti >= 199711L && _HAS_RTTI
#  define UWSIGN_CPP_RTTI
# endif
#else
# if __cpp_rtti >= 199711L
#  define UWSIGN_CPP_RTTI
# endif
#endif

#pragma push_macro("UWSIGN_CPP_EXCEPTIONS")
#undef UWSIGN_CPP_EXCEPTIONS
#if defined(_MSC_VER) && !defined(__clang__)
# if __cpp_exceptions >= 199711L && _HAS_EXCEPTIONS
#  define UWSIGN_CPP_EXCEPTIONS
# endif
#else
# if __cpp_exceptions >= 199711L
#  define UWSIGN_CPP_EXCEPTIONS
# endif
#endif

#pragma push_macro("UWSIGN_SUPPORT_PRELOAD_DL")
#undef UWSIGN_SUPPORT_PRELOAD_DL
#if (defined(_WIN32) || defined(__CYGWIN__)) && (!defined(__CYGWIN__) && !defined(__WINE__)) ||                                                                \
    ((!defined(_WIN32) || defined(__WINE__)) && (__has_include(<dlfcn.h>) && (defined(__CYGWIN__) || (!defined(__NEWLIB__) && !defined(__wasi__)))))
# define UWSIGN_SUPPORT_PRELOAD_DL
#endif

/// @brief        Determine whether the operating system supports mmap
/// @note         support: win9x, winnt, posix.
///               When AddressSanitizer is enabled, disable mmap-backed linear memory because the mmap backend
///               reserves very large VMAs (e.g. wasm32 full-protection) which can cause excessive ASan shadow
///               memory usage and OOM in fuzzing/CI environments.
#pragma push_macro("UWSIGN_SUPPORT_MMAP")
#undef UWSIGN_SUPPORT_MMAP
#if !defined(UWSIGN_FORCE_DISABLE_MMAP) &&                                                                                                                       \
    (((defined(_WIN32) || defined(__CYGWIN__)) ||                                                                                                              \
      (!defined(__NEWLIB__) && !(defined(__MSDOS__) || defined(__DJGPP__)) && (!defined(__wasm__) || (defined(__wasi__) && defined(_WASI_EMULATED_MMAN))) &&   \
       __has_include(<sys/mman.h>)))) && !(UWSIGN_HAS_FEATURE(address_sanitizer) || defined(__SANITIZE_ADDRESS__))
# define UWSIGN_SUPPORT_MMAP
#endif

#pragma push_macro("UWSIGN_SUPPORT_WEAK_SYMBOL")
#undef UWSIGN_SUPPORT_WEAK_SYMBOL
// Currently only supports ELF weak symbols.
#if defined(__ELF__) && UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__weak__) && UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__used__)
# define UWSIGN_SUPPORT_WEAK_SYMBOL
#endif

#pragma push_macro("UWSIGN_NOINLINE")
#undef UWSIGN_NOINLINE
#if UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__noinline__)
# define UWSIGN_NOINLINE [[__gnu__::__noinline__]]
#elif UWSIGN_HAS_CPP_ATTRIBUTE(msvc::noinline)
# define UWSIGN_NOINLINE [[msvc::noinline]]
#else
# define UWSIGN_NOINLINE
#endif

#pragma push_macro("UWSIGN_FASTCALL")
#undef UWSIGN_FASTCALL
#if defined(__i386__) || defined(_M_IX86)
# if (defined(_MSC_VER) && !defined(__clang__)) && !UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__fastcall__) && !defined(__WINE__)
#  define UWSIGN_FASTCALL __fastcall
# elif (defined(__clang__) || defined(__GNUC__)) && UWSIGN_HAS_CPP_ATTRIBUTE(__gnu__::__fastcall__)
#  define UWSIGN_FASTCALL __attribute__((__fastcall__))
# else
#  define UWSIGN_FASTCALL
# endif
#else
# define UWSIGN_FASTCALL
#endif
