/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @copyright   APL-2.0 License
 */

/****************************************
 *  _   _ __        ____     __ __  __  *
 * | | | |\ \      / /\ \   / /|  \/  | *
 * | | | | \ \ /\ / /  \ \ / / | |\/| | *
 * | |_| |  \ V  V /    \ V /  | |  | | *
 *  \___/    \_/\_/      \_/   |_|  |_| *
 *                                      *
 ****************************************/

#pragma once

#ifndef UWSIGN_MODULE
// import
# include <fast_io.h>
# include <fast_io_device.h>
// macro
# include <uwsign/utils/macro/push_macros.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

#ifdef UWSIGN
UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::io
{
    /// @note Keep this file to warning switches that are actually used.
    ///       When a warning category needs independent control, add the pair
    ///       `show_<category>_warning` and `<category>_warning_fatal` here,
    ///       then wire both variables into the warning emission site.

    /// @brief warning control
    inline bool show_warning{true};  // [global]

    /// @brief warning fatal control
    inline bool warning_fatal{};  // [global]

}  // namespace uwsign::uwsign::io
#endif

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
