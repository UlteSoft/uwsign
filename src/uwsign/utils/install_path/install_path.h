/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-29
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// platform
# ifdef UWSIGN_SUPPORT_INSTALL_PATH
#  include <fast_io_driver/install_path.h>
# endif
// import
# include <fast_io.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

#ifdef UWSIGN_SUPPORT_INSTALL_PATH
UWSIGN_MODULE_EXPORT namespace uwsign::utils::install_path
{
    inline ::fast_io::install_path get_module_install_path_noexcept() noexcept
    {
        ::fast_io::install_path ret{};
# ifdef UWSIGN_CPP_EXCEPTIONS
        try
# endif
        {
            ret = ::fast_io::get_module_install_path();
        }
# ifdef UWSIGN_CPP_EXCEPTIONS
        catch(::fast_io::error)
        {
#  ifdef UWSIGN
            if(::uwsign::uwsign::io::show_warning)
            {
                ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                    u8"uwsign: ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_YELLOW),
                                    u8"[warn]  ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    u8"Cannot get install path. ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_ORANGE),
                                    u8"(sign)\n",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));

                if(::uwsign::uwsign::io::warning_fatal) [[unlikely]]
                {
                    ::fast_io::io::perr(::uwsign::uwsign::io::u8log_output,
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                        u8"uwsign: ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_RED),
                                        u8"[fatal] ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                        u8"Convert warnings to fatal errors. ",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_ORANGE),
                                        u8"(sign)\n\n",
                                        ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL));
                    ::fast_io::fast_terminate();
                }
            }
#  endif
        }
# endif
        return ret;
    }
}
#endif

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
