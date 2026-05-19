/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        sign_replace.h
 * @brief       uwsign replace signature command line parameter
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
        inline bool sign_replace_is_exist{};  // [global]
    }

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wbraced-scalar-init"
#endif
    inline constexpr ::uwsign::utils::cmdline::parameter sign_replace{
        .name{u8"--replace"},
        .describe{u8"Replace existing wasm_uwsign sections instead of appending."},
        .is_exist{::std::addressof(details::sign_replace_is_exist)},
        .cate{::uwsign::utils::cmdline::categorization::sign}};
#if defined(__clang__)
# pragma clang diagnostic pop
#endif
}  // namespace uwsign::uwsign::cmdline::params

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
