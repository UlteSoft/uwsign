/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        version.h
 * @brief       uwsign version command line parameter
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
        inline bool version_is_exist{};  // [global]
        inline constexpr ::uwsign::utils::container::array<::uwsign::utils::container::u8string_view, 2uz> version_alias{u8"-v", u8"-ver"};
#if defined(UWSIGN_MODULE)
        extern "C++"
#else
        inline constexpr
#endif
            ::uwsign::utils::cmdline::parameter_return_type version_callback(::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                             ::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                             ::uwsign::utils::cmdline::parameter_parsing_results*) noexcept;
    }  // namespace details

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wbraced-scalar-init"
#endif
    inline constexpr ::uwsign::utils::cmdline::parameter version{
        .name{u8"--version"},
        .describe{u8"Show version information."},
        .alias{::uwsign::utils::cmdline::kns_u8_str_scatter_t{details::version_alias.data(), details::version_alias.size()}},
        .handle{::std::addressof(details::version_callback)},
        .is_exist{::std::addressof(details::version_is_exist)},
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
