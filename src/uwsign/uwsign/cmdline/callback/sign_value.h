/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        sign_value.h
 * @brief       uwsign sign value callback
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
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/cmdline/impl.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include <uwsign/uwsign/cmdline/params/value.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline::params::details
{
#if defined(UWSIGN_MODULE)
    extern "C++"
#else
    inline constexpr
#endif
        void required_value_pretreatment(char8_t const* const*& argv_curr,
                                         char8_t const* const* argv_end,
                                         ::uwsign::utils::container::vector<::uwsign::utils::cmdline::parameter_parsing_results>& pr) noexcept
    {
        auto currp1{argv_curr + 1u};

        if(currp1 != argv_end) [[likely]]
        {
            if(auto const currp1_cstr{*currp1}; currp1_cstr != nullptr)
            {
                auto const currp1_str{::uwsign::utils::container::u8cstring_view{::fast_io::mnp::os_c_str(currp1_cstr)}};
                if(!currp1_str.empty() && currp1_str.front_unchecked() != u8'-')
                {
                    pr.emplace_back_unchecked(currp1_str, nullptr, ::uwsign::utils::cmdline::parameter_parsing_results_type::occupied_arg);
                    argv_curr = currp1 + 1u;
                    return;
                }
            }
        }

        argv_curr = currp1;
    }

#if defined(UWSIGN_MODULE)
    extern "C++" UWSIGN_GNU_COLD
#else
    UWSIGN_GNU_COLD inline constexpr
#endif
        ::uwsign::utils::cmdline::parameter_return_type
        required_value_callback([[maybe_unused]] ::uwsign::utils::cmdline::parameter_parsing_results* para_begin,
                                ::uwsign::utils::cmdline::parameter_parsing_results* para_curr,
                                ::uwsign::utils::cmdline::parameter_parsing_results* para_end) noexcept
    {
        auto currp1{para_curr + 1u};

        if(currp1 == para_end || (currp1->type != ::uwsign::utils::cmdline::parameter_parsing_results_type::arg &&
                                  currp1->type != ::uwsign::utils::cmdline::parameter_parsing_results_type::occupied_arg)) [[unlikely]]
        {
            auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
            ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
                ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
            auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

            ::fast_io::io::perr(u8log_output_ul,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"Usage: ",
                                ::uwsign::utils::cmdline::print_usage(*(para_curr->para)),
                                u8"\n\n");
            return ::uwsign::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        currp1->type = ::uwsign::utils::cmdline::parameter_parsing_results_type::occupied_arg;
        return ::uwsign::utils::cmdline::parameter_return_type::def;
    }
}  // namespace uwsign::uwsign::cmdline::params::details

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
