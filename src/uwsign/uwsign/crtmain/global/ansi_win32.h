/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        ansi_win32.h
 * @brief       Windows NT ANSI escape setup for uwsign startup
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstdint>
# include <memory>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

#if (defined(_WIN32) && !defined(__CYGWIN__)) && !defined(_WIN32_WINDOWS)
UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::global
{
    /// @brief Enable ANSI escape processing for stdout and stderr on Windows NT consoles.
    struct enable_win32_ansi
    {
        inline static constexpr ::std::uint_least32_t enable_virtual_terminal_processing{0x0004u};

        UWSIGN_GNU_COLD inline enable_win32_ansi() noexcept
        {
            set_out();
            set_err();
        }

        inline void report_warning(char8_t const* api, char8_t const* stream_name) noexcept
        {
            if(::uwsign::uwsign::io::show_warning)
            {
                ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                    u8"uwsign: ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                    u8"[warn]  ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    u8"enable_virtual_terminal_processing: ",
                                    ::fast_io::mnp::os_c_str(api),
                                    u8" ",
                                    ::fast_io::mnp::os_c_str(stream_name),
                                    u8" failed. ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_ORANGE),
                                    u8"(sign)\n",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));

                if(::uwsign::uwsign::io::warning_fatal) [[unlikely]]
                {
                    ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                        u8"uwsign: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_RED),
                                        u8"[fatal] ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                        u8"Convert warnings to fatal errors. ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_ORANGE),
                                        u8"(sign)\n\n",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline void set_out() noexcept
        {
            ::std::uint_least32_t out_omode;
            void* out_handle{::fast_io::win32::GetStdHandle(::fast_io::win32_stdout_number)};
            if(out_handle == nullptr) [[unlikely]]
            {
                report_warning(u8"GetStdHandle", u8"stdout");
                return;
            }

            if(!::fast_io::win32::GetConsoleMode(out_handle, ::std::addressof(out_omode))) [[unlikely]]
            {
                return;
            }

            if(!::fast_io::win32::SetConsoleMode(out_handle, out_omode | enable_virtual_terminal_processing)) [[unlikely]]
            {
                report_warning(u8"SetConsoleMode", u8"stdout");
                return;
            }
        }

        inline void set_err() noexcept
        {
            ::std::uint_least32_t err_omode;
            void* err_handle{::fast_io::win32::GetStdHandle(::fast_io::win32_stderr_number)};
            if(err_handle == nullptr) [[unlikely]]
            {
                report_warning(u8"GetStdHandle", u8"stderr");
                return;
            }

            if(!::fast_io::win32::GetConsoleMode(err_handle, ::std::addressof(err_omode))) [[unlikely]]
            {
                return;
            }

            if(!::fast_io::win32::SetConsoleMode(err_handle, err_omode | enable_virtual_terminal_processing)) [[unlikely]]
            {
                report_warning(u8"SetConsoleMode", u8"stderr");
                return;
            }
        }
    };
}  // namespace uwsign::uwsign::global
#endif

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
