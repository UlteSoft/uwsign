/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        help.h
 * @brief       uwsign help command line parameter
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <memory>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/cmdline/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline::params
{
    namespace details
    {
        inline bool help_is_exist{};  // [global]
        inline constexpr ::uwsign::utils::container::u8string_view help_alias{u8"-h"};
#if defined(UWSIGN_MODULE)
        extern "C++"
#else
        inline constexpr
#endif
            ::uwsign::utils::cmdline::parameter_return_type help_callback(::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                          ::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                          ::uwsign::utils::cmdline::parameter_parsing_results*) noexcept;
    }  // namespace details

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wbraced-scalar-init"
#endif
    inline constexpr ::uwsign::utils::cmdline::parameter help{.name{u8"--help"},
                                                              .describe{u8"Show help information."},
                                                              .usage{u8"([all|global|sign|log])"},
                                                              .alias{::uwsign::utils::cmdline::kns_u8_str_scatter_t{::std::addressof(details::help_alias), 1uz}},
                                                              .handle{::std::addressof(details::help_callback)},
                                                              .is_exist{::std::addressof(details::help_is_exist)},
                                                              .cate{::uwsign::utils::cmdline::categorization::global}};
#if defined(__clang__)
# pragma clang diagnostic pop
#endif
}  // namespace uwsign::uwsign::cmdline::params

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
