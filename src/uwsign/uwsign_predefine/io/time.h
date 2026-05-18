/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-16
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
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

#ifdef UWSIGN

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::io
{
    // For verbose logging while preventing exceptions from being thrown.
    inline constexpr ::fast_io::iso8601_timestamp get_local_realtime() noexcept
    {
        ::fast_io::iso8601_timestamp local_realtime{};
# ifdef UWSIGN_CPP_EXCEPTIONS
        try
# endif
        {
            local_realtime = ::fast_io::local(::fast_io::posix_clock_gettime(::fast_io::posix_clock_id::realtime));
        }
# ifdef UWSIGN_CPP_EXCEPTIONS
        catch(::fast_io::error)
        {
            // keep default timestamp
        }
# endif

        return local_realtime;
    }
}  // uwsign::uwsign::io

#endif
