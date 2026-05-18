/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        uwsign.h
 * @brief       uwsign C++ startup entry points
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstddef>
# include <cstdint>
# include <bit>
# include <limits>
# include <utility>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/string.h>
# include <fast_io_dsal/vector.h>
# include <uwsign/utils/debug/impl.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include <uwsign/uwsign/cmdline/impl.h>
# include <uwsign/uwsign/crtmain/global/impl.h>
// callback
# include <uwsign/uwsign/cmdline/callback/impl.h>
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

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign
{
    enum class retval : int
    {
        ok = 0,
        parameter_error = 1,
        unimplemented = 1
    };

    namespace details
    {
        inline void print_parameter_error(char8_t const* message) noexcept
        {
            ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                ::fast_io::mnp::os_c_str(message),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                u8"\n\n");
        }
    }  // namespace details

    /// @brief      uwsign C++ uz u8 main function.
    /// @param      argc Argument Count
    /// @param      argv Argument Vector
    /// @return     exit value
    inline int uwsign_uz_u8main(::std::size_t argc, char8_t const* const* argv) noexcept
    {
        switch(::uwsign::uwsign::cmdline::parsing(argc, argv))
        {
            case ::uwsign::uwsign::cmdline::parsing_return_val::def:
            {
                break;
            }
            case ::uwsign::uwsign::cmdline::parsing_return_val::return0:
            {
                return static_cast<int>(retval::ok);
            }
            case ::uwsign::uwsign::cmdline::parsing_return_val::returnm1:
            {
                return static_cast<int>(retval::parameter_error);
            }
            [[unlikely]] default:
            {
#if (defined(_DEBUG) || defined(DEBUG)) && defined(UWSIGN_ENABLE_DETAILED_DEBUG_CHECK)
                ::uwsign::utils::debug::trap_and_inform_bug_pos();
#endif
                ::std::unreachable();
            }
        }

        ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                            u8"uwsign: ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                            u8"[error] ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                            u8"signing command handling has not been implemented yet.\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                            u8"uwsign: ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_GREEN),
                            u8"[info]  ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                            u8"Use --help to see the currently available options.",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                            u8"\n");
        return static_cast<int>(retval::unimplemented);
    }

#if !((defined(_WIN32) && !defined(__CYGWIN__)) && !defined(_WIN32_WINDOWS))  // NOT WINNT

    /// @brief      uwsign C++ main function (not Windows NT).
    /// @details    Handles startup initialization and converts argv to the UTF-8 entry path.
    /// @param      argc Argument Count
    /// @param      argv Argument Vector
    /// @return     exit value
    /// @see        main()
    inline int uwsign_main_non_winnt(int argc, char** argv) noexcept
    {
        ::uwsign::uwsign::global::tz_set_s tz_set_ele{};

        constexpr auto size_t_max{::std::numeric_limits<::std::size_t>::max()};
        constexpr auto int_max{::std::numeric_limits<int>::max()};
        if constexpr(size_t_max < int_max)
        {
            if(argc > static_cast<int>(size_t_max)) [[unlikely]]
            {
                details::print_parameter_error(u8"argc exceeds the maximum value of size_t.");
                return static_cast<int>(retval::parameter_error);
            }
        }

        if(argc < 0) [[unlikely]]
        {
            details::print_parameter_error(u8"argc is less than zero.");
            return static_cast<int>(retval::parameter_error);
        }

        auto const argc_uz{static_cast<::std::size_t>(argc)};
        using char8_t_const_ptr_const_may_alias_ptr UWSIGN_GNU_MAY_ALIAS = char8_t const* const*;
        auto const argv_u8{reinterpret_cast<char8_t_const_ptr_const_may_alias_ptr>(argv)};

# if defined(_WIN32) || (!defined(__wasi__) && __has_include(<sys/socket.h>) && __has_include(<netinet/in.h>))
        ::fast_io::net_service service{};
# endif

        return uwsign_uz_u8main(argc_uz, argv_u8);
    }

#else

    /// @brief      uwsign C++ main function (Windows NT).
    /// @details    Handles startup initialization and retrieves UTF-16 command-line data from Windows.
    /// @return     exit value
    /// @see        main()
    inline int uwsign_main_winnt() noexcept
    {
        ::uwsign::uwsign::global::set_win32_console_io_cp_to_utf8 set_native_console_io_cp_to_utf8_ele{};
        ::uwsign::uwsign::global::enable_win32_ansi enable_native_ansi_ele{};
        ::uwsign::uwsign::global::tz_set_s tz_set_ele{};

        auto const nt_proc_para{::fast_io::win32::nt::nt_get_current_peb()->ProcessParameters};
        auto const nt_proc_cmdline{nt_proc_para->CommandLine};

        int u16_cmdline_argc;
        auto const u16_cmdline_argv{::fast_io::win32::CommandLineToArgvW(nt_proc_cmdline.Buffer, ::std::addressof(u16_cmdline_argc))};
        if(u16_cmdline_argv == nullptr) [[unlikely]]
        {
            ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_RED),
                                u8"[fatal] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"CommandLineToArgvW failed: ",
                                ::fast_io::error{::fast_io::win32_domain_value, ::fast_io::win32::GetLastError()},
                                u8"\n",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                u8"Terminate.\n\n");
            ::fast_io::fast_terminate();
        }

        struct u16_cmdline_argv_guard
        {
            char16_t** argv{};
            inline constexpr explicit u16_cmdline_argv_guard(char16_t** p) noexcept : argv{p} {}
            u16_cmdline_argv_guard(u16_cmdline_argv_guard const&) = delete;
            u16_cmdline_argv_guard& operator= (u16_cmdline_argv_guard const&) = delete;
            inline constexpr ~u16_cmdline_argv_guard()
            {
                if(argv != nullptr) { ::fast_io::win32::LocalFree(argv); }
            }
        } guard{u16_cmdline_argv};

        static_assert(::std::numeric_limits<::std::size_t>::max() >= ::std::numeric_limits<int>::max());
        auto const argc_uz{static_cast<::std::size_t>(u16_cmdline_argc)};

        ::fast_io::u8string parameter_sequence{};
        ::fast_io::vector<char8_t const*> argv{};
        argv.reserve(argc_uz);
        ::fast_io::u8ostring_ref_fast_io u8_storage_ref{::std::addressof(parameter_sequence)};

        static_assert(sizeof(::std::size_t) == sizeof(char8_t const*));
        for(auto curr_argv{u16_cmdline_argv}; curr_argv != u16_cmdline_argv + argc_uz; ++curr_argv)
        {
            argv.push_back_unchecked(::std::bit_cast<char8_t const*>(parameter_sequence.size()));
            ::fast_io::operations::print_freestanding<false>(u8_storage_ref, ::fast_io::mnp::code_cvt_os_c_str(*curr_argv), u8"\0");
        }

        for(auto const parameter_sequence_cbegin{parameter_sequence.cbegin()}; auto& curr_argv: argv)
        {
            auto const offset{::std::bit_cast<::std::size_t>(curr_argv)};
            curr_argv = parameter_sequence_cbegin + offset;
        }

# if defined(_WIN32) || (!defined(__wasi__) && __has_include(<sys/socket.h>) && __has_include(<netinet/in.h>))
        ::fast_io::net_service service{};
# endif

        return uwsign_uz_u8main(argc_uz, argv.data());
    }

#endif

}  // namespace uwsign::uwsign

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
