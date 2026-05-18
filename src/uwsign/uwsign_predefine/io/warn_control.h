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
    /// @brief warning control
    inline bool show_warning{true};              // [global]
    inline bool show_sign_warning{true};         // [global]
    inline bool show_input_warning{true};        // [global]
    inline bool show_output_warning{true};       // [global]
    inline bool show_format_warning{true};       // [global]
    inline bool show_path_warning{true};         // [global]
    inline bool show_file_warning{true};         // [global]
    inline bool show_key_warning{true};          // [global]
    inline bool show_certificate_warning{true};  // [global]
    inline bool show_signature_warning{true};    // [global]
    inline bool show_timestamp_warning{true};    // [global]

    /// @brief warning fatal control
    inline bool warning_fatal{};              // [global]
    inline bool sign_warning_fatal{};         // [global]
    inline bool input_warning_fatal{};        // [global]
    inline bool output_warning_fatal{};       // [global]
    inline bool format_warning_fatal{};       // [global]
    inline bool path_warning_fatal{};         // [global]
    inline bool file_warning_fatal{};         // [global]
    inline bool key_warning_fatal{};          // [global]
    inline bool certificate_warning_fatal{};  // [global]
    inline bool signature_warning_fatal{};    // [global]
    inline bool timestamp_warning_fatal{};    // [global]

}  // namespace uwsign::uwsign::io
#endif

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
