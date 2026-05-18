/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-05-27
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <source_location>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/ansies/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::debug
{
    [[noreturn]] inline void trap_and_inform_bug_pos(::std::source_location loc = ::fast_io::mnp::cur_src_loc()) noexcept
    {
#ifdef UWSIGN
        ::fast_io::io::panic(::fast_io::u8err(),
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                             u8"uwsign: ",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_RED),
                             u8"[fatal] ",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8"There is a problem with the uwsign implementation: \n",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                             loc,
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8"\n\nuwsign: ",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_GREEN),
                             u8"[info]  ",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8"Please submit a bug report with version information (\"",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_PURPLE),
                             u8"uwsign --version",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8"\") and the configuration information (\"",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_PURPLE),
                             u8"xmake config -v",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8"\") in the issue at (",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_CYAN),
                             u8"https://github.com/UlteSoft/uwsign",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                             u8").\n\n",
                             ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
#else
        ::fast_io::io::panic(
            ::fast_io::u8err(),
            u8"uwsign: [fatal] There is a problem with the uwsign implementation: \n",
            loc,
            u8"\n\nuwsign: [info]  Please submit a bug report with version information (\"uwsign --version\") and the configuration information (\"xmake config -v\") in the issue at (https://github.com/UlteSoft/uwsign).\n\n");
#endif
    }
}

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
