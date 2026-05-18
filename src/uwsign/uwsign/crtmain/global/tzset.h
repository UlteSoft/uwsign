/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        tzset.h
 * @brief       timezone setup guard for uwsign startup
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::global
{
    /// @brief Declare this in crtmain startup to initialize timezone data.
    struct tz_set_s
    {
        UWSIGN_GNU_COLD inline tz_set_s() noexcept
        { ::fast_io::posix_tzset(); }
    };
}  // namespace uwsign::uwsign::global

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
