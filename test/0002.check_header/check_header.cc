/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     1.0.0.0
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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <memory>

#include <uwsign/uwsign/crtmain/impl.h>

int main()
{
    /// @brief Check if all headers are popped out

#ifdef UWSIGN_DLLIMPORT
# error "UWSIGN_DLLIMPORT existed"
#endif

#ifdef UWSIGN_DLL_DLLIMPORT
# error "UWSIGN_DLL_DLLIMPORT existed"
#endif

#ifdef UWSIGN_HAS_CPP_ATTRIBUTE
# error "UWSIGN_HAS_CPP_ATTRIBUTE existed"
#endif

#ifdef UWSIGN_SUPPORT_INSTALL_PATH
# error "UWSIGN_SUPPORT_INSTALL_PATH existed"
#endif

#ifdef UWSIGN_SUPPORT_UNIX_PATH_SOCKET
# error "UWSIGN_SUPPORT_UNIX_PATH_SOCKET existed"
#endif

#ifdef UWSIGN_SUPPORT_PRELOAD_DL
# error "UWSIGN_SUPPORT_PRELOAD_DL existed"
#endif

#ifdef UWSIGN_SUPPORT_MMAP
# error "UWSIGN_SUPPORT_MMAP existed"
#endif

#ifdef UWSIGN_SUPPORT_WEAK_SYMBOL
# error "UWSIGN_SUPPORT_WEAK_SYMBOL existed"
#endif

#ifdef UWSIGN_COLOR_RST_ALL
# error "UWSIGN_COLOR_RST_ALL existed"
#endif

#ifdef UWSIGN_COLOR_U8_RST_ALL
# error "UWSIGN_COLOR_U8_RST_ALL existed"
#endif

#ifdef UWSIGN_AES_RST_ALL
# error "UWSIGN_AES_RST_ALL existed"
#endif

#ifdef UWSIGN_WIN32_TEXTATTR_RST_ALL
# error "UWSIGN_WIN32_TEXTATTR_RST_ALL existed"
#endif
}
