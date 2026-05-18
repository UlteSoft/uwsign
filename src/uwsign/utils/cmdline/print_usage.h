/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-07-07
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstdint>
# include <cstddef>
# include <concepts>
# include <new>
# include <memory>
# include <utility>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include "handle.h"
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::cmdline
{
    namespace details
    {
        struct usage_printer
        {
            ::uwsign::utils::cmdline::parameter const* para{};
        };

        /// @brief Print the usage
        /// @details Currently only char8_t is supported
        /// @throws maybe throw fast_io::error, see the implementation of the stream
        template <typename Stm>
        inline constexpr void print_define(::fast_io::io_reserve_type_t<char8_t, usage_printer>, Stm&& stream, usage_printer const uspt)
        {
            auto const p{uspt.para};
            if(p == nullptr) [[unlikely]] { return; }

#ifdef UWSIGN
            ::fast_io::io::perr(::std::forward<Stm>(stream),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"[",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_GREEN),
                                p->name);

            for(auto curr_base{p->alias.base}; curr_base != p->alias.base + p->alias.len; ++curr_base)
            {
                ::fast_io::io::perr(::std::forward<Stm>(stream),
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    u8"|",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_GREEN),
                                    *curr_base);
            }

            ::fast_io::io::perr(::std::forward<Stm>(stream),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                p->usage,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
#else
            ::fast_io::io::perr(::std::forward<Stm>(stream), u8"[", p->name);

            for(auto curr_base{p->alias.base}; curr_base != p->alias.base + p->alias.len; ++curr_base)
            {
                ::fast_io::io::perr(::std::forward<Stm>(stream), u8"|", *curr_base);
            }

            ::fast_io::io::perr(::std::forward<Stm>(stream), u8"] ", p->usage);
#endif
        }
    }  // namespace details

    inline constexpr details::usage_printer print_usage(::uwsign::utils::cmdline::parameter const& para) noexcept
    { return details::usage_printer{::std::addressof(para)}; }
}

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
