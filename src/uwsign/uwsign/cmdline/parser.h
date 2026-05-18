/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        parser.h
 * @brief       uwsign command line parser
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstddef>
# include <cstdint>
# include <memory>
# include <utility>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/cmdline/impl.h>
# include <uwsign/utils/debug/impl.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include "params.h"
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline
{
    enum class parsing_return_val : unsigned
    {
        def,
        return0,
        returnm1
    };

    // globals: command line parsing runs before worker threads are created.
    inline ::uwsign::utils::container::vector<::uwsign::utils::cmdline::parameter_parsing_results> parsing_result{};  // [global]
    inline char8_t const* argv0_dir{};                                                                                // [global]

    inline constexpr void print_error_prefix(auto&& stm) noexcept
    {
        ::fast_io::io::perr(::std::forward<decltype(stm)>(stm),
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                            u8"uwsign: ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                            u8"[error] ",
                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE));
    }

    inline constexpr parsing_return_val parsing(::std::size_t argc, char8_t const* const* argv) noexcept
    {
#ifdef UWSIGN_TIMER
        ::uwsign::utils::debug::timer parsing_timer{u8"parsing parameters"};
#endif

        auto& pr{parsing_result};
        auto const& ht{::uwsign::uwsign::cmdline::hash_table};

        pr.clear();
        pr.reserve(argc + 1uz);

        if(!argc) [[unlikely]]
        {
            ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                u8"No Parameters.",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                u8"\n\n");
            return parsing_return_val::returnm1;
        }

        auto curr_argv{argv};
        if(*curr_argv != nullptr) [[likely]]
        {
            pr.emplace_back_unchecked(::uwsign::utils::container::u8cstring_view{::fast_io::mnp::os_c_str(*curr_argv)},
                                      nullptr,
                                      ::uwsign::utils::cmdline::parameter_parsing_results_type::dir);
            argv0_dir = *curr_argv;
        }

        auto const argv_end{argv + argc};
        for(++curr_argv; curr_argv != argv_end;)
        {
            if(*curr_argv == nullptr) [[unlikely]]
            {
                ++curr_argv;
            }
            else if(::uwsign::utils::container::u8cstring_view const argv_str{::fast_io::mnp::os_c_str(*curr_argv)}; argv_str.empty()) [[unlikely]]
            {
                ++curr_argv;
            }
            else if(argv_str.front_unchecked() == u8'-')
            {
                auto const para{::uwsign::utils::cmdline::find_from_hash_table(ht, argv_str)};
                if(para == nullptr) [[unlikely]]
                {
                    pr.emplace_back_unchecked(argv_str, nullptr, ::uwsign::utils::cmdline::parameter_parsing_results_type::invalid_parameter);
                    ++curr_argv;
                }
                else [[likely]]
                {
                    if(para->is_exist)
                    {
                        if(auto& para_is_exist{*para->is_exist}; para_is_exist)
                        {
                            pr.emplace_back_unchecked(argv_str, para, ::uwsign::utils::cmdline::parameter_parsing_results_type::duplicate_parameter);
                        }
                        else
                        {
                            para_is_exist = true;
                            pr.emplace_back_unchecked(argv_str, para, ::uwsign::utils::cmdline::parameter_parsing_results_type::parameter);
                        }
                    }
                    else
                    {
                        pr.emplace_back_unchecked(argv_str, para, ::uwsign::utils::cmdline::parameter_parsing_results_type::parameter);
                    }

                    if(para->pretreatment)
                    {
                        para->pretreatment(curr_argv, argv_end, pr);
                    }
                    else
                    {
                        ++curr_argv;
                    }
                }
            }
            else
            {
                pr.emplace_back_unchecked(argv_str, nullptr, ::uwsign::utils::cmdline::parameter_parsing_results_type::arg);
                ++curr_argv;
            }
        }

        if(pr.size() == 1uz) [[unlikely]]
        {
            pr.emplace_back_unchecked(::uwsign::utils::container::u8cstring_view{u8"--help"},
                                      ::std::addressof(::uwsign::uwsign::cmdline::params::help),
                                      ::uwsign::utils::cmdline::parameter_parsing_results_type::parameter);
        }

        {
            auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
            ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
                ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
            auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

            bool shouldreturn{};

            for(auto curr_pr{pr.begin() + 1u}; curr_pr != pr.end(); ++curr_pr)
            {
                if(curr_pr->type == ::uwsign::utils::cmdline::parameter_parsing_results_type::invalid_parameter) [[unlikely]]
                {
                    shouldreturn = true;
                    print_error_prefix(u8log_output_ul);
                    ::fast_io::io::perr(u8log_output_ul,
                                        u8"invalid parameter: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_CYAN),
                                        curr_pr->str);

                    ::uwsign::utils::container::u8string_view f_test_str{};
                    ::std::size_t const str_size{curr_pr->str.size()};
                    constexpr ::std::size_t smax{::std::numeric_limits<::std::size_t>::max() / 4uz};
                    [[assume(str_size < smax)]];

                    ::std::size_t const test_size{str_size * 4uz / 10uz};
                    ::std::size_t f_test_size{test_size};

                    for(auto const& j: ::uwsign::uwsign::cmdline::parameter_lookup_table)
                    {
                        if(j.str.size() < str_size - f_test_size || j.str.size() > str_size + f_test_size) { continue; }

                        constexpr ::std::size_t shortest_path_stack_size{parameter_max_name_size + parameter_max_name_size * 4uz / 10uz + 1uz};
                        static_assert(shortest_path_stack_size > parameter_max_name_size, "addition overflow");

                        if(auto const dp_res{::uwsign::utils::cmdline::shortest_path<shortest_path_stack_size>(curr_pr->str.data(),
                                                                                                                curr_pr->str.size(),
                                                                                                                j.str.data(),
                                                                                                                j.str.size())};
                           dp_res <= test_size)
                        {
                            f_test_str = j.str;
                            f_test_size = dp_res;
                        }
                    }

                    if(f_test_str.empty())
                    {
                        ::fast_io::io::perr(u8log_output_ul, ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL), u8"\n");
                    }
                    else
                    {
                        ::fast_io::io::perr(u8log_output_ul,
                                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                            u8" (did you mean: ",
                                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_GREEN),
                                            f_test_str,
                                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                            u8")",
                                            ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                            u8"\n");
                    }
                }
                else if(curr_pr->type == ::uwsign::utils::cmdline::parameter_parsing_results_type::duplicate_parameter) [[unlikely]]
                {
                    shouldreturn = true;
                    print_error_prefix(u8log_output_ul);
                    ::fast_io::io::perr(u8log_output_ul,
                                        u8"duplicate parameter: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_CYAN),
                                        curr_pr->str,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                        u8"\n");
                }
            }

            if(shouldreturn) [[unlikely]]
            {
                ::fast_io::io::perrln(u8log_output_ul);
                return parsing_return_val::returnm1;
            }
        }

        {
            bool needexit{};
            bool needterminal{};

            for(auto curr_pr{pr.begin() + 1u}; curr_pr != pr.end(); ++curr_pr)
            {
                auto const cp{curr_pr->para};
                if(cp == nullptr) { continue; }

                if(auto const cb{cp->handle}; cb != nullptr)
                {
                    auto const res{cb(pr.begin(), curr_pr, pr.end())};

                    switch(res)
                    {
                        case ::uwsign::utils::cmdline::parameter_return_type::def: break;
                        case ::uwsign::utils::cmdline::parameter_return_type::return_m1_imme: return parsing_return_val::returnm1;
                        case ::uwsign::utils::cmdline::parameter_return_type::return_imme: return parsing_return_val::return0;
                        case ::uwsign::utils::cmdline::parameter_return_type::return_soon:
                        {
                            needexit = true;
                            break;
                        }
                        case ::uwsign::utils::cmdline::parameter_return_type::err_imme: ::fast_io::fast_terminate();
                        case ::uwsign::utils::cmdline::parameter_return_type::err_soon:
                        {
                            needterminal = true;
                            break;
                        }
                        [[unlikely]] default:
                        {
#if (defined(_DEBUG) || defined(DEBUG)) && defined(UWSIGN_ENABLE_DETAILED_DEBUG_CHECK)
                            ::uwsign::utils::debug::trap_and_inform_bug_pos();
#endif
                            ::std::unreachable();
                        }
                    }
                }
            }

            if(needterminal) [[unlikely]] { ::fast_io::fast_terminate(); }
            if(needexit) [[unlikely]] { return parsing_return_val::returnm1; }
        }

        {
            auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
            ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
                ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
            auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

            bool shouldreturn{};

            for(auto curr_pr{pr.begin() + 1u}; curr_pr != pr.end(); ++curr_pr)
            {
                if(curr_pr->type == ::uwsign::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
                {
                    shouldreturn = true;
                    print_error_prefix(u8log_output_ul);
                    ::fast_io::io::perr(u8log_output_ul,
                                        u8"invalid option: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_CYAN),
                                        curr_pr->str,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                        u8"\n");
                }
            }

            if(shouldreturn) [[unlikely]]
            {
                ::fast_io::io::perrln(u8log_output_ul);
                return parsing_return_val::returnm1;
            }
        }

        return parsing_return_val::def;
    }
}  // namespace uwsign::uwsign::cmdline

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
