/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        main.cc
 * @brief       main function for crt startup
 * @details     This function does nothing but call the cpp boot method of the other module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @date        2025-03-20
 * @copyright   APL-2.0 License
 */

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <uwsign/uwsign/crtmain/impl.h>
#endif

/// @brief      (crt) main func. The main function is a special function, but there are still meaningless [[gnu::used]].
/// @details    winnt avoid using int main(argc argv), use int main() directly to avoid wasting time parsing and transcoding ACP.
/// @param      argc Argument Count
/// @param      argv Argument Vector
/// @return     exit(3)
/// @see        ::uwsign::uwsign::uwsign_main_non_winnt()
UWSIGN_GNU_USED int main(
#if !((defined(_WIN32) && !defined(__CYGWIN__)) && !defined(_WIN32_WINDOWS))  // NOT WINNT
    int argc,
    char** argv
#endif
)
{
#if !((defined(_WIN32) && !defined(__CYGWIN__)) && !defined(_WIN32_WINDOWS))  // NOT WINNT
    return ::uwsign::uwsign::uwsign_main_non_winnt(argc, argv);
#else
    return ::uwsign::uwsign::uwsign_main_winnt();
#endif
}

#ifndef UWSIGN_MODULE
// This cpp may not be the end of the translation unit, it may be included in other cpp files. So it needs to be pop.
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
