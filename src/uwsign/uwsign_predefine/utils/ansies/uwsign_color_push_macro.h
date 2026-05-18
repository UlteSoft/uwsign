/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-24
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

/// @brief      The following are the macros used by ansi escape sequences.
/// @details    Use `push_macro` to avoid side effects on existing macros. Please use `pop_macro` in conjunction.

// #pragma once
#ifdef UWSIGN

# include <uwsign/utils/ansies/ansi_push_macro.h>
# include <uwsign/utils/ansies/win32_text_attr_push_macro.h>
///
/// CHAR
///
# pragma push_macro("UWSIGN_COLOR_RST_ALL")
# undef UWSIGN_COLOR_RST_ALL
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_RST_ALL ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_RST_ALL, UWSIGN_WIN32_TEXTATTR_RST_ALL)
# else
#  define UWSIGN_COLOR_RST_ALL UWSIGN_AES_RST_ALL
# endif

# pragma push_macro("UWSIGN_COLOR_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_COLOR_RST_ALL_AND_SET_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_RST_ALL_AND_SET_WHITE                                                                                                                     \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_RST_ALL UWSIGN_AES_WHITE, UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE)
# else
#  define UWSIGN_COLOR_RST_ALL_AND_SET_WHITE UWSIGN_AES_RST_ALL UWSIGN_AES_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_COLOR_RST_ALL_AND_SET_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_RST_ALL_AND_SET_PURPLE                                                                                                                    \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_RST_ALL UWSIGN_AES_PURPLE, UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE)
# else
#  define UWSIGN_COLOR_RST_ALL_AND_SET_PURPLE UWSIGN_AES_RST_ALL UWSIGN_AES_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_BLACK")
# undef UWSIGN_COLOR_BLACK
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_BLACK ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_BLACK, UWSIGN_WIN32_TEXTATTR_BLACK)
# else
#  define UWSIGN_COLOR_BLACK UWSIGN_AES_BLACK
# endif

# pragma push_macro("UWSIGN_COLOR_RED")
# undef UWSIGN_COLOR_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_RED, UWSIGN_WIN32_TEXTATTR_RED)
# else
#  define UWSIGN_COLOR_RED UWSIGN_AES_RED
# endif

# pragma push_macro("UWSIGN_COLOR_GREEN")
# undef UWSIGN_COLOR_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_GREEN, UWSIGN_WIN32_TEXTATTR_GREEN)
# else
#  define UWSIGN_COLOR_GREEN UWSIGN_AES_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_ORANGE")
# undef UWSIGN_COLOR_ORANGE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_ORANGE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_ORANGE, UWSIGN_WIN32_TEXTATTR_ORANGE)
# else
#  define UWSIGN_COLOR_ORANGE UWSIGN_AES_ORANGE
# endif

# pragma push_macro("UWSIGN_COLOR_BLUE")
# undef UWSIGN_COLOR_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_BLUE, UWSIGN_WIN32_TEXTATTR_BLUE)
# else
#  define UWSIGN_COLOR_BLUE UWSIGN_AES_BLUE
# endif
# pragma push_macro("UWSIGN_COLOR_PURPLE")
# undef UWSIGN_COLOR_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_PURPLE, UWSIGN_WIN32_TEXTATTR_PURPLE)
# else
#  define UWSIGN_COLOR_PURPLE UWSIGN_AES_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_CYAN")
# undef UWSIGN_COLOR_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_CYAN, UWSIGN_WIN32_TEXTATTR_CYAN)
# else
#  define UWSIGN_COLOR_CYAN UWSIGN_AES_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_GRAY")
# undef UWSIGN_COLOR_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_GRAY, UWSIGN_WIN32_TEXTATTR_GRAY)
# else
#  define UWSIGN_COLOR_GRAY UWSIGN_AES_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_DK_GRAY")
# undef UWSIGN_COLOR_DK_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_DK_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_DK_GRAY, UWSIGN_WIN32_TEXTATTR_DK_GRAY)
# else
#  define UWSIGN_COLOR_DK_GRAY UWSIGN_AES_DK_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_LT_RED")
# undef UWSIGN_COLOR_LT_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_LT_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_LT_RED, UWSIGN_WIN32_TEXTATTR_LT_RED)
# else
#  define UWSIGN_COLOR_LT_RED UWSIGN_AES_LT_RED
# endif

# pragma push_macro("UWSIGN_COLOR_LT_GREEN")
# undef UWSIGN_COLOR_LT_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_LT_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_LT_GREEN, UWSIGN_WIN32_TEXTATTR_LT_GREEN)
# else
#  define UWSIGN_COLOR_LT_GREEN UWSIGN_AES_LT_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_YELLOW")
# undef UWSIGN_COLOR_YELLOW
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_YELLOW ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_YELLOW, UWSIGN_WIN32_TEXTATTR_YELLOW)
# else
#  define UWSIGN_COLOR_YELLOW UWSIGN_AES_YELLOW
# endif

# pragma push_macro("UWSIGN_COLOR_LT_BLUE")
# undef UWSIGN_COLOR_LT_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_LT_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_LT_BLUE, UWSIGN_WIN32_TEXTATTR_LT_BLUE)
# else
#  define UWSIGN_COLOR_LT_BLUE UWSIGN_AES_LT_BLUE
# endif

# pragma push_macro("UWSIGN_COLOR_LT_PURPLE")
# undef UWSIGN_COLOR_LT_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_LT_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_LT_PURPLE, UWSIGN_WIN32_TEXTATTR_LT_PURPLE)
# else
#  define UWSIGN_COLOR_LT_PURPLE UWSIGN_AES_LT_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_LT_CYAN")
# undef UWSIGN_COLOR_LT_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_LT_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_LT_CYAN, UWSIGN_WIN32_TEXTATTR_LT_CYAN)
# else
#  define UWSIGN_COLOR_LT_CYAN UWSIGN_AES_LT_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_WHITE")
# undef UWSIGN_COLOR_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_WHITE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_WHITE, UWSIGN_WIN32_TEXTATTR_WHITE)
# else
#  define UWSIGN_COLOR_WHITE UWSIGN_AES_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_RGB")
# undef UWSIGN_COLOR_RGB
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_RGB(r, g, b) ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_RGB(r, g, b))
# else
#  define UWSIGN_COLOR_RGB(r, g, b) UWSIGN_AES_RGB(r, g, b)
# endif

///
/// WCHAR
///
# pragma push_macro("UWSIGN_COLOR_W_RST_ALL")
# undef UWSIGN_COLOR_W_RST_ALL
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_RST_ALL ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_RST_ALL, UWSIGN_WIN32_TEXTATTR_RST_ALL)
# else
#  define UWSIGN_COLOR_W_RST_ALL UWSIGN_AES_W_RST_ALL
# endif

# pragma push_macro("UWSIGN_COLOR_W_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_COLOR_W_RST_ALL_AND_SET_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_RST_ALL_AND_SET_WHITE                                                                                                                   \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_RST_ALL UWSIGN_AES_W_WHITE, UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE)
# else
#  define UWSIGN_COLOR_W_RST_ALL_AND_SET_WHITE UWSIGN_AES_W_RST_ALL UWSIGN_AES_W_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_W_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_COLOR_W_RST_ALL_AND_SET_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_RST_ALL_AND_SET_PURPLE                                                                                                                  \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_RST_ALL UWSIGN_AES_W_PURPLE, UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE)
# else
#  define UWSIGN_COLOR_W_RST_ALL_AND_SET_PURPLE UWSIGN_AES_W_RST_ALL UWSIGN_AES_W_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_W_BLACK")
# undef UWSIGN_COLOR_W_BLACK
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_BLACK ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_BLACK, UWSIGN_WIN32_TEXTATTR_BLACK)
# else
#  define UWSIGN_COLOR_W_BLACK UWSIGN_AES_W_BLACK
# endif

# pragma push_macro("UWSIGN_COLOR_W_RED")
# undef UWSIGN_COLOR_W_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_RED, UWSIGN_WIN32_TEXTATTR_RED)
# else
#  define UWSIGN_COLOR_W_RED UWSIGN_AES_W_RED
# endif

# pragma push_macro("UWSIGN_COLOR_W_GREEN")
# undef UWSIGN_COLOR_W_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_GREEN, UWSIGN_WIN32_TEXTATTR_GREEN)
# else
#  define UWSIGN_COLOR_W_GREEN UWSIGN_AES_W_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_W_ORANGE")
# undef UWSIGN_COLOR_W_ORANGE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_ORANGE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_ORANGE, UWSIGN_WIN32_TEXTATTR_ORANGE)
# else
#  define UWSIGN_COLOR_W_ORANGE UWSIGN_AES_W_ORANGE
# endif

# pragma push_macro("UWSIGN_COLOR_W_BLUE")
# undef UWSIGN_COLOR_W_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_BLUE, UWSIGN_WIN32_TEXTATTR_BLUE)
# else
#  define UWSIGN_COLOR_W_BLUE UWSIGN_AES_W_BLUE
# endif
# pragma push_macro("UWSIGN_COLOR_W_PURPLE")
# undef UWSIGN_COLOR_W_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_PURPLE, UWSIGN_WIN32_TEXTATTR_PURPLE)
# else
#  define UWSIGN_COLOR_W_PURPLE UWSIGN_AES_W_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_W_CYAN")
# undef UWSIGN_COLOR_W_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_CYAN, UWSIGN_WIN32_TEXTATTR_CYAN)
# else
#  define UWSIGN_COLOR_W_CYAN UWSIGN_AES_W_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_W_GRAY")
# undef UWSIGN_COLOR_W_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_GRAY, UWSIGN_WIN32_TEXTATTR_GRAY)
# else
#  define UWSIGN_COLOR_W_GRAY UWSIGN_AES_W_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_W_DK_GRAY")
# undef UWSIGN_COLOR_W_DK_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_DK_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_DK_GRAY, UWSIGN_WIN32_TEXTATTR_DK_GRAY)
# else
#  define UWSIGN_COLOR_W_DK_GRAY UWSIGN_AES_W_DK_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_W_LT_RED")
# undef UWSIGN_COLOR_W_LT_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_LT_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_LT_RED, UWSIGN_WIN32_TEXTATTR_LT_RED)
# else
#  define UWSIGN_COLOR_W_LT_RED UWSIGN_AES_W_LT_RED
# endif

# pragma push_macro("UWSIGN_COLOR_W_LT_GREEN")
# undef UWSIGN_COLOR_W_LT_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_LT_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_LT_GREEN, UWSIGN_WIN32_TEXTATTR_LT_GREEN)
# else
#  define UWSIGN_COLOR_W_LT_GREEN UWSIGN_AES_W_LT_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_W_YELLOW")
# undef UWSIGN_COLOR_W_YELLOW
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_YELLOW ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_YELLOW, UWSIGN_WIN32_TEXTATTR_YELLOW)
# else
#  define UWSIGN_COLOR_W_YELLOW UWSIGN_AES_W_YELLOW
# endif

# pragma push_macro("UWSIGN_COLOR_W_LT_BLUE")
# undef UWSIGN_COLOR_W_LT_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_LT_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_LT_BLUE, UWSIGN_WIN32_TEXTATTR_LT_BLUE)
# else
#  define UWSIGN_COLOR_W_LT_BLUE UWSIGN_AES_W_LT_BLUE
# endif

# pragma push_macro("UWSIGN_COLOR_W_LT_PURPLE")
# undef UWSIGN_COLOR_W_LT_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_LT_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_LT_PURPLE, UWSIGN_WIN32_TEXTATTR_LT_PURPLE)
# else
#  define UWSIGN_COLOR_W_LT_PURPLE UWSIGN_AES_W_LT_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_W_LT_CYAN")
# undef UWSIGN_COLOR_W_LT_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_LT_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_LT_CYAN, UWSIGN_WIN32_TEXTATTR_LT_CYAN)
# else
#  define UWSIGN_COLOR_W_LT_CYAN UWSIGN_AES_W_LT_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_W_WHITE")
# undef UWSIGN_COLOR_W_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_WHITE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_WHITE, UWSIGN_WIN32_TEXTATTR_WHITE)
# else
#  define UWSIGN_COLOR_W_WHITE UWSIGN_AES_W_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_W_RGB")
# undef UWSIGN_COLOR_W_RGB
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_W_RGB(r, g, b) ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_W_RGB(r, g, b))
# else
#  define UWSIGN_COLOR_W_RGB(r, g, b) UWSIGN_AES_W_RGB(r, g, b)
# endif

///
/// UTF-8
///
# pragma push_macro("UWSIGN_COLOR_U8_RST_ALL")
# undef UWSIGN_COLOR_U8_RST_ALL
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_RST_ALL ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_RST_ALL, UWSIGN_WIN32_TEXTATTR_RST_ALL)
# else
#  define UWSIGN_COLOR_U8_RST_ALL UWSIGN_AES_U8_RST_ALL
# endif

# pragma push_macro("UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE                                                                                                                  \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_RST_ALL UWSIGN_AES_U8_WHITE, UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE)
# else
#  define UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE UWSIGN_AES_U8_RST_ALL UWSIGN_AES_U8_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_COLOR_U8_RST_ALL_AND_SET_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_RST_ALL_AND_SET_PURPLE                                                                                                                 \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b,                                                                                 \
                           UWSIGN_AES_U8_RST_ALL UWSIGN_AES_U8_PURPLE,                                                                                             \
                           UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE)
# else
#  define UWSIGN_COLOR_U8_RST_ALL_AND_SET_PURPLE UWSIGN_AES_U8_RST_ALL UWSIGN_AES_U8_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_BLACK")
# undef UWSIGN_COLOR_U8_BLACK
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_BLACK ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_BLACK, UWSIGN_WIN32_TEXTATTR_BLACK)
# else
#  define UWSIGN_COLOR_U8_BLACK UWSIGN_AES_U8_BLACK
# endif

# pragma push_macro("UWSIGN_COLOR_U8_RED")
# undef UWSIGN_COLOR_U8_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_RED, UWSIGN_WIN32_TEXTATTR_RED)
# else
#  define UWSIGN_COLOR_U8_RED UWSIGN_AES_U8_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U8_GREEN")
# undef UWSIGN_COLOR_U8_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_GREEN, UWSIGN_WIN32_TEXTATTR_GREEN)
# else
#  define UWSIGN_COLOR_U8_GREEN UWSIGN_AES_U8_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U8_ORANGE")
# undef UWSIGN_COLOR_U8_ORANGE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_ORANGE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_ORANGE, UWSIGN_WIN32_TEXTATTR_ORANGE)
# else
#  define UWSIGN_COLOR_U8_ORANGE UWSIGN_AES_U8_ORANGE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_BLUE")
# undef UWSIGN_COLOR_U8_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_BLUE, UWSIGN_WIN32_TEXTATTR_BLUE)
# else
#  define UWSIGN_COLOR_U8_BLUE UWSIGN_AES_U8_BLUE
# endif
# pragma push_macro("UWSIGN_COLOR_U8_PURPLE")
# undef UWSIGN_COLOR_U8_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_PURPLE, UWSIGN_WIN32_TEXTATTR_PURPLE)
# else
#  define UWSIGN_COLOR_U8_PURPLE UWSIGN_AES_U8_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_CYAN")
# undef UWSIGN_COLOR_U8_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_CYAN, UWSIGN_WIN32_TEXTATTR_CYAN)
# else
#  define UWSIGN_COLOR_U8_CYAN UWSIGN_AES_U8_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U8_GRAY")
# undef UWSIGN_COLOR_U8_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_GRAY, UWSIGN_WIN32_TEXTATTR_GRAY)
# else
#  define UWSIGN_COLOR_U8_GRAY UWSIGN_AES_U8_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U8_DK_GRAY")
# undef UWSIGN_COLOR_U8_DK_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_DK_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_DK_GRAY, UWSIGN_WIN32_TEXTATTR_DK_GRAY)
# else
#  define UWSIGN_COLOR_U8_DK_GRAY UWSIGN_AES_U8_DK_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U8_LT_RED")
# undef UWSIGN_COLOR_U8_LT_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_LT_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_LT_RED, UWSIGN_WIN32_TEXTATTR_LT_RED)
# else
#  define UWSIGN_COLOR_U8_LT_RED UWSIGN_AES_U8_LT_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U8_LT_GREEN")
# undef UWSIGN_COLOR_U8_LT_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_LT_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_LT_GREEN, UWSIGN_WIN32_TEXTATTR_LT_GREEN)
# else
#  define UWSIGN_COLOR_U8_LT_GREEN UWSIGN_AES_U8_LT_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U8_YELLOW")
# undef UWSIGN_COLOR_U8_YELLOW
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_YELLOW ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_YELLOW, UWSIGN_WIN32_TEXTATTR_YELLOW)
# else
#  define UWSIGN_COLOR_U8_YELLOW UWSIGN_AES_U8_YELLOW
# endif

# pragma push_macro("UWSIGN_COLOR_U8_LT_BLUE")
# undef UWSIGN_COLOR_U8_LT_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_LT_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_LT_BLUE, UWSIGN_WIN32_TEXTATTR_LT_BLUE)
# else
#  define UWSIGN_COLOR_U8_LT_BLUE UWSIGN_AES_U8_LT_BLUE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_LT_PURPLE")
# undef UWSIGN_COLOR_U8_LT_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_LT_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_LT_PURPLE, UWSIGN_WIN32_TEXTATTR_LT_PURPLE)
# else
#  define UWSIGN_COLOR_U8_LT_PURPLE UWSIGN_AES_U8_LT_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_LT_CYAN")
# undef UWSIGN_COLOR_U8_LT_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_LT_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_LT_CYAN, UWSIGN_WIN32_TEXTATTR_LT_CYAN)
# else
#  define UWSIGN_COLOR_U8_LT_CYAN UWSIGN_AES_U8_LT_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U8_WHITE")
# undef UWSIGN_COLOR_U8_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_WHITE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_WHITE, UWSIGN_WIN32_TEXTATTR_WHITE)
# else
#  define UWSIGN_COLOR_U8_WHITE UWSIGN_AES_U8_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U8_RGB")
# undef UWSIGN_COLOR_U8_RGB
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U8_RGB(r, g, b) ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U8_RGB(r, g, b))
# else
#  define UWSIGN_COLOR_U8_RGB(r, g, b) UWSIGN_AES_U8_RGB(r, g, b)
# endif

///
/// UTF-16
///
# pragma push_macro("UWSIGN_COLOR_U16_RST_ALL")
# undef UWSIGN_COLOR_U16_RST_ALL
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_RST_ALL ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_RST_ALL, UWSIGN_WIN32_TEXTATTR_RST_ALL)
# else
#  define UWSIGN_COLOR_U16_RST_ALL UWSIGN_AES_U16_RST_ALL
# endif

# pragma push_macro("UWSIGN_COLOR_U16_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_COLOR_U16_RST_ALL_AND_SET_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_RST_ALL_AND_SET_WHITE                                                                                                                 \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b,                                                                                 \
                           UWSIGN_AES_U16_RST_ALL UWSIGN_AES_U16_WHITE,                                                                                            \
                           UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE)
# else
#  define UWSIGN_COLOR_U16_RST_ALL_AND_SET_WHITE UWSIGN_AES_U16_RST_ALL UWSIGN_AES_U16_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_COLOR_U16_RST_ALL_AND_SET_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_RST_ALL_AND_SET_PURPLE                                                                                                                \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b,                                                                                 \
                           UWSIGN_AES_U16_RST_ALL UWSIGN_AES_U16_PURPLE,                                                                                           \
                           UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE)
# else
#  define UWSIGN_COLOR_U16_RST_ALL_AND_SET_PURPLE UWSIGN_AES_U16_RST_ALL UWSIGN_AES_U16_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_BLACK")
# undef UWSIGN_COLOR_U16_BLACK
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_BLACK ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_BLACK, UWSIGN_WIN32_TEXTATTR_BLACK)
# else
#  define UWSIGN_COLOR_U16_BLACK UWSIGN_AES_U16_BLACK
# endif

# pragma push_macro("UWSIGN_COLOR_U16_RED")
# undef UWSIGN_COLOR_U16_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_RED, UWSIGN_WIN32_TEXTATTR_RED)
# else
#  define UWSIGN_COLOR_U16_RED UWSIGN_AES_U16_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U16_GREEN")
# undef UWSIGN_COLOR_U16_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_GREEN, UWSIGN_WIN32_TEXTATTR_GREEN)
# else
#  define UWSIGN_COLOR_U16_GREEN UWSIGN_AES_U16_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U16_ORANGE")
# undef UWSIGN_COLOR_U16_ORANGE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_ORANGE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_ORANGE, UWSIGN_WIN32_TEXTATTR_ORANGE)
# else
#  define UWSIGN_COLOR_U16_ORANGE UWSIGN_AES_U16_ORANGE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_BLUE")
# undef UWSIGN_COLOR_U16_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_BLUE, UWSIGN_WIN32_TEXTATTR_BLUE)
# else
#  define UWSIGN_COLOR_U16_BLUE UWSIGN_AES_U16_BLUE
# endif
# pragma push_macro("UWSIGN_COLOR_U16_PURPLE")
# undef UWSIGN_COLOR_U16_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_PURPLE, UWSIGN_WIN32_TEXTATTR_PURPLE)
# else
#  define UWSIGN_COLOR_U16_PURPLE UWSIGN_AES_U16_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_CYAN")
# undef UWSIGN_COLOR_U16_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_CYAN, UWSIGN_WIN32_TEXTATTR_CYAN)
# else
#  define UWSIGN_COLOR_U16_CYAN UWSIGN_AES_U16_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U16_GRAY")
# undef UWSIGN_COLOR_U16_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_GRAY, UWSIGN_WIN32_TEXTATTR_GRAY)
# else
#  define UWSIGN_COLOR_U16_GRAY UWSIGN_AES_U16_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U16_DK_GRAY")
# undef UWSIGN_COLOR_U16_DK_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_DK_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_DK_GRAY, UWSIGN_WIN32_TEXTATTR_DK_GRAY)
# else
#  define UWSIGN_COLOR_U16_DK_GRAY UWSIGN_AES_U16_DK_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U16_LT_RED")
# undef UWSIGN_COLOR_U16_LT_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_LT_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_LT_RED, UWSIGN_WIN32_TEXTATTR_LT_RED)
# else
#  define UWSIGN_COLOR_U16_LT_RED UWSIGN_AES_U16_LT_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U16_LT_GREEN")
# undef UWSIGN_COLOR_U16_LT_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_LT_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_LT_GREEN, UWSIGN_WIN32_TEXTATTR_LT_GREEN)
# else
#  define UWSIGN_COLOR_U16_LT_GREEN UWSIGN_AES_U16_LT_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U16_YELLOW")
# undef UWSIGN_COLOR_U16_YELLOW
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_YELLOW ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_YELLOW, UWSIGN_WIN32_TEXTATTR_YELLOW)
# else
#  define UWSIGN_COLOR_U16_YELLOW UWSIGN_AES_U16_YELLOW
# endif

# pragma push_macro("UWSIGN_COLOR_U16_LT_BLUE")
# undef UWSIGN_COLOR_U16_LT_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_LT_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_LT_BLUE, UWSIGN_WIN32_TEXTATTR_LT_BLUE)
# else
#  define UWSIGN_COLOR_U16_LT_BLUE UWSIGN_AES_U16_LT_BLUE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_LT_PURPLE")
# undef UWSIGN_COLOR_U16_LT_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_LT_PURPLE                                                                                                                             \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_LT_PURPLE, UWSIGN_WIN32_TEXTATTR_LT_PURPLE)
# else
#  define UWSIGN_COLOR_U16_LT_PURPLE UWSIGN_AES_U16_LT_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_LT_CYAN")
# undef UWSIGN_COLOR_U16_LT_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_LT_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_LT_CYAN, UWSIGN_WIN32_TEXTATTR_LT_CYAN)
# else
#  define UWSIGN_COLOR_U16_LT_CYAN UWSIGN_AES_U16_LT_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U16_WHITE")
# undef UWSIGN_COLOR_U16_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_WHITE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_WHITE, UWSIGN_WIN32_TEXTATTR_WHITE)
# else
#  define UWSIGN_COLOR_U16_WHITE UWSIGN_AES_U16_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U16_RGB")
# undef UWSIGN_COLOR_U16_RGB
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U16_RGB(r, g, b) ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U16_RGB(r, g, b))
# else
#  define UWSIGN_COLOR_U16_RGB(r, g, b) UWSIGN_AES_U16_RGB(r, g, b)
# endif

///
/// UTF-32
///
# pragma push_macro("UWSIGN_COLOR_U32_RST_ALL")
# undef UWSIGN_COLOR_U32_RST_ALL
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_RST_ALL ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_RST_ALL, UWSIGN_WIN32_TEXTATTR_RST_ALL)
# else
#  define UWSIGN_COLOR_U32_RST_ALL UWSIGN_AES_U32_RST_ALL
# endif

# pragma push_macro("UWSIGN_COLOR_U32_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_COLOR_U32_RST_ALL_AND_SET_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_RST_ALL_AND_SET_WHITE                                                                                                                 \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b,                                                                                 \
                           UWSIGN_AES_U32_RST_ALL UWSIGN_AES_U32_WHITE,                                                                                            \
                           UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE)
# else
#  define UWSIGN_COLOR_U32_RST_ALL_AND_SET_WHITE UWSIGN_AES_U32_RST_ALL UWSIGN_AES_U32_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_COLOR_U32_RST_ALL_AND_SET_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_RST_ALL_AND_SET_PURPLE                                                                                                                \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b,                                                                                 \
                           UWSIGN_AES_U32_RST_ALL UWSIGN_AES_U32_PURPLE,                                                                                           \
                           UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE)
# else
#  define UWSIGN_COLOR_U32_RST_ALL_AND_SET_PURPLE UWSIGN_AES_U32_RST_ALL UWSIGN_AES_U32_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_BLACK")
# undef UWSIGN_COLOR_U32_BLACK
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_BLACK ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_BLACK, UWSIGN_WIN32_TEXTATTR_BLACK)
# else
#  define UWSIGN_COLOR_U32_BLACK UWSIGN_AES_U32_BLACK
# endif

# pragma push_macro("UWSIGN_COLOR_U32_RED")
# undef UWSIGN_COLOR_U32_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_RED, UWSIGN_WIN32_TEXTATTR_RED)
# else
#  define UWSIGN_COLOR_U32_RED UWSIGN_AES_U32_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U32_GREEN")
# undef UWSIGN_COLOR_U32_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_GREEN, UWSIGN_WIN32_TEXTATTR_GREEN)
# else
#  define UWSIGN_COLOR_U32_GREEN UWSIGN_AES_U32_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U32_ORANGE")
# undef UWSIGN_COLOR_U32_ORANGE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_ORANGE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_ORANGE, UWSIGN_WIN32_TEXTATTR_ORANGE)
# else
#  define UWSIGN_COLOR_U32_ORANGE UWSIGN_AES_U32_ORANGE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_BLUE")
# undef UWSIGN_COLOR_U32_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_BLUE, UWSIGN_WIN32_TEXTATTR_BLUE)
# else
#  define UWSIGN_COLOR_U32_BLUE UWSIGN_AES_U32_BLUE
# endif
# pragma push_macro("UWSIGN_COLOR_U32_PURPLE")
# undef UWSIGN_COLOR_U32_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_PURPLE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_PURPLE, UWSIGN_WIN32_TEXTATTR_PURPLE)
# else
#  define UWSIGN_COLOR_U32_PURPLE UWSIGN_AES_U32_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_CYAN")
# undef UWSIGN_COLOR_U32_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_CYAN, UWSIGN_WIN32_TEXTATTR_CYAN)
# else
#  define UWSIGN_COLOR_U32_CYAN UWSIGN_AES_U32_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U32_GRAY")
# undef UWSIGN_COLOR_U32_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_GRAY, UWSIGN_WIN32_TEXTATTR_GRAY)
# else
#  define UWSIGN_COLOR_U32_GRAY UWSIGN_AES_U32_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U32_DK_GRAY")
# undef UWSIGN_COLOR_U32_DK_GRAY
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_DK_GRAY ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_DK_GRAY, UWSIGN_WIN32_TEXTATTR_DK_GRAY)
# else
#  define UWSIGN_COLOR_U32_DK_GRAY UWSIGN_AES_U32_DK_GRAY
# endif

# pragma push_macro("UWSIGN_COLOR_U32_LT_RED")
# undef UWSIGN_COLOR_U32_LT_RED
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_LT_RED ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_LT_RED, UWSIGN_WIN32_TEXTATTR_LT_RED)
# else
#  define UWSIGN_COLOR_U32_LT_RED UWSIGN_AES_U32_LT_RED
# endif

# pragma push_macro("UWSIGN_COLOR_U32_LT_GREEN")
# undef UWSIGN_COLOR_U32_LT_GREEN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_LT_GREEN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_LT_GREEN, UWSIGN_WIN32_TEXTATTR_LT_GREEN)
# else
#  define UWSIGN_COLOR_U32_LT_GREEN UWSIGN_AES_U32_LT_GREEN
# endif

# pragma push_macro("UWSIGN_COLOR_U32_YELLOW")
# undef UWSIGN_COLOR_U32_YELLOW
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_YELLOW ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_YELLOW, UWSIGN_WIN32_TEXTATTR_YELLOW)
# else
#  define UWSIGN_COLOR_U32_YELLOW UWSIGN_AES_U32_YELLOW
# endif

# pragma push_macro("UWSIGN_COLOR_U32_LT_BLUE")
# undef UWSIGN_COLOR_U32_LT_BLUE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_LT_BLUE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_LT_BLUE, UWSIGN_WIN32_TEXTATTR_LT_BLUE)
# else
#  define UWSIGN_COLOR_U32_LT_BLUE UWSIGN_AES_U32_LT_BLUE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_LT_PURPLE")
# undef UWSIGN_COLOR_U32_LT_PURPLE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_LT_PURPLE                                                                                                                             \
      ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_LT_PURPLE, UWSIGN_WIN32_TEXTATTR_LT_PURPLE)
# else
#  define UWSIGN_COLOR_U32_LT_PURPLE UWSIGN_AES_U32_LT_PURPLE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_LT_CYAN")
# undef UWSIGN_COLOR_U32_LT_CYAN
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_LT_CYAN ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_LT_CYAN, UWSIGN_WIN32_TEXTATTR_LT_CYAN)
# else
#  define UWSIGN_COLOR_U32_LT_CYAN UWSIGN_AES_U32_LT_CYAN
# endif

# pragma push_macro("UWSIGN_COLOR_U32_WHITE")
# undef UWSIGN_COLOR_U32_WHITE
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_WHITE ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_WHITE, UWSIGN_WIN32_TEXTATTR_WHITE)
# else
#  define UWSIGN_COLOR_U32_WHITE UWSIGN_AES_U32_WHITE
# endif

# pragma push_macro("UWSIGN_COLOR_U32_RGB")
# undef UWSIGN_COLOR_U32_RGB
# if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
#  define UWSIGN_COLOR_U32_RGB(r, g, b) ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::log_win32_use_ansi_b, UWSIGN_AES_U32_RGB(r, g, b))
# else
#  define UWSIGN_COLOR_U32_RGB(r, g, b) UWSIGN_AES_U32_RGB(r, g, b)
# endif

#endif
