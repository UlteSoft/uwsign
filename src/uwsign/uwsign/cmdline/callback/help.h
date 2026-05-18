/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        help.h
 * @brief       uwsign help callback
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstddef>
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
# include <uwsign/uwsign/cmdline/impl.h>
# include <uwsign/uwsign/cmdline/params/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline::params::details
{
    template <::std::size_t N>
    inline constexpr ::uwsign::utils::container::array<char8_t, N + 1> u8nspace() noexcept
    {
        ::uwsign::utils::container::array<char8_t, N + 1> res{};
        for(::std::size_t i{}; i != N; ++i) { res[i] = u8' '; }
        res[N] = u8'\0';
        return res;
    }

    inline constexpr auto parameter_max_principal_name_size_u8nspace{u8nspace<::uwsign::uwsign::cmdline::parameter_max_principal_name_size + 4>()};

    template <typename Stm>
    inline constexpr void help_output_single_cate(Stm&& stm, ::uwsign::utils::cmdline::categorization cate) noexcept
    {
        for(auto const p: ::uwsign::uwsign::cmdline::parameters)
        {
            if(p->cate != cate) { continue; }
            ::fast_io::io::perr(::std::forward<Stm>(stm),
                                u8"  ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_GREEN),
                                ::fast_io::mnp::left(p->name, ::uwsign::uwsign::cmdline::parameter_max_principal_name_size));
            ::fast_io::io::perrln(::std::forward<Stm>(stm),
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                  u8"  -----  ",
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                  p->describe);
            ::fast_io::io::perrln(::std::forward<Stm>(stm),
                                  parameter_max_principal_name_size_u8nspace.element,
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_PURPLE),
                                  u8"Usage: ",
                                  ::uwsign::utils::cmdline::print_usage(*p));
        }
    }

    template <typename Stm>
    inline constexpr void help_output_all(Stm&& stm) noexcept
    {
        for(auto const p: ::uwsign::uwsign::cmdline::parameters)
        {
            ::fast_io::io::perr(::std::forward<Stm>(stm),
                                u8"  ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_GREEN),
                                ::fast_io::mnp::left(p->name, ::uwsign::uwsign::cmdline::parameter_max_principal_name_size));
            ::fast_io::io::perrln(::std::forward<Stm>(stm),
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                  u8"  -----  ",
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                  p->describe);
            ::fast_io::io::perrln(::std::forward<Stm>(stm),
                                  parameter_max_principal_name_size_u8nspace.element,
                                  ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_PURPLE),
                                  u8"Usage: ",
                                  ::uwsign::utils::cmdline::print_usage(*p));
        }
    }

    inline constexpr void help_output_category_header(auto&& stm, char8_t const* cate_name) noexcept
    {
        ::fast_io::io::perr(::std::forward<decltype(stm)>(stm),
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                            u8"Arguments:\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_CYAN),
                            u8"  <",
                            ::fast_io::mnp::os_c_str(cate_name),
                            u8">",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                            u8":\n");
    }

    inline constexpr void help_output_hint(auto&& stm, char8_t const* cate_name) noexcept
    {
        ::fast_io::io::perr(::std::forward<decltype(stm)>(stm),
                            u8"\n",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_CYAN),
                            u8"  <",
                            ::fast_io::mnp::os_c_str(cate_name),
                            u8">",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                            u8"  -----  ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                            u8"Use \"",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                            u8"--help ",
                            ::fast_io::mnp::os_c_str(cate_name),
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                            u8"\" to display the ",
                            ::fast_io::mnp::os_c_str(cate_name),
                            u8" arguments.\n");
    }

#if defined(UWSIGN_MODULE)
    extern "C++" UWSIGN_GNU_COLD
#else
    UWSIGN_GNU_COLD inline constexpr
#endif
        ::uwsign::utils::cmdline::parameter_return_type help_callback([[maybe_unused]] ::uwsign::utils::cmdline::parameter_parsing_results* para_begin,
                                                                      ::uwsign::utils::cmdline::parameter_parsing_results* para_curr,
                                                                      ::uwsign::utils::cmdline::parameter_parsing_results* para_end) noexcept
    {
        auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
        ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
            ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
        auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

        auto currp1{para_curr + 1u};

        if(currp1 == para_end || currp1->type != ::uwsign::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
        {
            ::fast_io::io::perr(u8log_output_ul,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"Arguments:\n");
            help_output_single_cate(u8log_output_ul, ::uwsign::utils::cmdline::categorization::global);
            help_output_hint(u8log_output_ul, u8"sign");
            help_output_hint(u8log_output_ul, u8"log");
            ::fast_io::io::perrln(u8log_output_ul, ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
            return ::uwsign::utils::cmdline::parameter_return_type::return_imme;
        }

        currp1->type = ::uwsign::utils::cmdline::parameter_parsing_results_type::occupied_arg;

        if(auto const currp1_str{currp1->str}; currp1_str == u8"all")
        {
            ::fast_io::io::perr(u8log_output_ul,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"Arguments:\n");
            help_output_all(u8log_output_ul);
            ::fast_io::io::perrln(u8log_output_ul);
        }
        else if(currp1_str == u8"global")
        {
            help_output_category_header(u8log_output_ul, u8"global");
            help_output_single_cate(u8log_output_ul, ::uwsign::utils::cmdline::categorization::global);
            ::fast_io::io::perrln(u8log_output_ul);
        }
        else if(currp1_str == u8"sign")
        {
            help_output_category_header(u8log_output_ul, u8"sign");
            help_output_single_cate(u8log_output_ul, ::uwsign::utils::cmdline::categorization::sign);
            ::fast_io::io::perrln(u8log_output_ul);
        }
        else if(currp1_str == u8"log")
        {
            help_output_category_header(u8log_output_ul, u8"log");
            help_output_single_cate(u8log_output_ul, ::uwsign::utils::cmdline::categorization::log);
            ::fast_io::io::perrln(u8log_output_ul);
        }
        else
        {
            ::fast_io::io::perr(u8log_output_ul,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"Invalid Extra Help Name \"",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_CYAN),
                                currp1_str,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"\". Usage: ",
                                ::uwsign::utils::cmdline::print_usage(::uwsign::uwsign::cmdline::params::help),
                                u8"\n\n");
            return ::uwsign::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        return ::uwsign::utils::cmdline::parameter_return_type::return_imme;
    }
}  // namespace uwsign::uwsign::cmdline::params::details

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
