/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        version.h
 * @brief       uwsign version callback
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <memory>
# include <utility>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// platform
# if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#  include <linux/version.h>
# endif
# if defined(__APPLE__) || defined(__DARWIN_C_LEVEL)
#  include <TargetConditionals.h>
#  include <Availability.h>
# endif
# if (defined(__MIPS__) || defined(__mips__) || defined(_MIPS_ARCH))
#  include <sgidefs.h>
# endif
// imported
# include <fast_io.h>
# include <fast_io_crypto.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/version/impl.h>
# include <uwsign/utils/cmdline/impl.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

#ifndef UWSIGN_GIT_COMMIT_ID
# define UWSIGN_GIT_COMMIT_ID u8"unknown"
#endif

#ifndef UWSIGN_GIT_REMOTE_URL
# define UWSIGN_GIT_REMOTE_URL u8"unknown"
#endif

#ifndef UWSIGN_GIT_COMMIT_DATA
# define UWSIGN_GIT_COMMIT_DATA u8"unknown"
#endif

#ifndef UWSIGN_GIT_UPSTREAM_BRANCH
# define UWSIGN_GIT_UPSTREAM_BRANCH u8"unknown"
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline::params::details
{

    template <typename Stm>
    inline constexpr void logo_u8print_not_rst_impl([[maybe_unused]] Stm && stm) noexcept
    {
#if 0
        ::fast_io::io::perr(::std::forward<Stm>(stm),
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                            u8"\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(42, 92, 170)),
                            u8" ----------------------------------------- \n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(42, 92, 170)),
                            u8"|",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(42, 160, 180)),
                            u8" UlteSoft ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(76, 190, 120)),
                            u8"WebAssembly ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(220, 176, 72)),
                            u8"Signer       ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(42, 92, 170)),
                            u8"|\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RGB(42, 92, 170)),
                            u8" ----------------------------------------- \n\n");

#endif
    }

#if defined(UWSIGN_MODULE)
    extern "C++" UWSIGN_GNU_COLD
#else
    UWSIGN_GNU_COLD inline constexpr
#endif
        ::uwsign::utils::cmdline::parameter_return_type version_callback(::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                         ::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                         ::uwsign::utils::cmdline::parameter_parsing_results*) noexcept
    {
        auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
        ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
            ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
        auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

        logo_u8print_not_rst_impl(u8log_output_ul);

        ::fast_io::io::perr(u8log_output_ul,
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_PURPLE),
                            u8"UlteSoft WebAssembly Signer",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                            u8"\nMode: "
#if defined(UWSIGN_MODE_RELEASE)
                            u8"Release "
#elif defined(UWSIGN_MODE_RELEASEDBG)
                            u8"Releasedbg "
#elif defined(UWSIGN_MODE_MINSIZEREL)
                            u8"Minsizerel "
#elif defined(UWSIGN_MODE_DEBUG)
                            u8"Debug "
#else
                            u8"Unknown "
#endif
#if defined(UWSIGN_MODULE)
                            u8"(CXX-Module Build) "
#endif
                            u8"\nCopyright (c) 2026-present UlteSoft. All rights reserved.  "
                            u8"\nVersion: ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_GREEN),
                            ::uwsign::utils::version{UWSIGN_VERSION_X, UWSIGN_VERSION_Y, UWSIGN_VERSION_Z, UWSIGN_VERSION_S},
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                            u8" (",
                            UWSIGN_GIT_COMMIT_DATA,
                            u8")"
                            u8"\nGit: "
#ifdef UWSIGN_GIT_HAS_UNCOMMITTED_MODIFICATIONS
                            u8"(M) "
#endif
                            ,
                            UWSIGN_GIT_COMMIT_ID,
                            u8" branch '",
                            UWSIGN_GIT_UPSTREAM_BRANCH,
                            u8"' of ",
                            UWSIGN_GIT_REMOTE_URL,
                            u8"\nCompiler: "
#if defined(__INTEL_LLVM_COMPILER)
                            u8"Intel LLVM Compiler "
#elif defined(__clang__)
                            u8"LLVM clang "
# if defined(__clang_version__)
                            __clang_version__
# endif
#elif defined(__GNUC__)
                            u8"GCC "
# if defined(__VERSION__)
                            __VERSION__
# endif
#elif defined(_MSC_VER)
                            u8"Microsoft Visual C++ ",
                            _MSC_VER,
#elif defined(__INTELLISENSE__)
                            u8"Intel C++ Compiler"
#else
                            u8"Unknown C++ compiler"
#endif
                            u8"\nC++ STD Library: "
#if defined(_LIBCPP_VERSION)
                            u8"LLVM libc++ ",
                            _LIBCPP_VERSION,
#elif defined(__GLIBCXX__)
                            u8"GNU C++ Library ",
                            _GLIBCXX_RELEASE,
                            u8" ",
                            __GLIBCXX__,
#elif defined(_MSVC_STL_UPDATE)
                            u8"Microsoft Visual C++ STL ",
                            _MSVC_STL_UPDATE,
#else
                            u8"Unknown C++ standard library",
#endif
                            u8"\nArchitecture: "
#if defined(__wasm__)
                            u8"WASM"
# if defined(__wasm32__)
                            u8"32"
# elif defined(__wasm64__)
                            u8"64"
# endif
#elif defined(__alpha__)
                            u8"DEC Alpha"
#elif defined(__arm64ec__) || defined(_M_ARM64EC)
                            u8"ARM64EC"
#elif defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64)
                            u8"AArch64"
# if defined(__AARCH64EB__) || defined(__AARCH_BIG_ENDIAN)
                            u8"EB"
# endif
#elif defined(__arm__) || defined(_M_ARM)
                            u8"ARM"
# if defined(__ARMEB__) || defined(__ARM_BIG_ENDIAN)
                            u8"EB"
# endif
#elif (defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64)) && !(defined(__arm64ec__) || defined(_M_ARM64EC))
                            u8"x86_64"
#elif defined(__i386__) || defined(_M_IX86)
# if defined(__i686__) || defined(_MSC_VER)
                            u8"i686"
# elif defined(__i586__)
                            u8"i586"
# elif defined(__i486__)
                            u8"i486"
# else
                            u8"i386"
# endif
#elif defined(__riscv)
                            u8"RISC-V"
# if __riscv_xlen == 32
                            u8"32"
# elif __riscv_xlen == 64
                            u8"64"
# endif
#elif defined(__loongarch64)
                            u8"LoongArch64"
#elif defined(__loongarch32)
                            u8"LoongArch32"
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(_M_PPC64)
                            u8"PowerPC64"
#elif defined(__powerpc__) || defined(__ppc__) || defined(_M_PPC)
                            u8"PowerPC"
#elif defined(__mips64) || defined(__mips64__) || (defined(_MIPS_ARCH) && defined(_MIPS_SZLONG) && _MIPS_SZLONG == 64)
                            u8"MIPS64"
#elif defined(__mips__) || defined(__mips) || defined(_MIPS_ARCH)
                            u8"MIPS"
#elif defined(__s390x__)
                            u8"IBM z/Architecture"
#elif defined(__s390__)
                            u8"IBM S/390"
#else
                            u8"Unknown"
#endif
                            u8"\nPlatform: "
#if defined(_WIN32)
                            u8"Windows"
#elif defined(__APPLE__) && defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
                            u8"iPhoneOS"
#elif defined(__APPLE__)
                            u8"macOS"
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
                            u8"Linux"
#elif defined(__FreeBSD__)
                            u8"FreeBSD"
#elif defined(__OpenBSD__)
                            u8"OpenBSD"
#elif defined(__NetBSD__)
                            u8"NetBSD"
#elif defined(__DragonFly__)
                            u8"DragonFlyBSD"
#elif defined(__wasi__)
                            u8"WASI"
#elif defined(__unix__)
                            u8"Unix"
#else
                            u8"Unknown"
#endif
                            u8"\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                            u8"\n");

        return ::uwsign::utils::cmdline::parameter_return_type::return_imme;
    }
}  // namespace uwsign::uwsign::cmdline::params::details

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
