/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        consolecp_win32.h
 * @brief       Windows NT console UTF-8 setup for uwsign startup
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstdint>
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
    /// @brief Set Windows NT console input and output code pages to UTF-8.
    struct set_win32_console_io_cp_to_utf8
    {
        inline static constexpr ::std::uint_least32_t utf8_coding{65001u};

        UWSIGN_GNU_COLD inline set_win32_console_io_cp_to_utf8() noexcept
        {
            if(!::fast_io::win32::SetConsoleOutputCP(utf8_coding)) [[unlikely]]
            {
                report_warning(u8"SetConsoleOutputCP");
            }

            if(!::fast_io::win32::SetConsoleCP(utf8_coding)) [[unlikely]]
            {
                report_warning(u8"SetConsoleCP");
            }
        }

        inline static void report_warning(char8_t const* api) noexcept
        {
            if(::uwsign::uwsign::io::show_warning)
            {
                ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                    u8"uwsign: ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                    u8"[warn]  ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    u8"set_win32_console_io_cp_to_utf8: ",
                                    ::fast_io::mnp::os_c_str(api),
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
    };
}  // namespace uwsign::uwsign::global
#endif

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
