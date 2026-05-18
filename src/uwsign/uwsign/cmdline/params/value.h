/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        value.h
 * @brief       uwsign command line value parameter helpers
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <uwsign/utils/cmdline/impl.h>
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
        void required_value_pretreatment(char8_t const* const*&,
                                         char8_t const* const*,
                                         ::uwsign::utils::container::vector<::uwsign::utils::cmdline::parameter_parsing_results>&) noexcept;

#if defined(UWSIGN_MODULE)
    extern "C++"
#else
    inline constexpr
#endif
        ::uwsign::utils::cmdline::parameter_return_type required_value_callback(::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                                ::uwsign::utils::cmdline::parameter_parsing_results*,
                                                                                ::uwsign::utils::cmdline::parameter_parsing_results*) noexcept;
}  // namespace uwsign::uwsign::cmdline::params::details

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
