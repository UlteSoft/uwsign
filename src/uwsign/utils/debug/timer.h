/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-01
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/ansies/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::debug
{
    struct timer
    {
        ::uwsign::utils::container::u8string_view s{};
        ::fast_io::unix_timestamp t0{};
#ifdef UWSIGN_CPP_EXCEPTIONS
        // `t0_success`: Only useful when exceptions are on, off exceptions directly crash the program.
        bool t0_success{true};
#endif

        // posix_clock_gettime may throw
        // Please use string literals initially to prevent dangling.

        UWSIGN_GNU_COLD inline explicit constexpr timer(::uwsign::utils::container::u8string_view strvw) noexcept : s{strvw}
        {
#ifdef UWSIGN_CPP_EXCEPTIONS
            try
#endif
            {
                t0 = ::fast_io::posix_clock_gettime(::fast_io::posix_clock_id::monotonic_raw);
            }
#ifdef UWSIGN_CPP_EXCEPTIONS
            catch(::fast_io::error)
            {
# ifdef UWSIGN
                if(::uwsign::uwsign::io::show_warning)
                {
                    ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                        u8"uwsign: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                        u8"[warn]  ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                        u8"timer can't get the time. ",
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
# endif

                // Mark t0 as a failure and do not check t1 subsequently
                t0_success = false;
            }
#endif
        }

        inline constexpr timer(timer const&) = delete;
        inline constexpr timer& operator= (timer const&) = delete;
        inline constexpr timer(timer&&) = delete;
        inline constexpr timer& operator= (timer&&) = delete;

        UWSIGN_GNU_COLD inline constexpr ~timer()
        {
#ifdef UWSIGN_CPP_EXCEPTIONS
            if(!t0_success) [[unlikely]]
            {
                // If the t0 fetch fails, processing is not continued to prevent outputting the wrong time.
                return;
            }
#endif

            // `t1` no initialization is required, even if subsequent exceptions are not used, there is no ub.
            ::fast_io::unix_timestamp t1;

#ifdef UWSIGN_CPP_EXCEPTIONS
            try
#endif
            {
                t1 = ::fast_io::posix_clock_gettime(::fast_io::posix_clock_id::monotonic_raw);
            }
#ifdef UWSIGN_CPP_EXCEPTIONS
            catch(::fast_io::error)
            {
# ifdef UWSIGN
                if(::uwsign::uwsign::io::show_warning)
                {
                    ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                        u8"uwsign: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                        u8"[warn]  ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                        u8"timer can't get the time. ",
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
# endif

                // An error message has been output and the return value cannot be obtained
                return;
            }
#endif

            ::fast_io::iso8601_timestamp local_realtime{};

#ifdef UWSIGN_CPP_EXCEPTIONS
            try
#endif
            {
                local_realtime = ::fast_io::local(::fast_io::posix_clock_gettime(::fast_io::posix_clock_id::realtime));
            }
#ifdef UWSIGN_CPP_EXCEPTIONS
            catch(::fast_io::error)
            {
                // do nothing
            }
#endif

            // Output correct time
#ifdef UWSIGN
            ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_CYAN),
                                u8"[debug] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"timer \"",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                s,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"\": ",
                                t1 - t0,
                                u8"s ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_GREEN),
                                u8"[",
                                local_realtime,
                                u8"]\n",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
#else
            ::fast_io::io::perr(::fast_io::u8err(), u8"uwsign: [debug] timer \"", s, u8"\": ", t1 - t0, u8"s [", local_realtime, u8"]\n");
#endif
        }
    };
}

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
