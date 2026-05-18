/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-24
 * @copyright   APL-2.0 License
 */

/// @brief      The following are the macros used by ansi escape sequences.
/// @details    Use `push_macro` to avoid side effects on existing macros. Please use `pop_macro` in conjunction.

// #pragma once
#if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))

# include "win32_text_attr.h"  // pragma once
# include "ansi_push_macro.h"

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_RST_ALL")
# undef UWSIGN_WIN32_TEXTATTR_RST_ALL
# define UWSIGN_WIN32_TEXTATTR_RST_ALL                                                                                                                           \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_rst_all }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE")
# undef UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE
# define UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_WHITE                                                                                                             \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_white }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE")
# undef UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE
# define UWSIGN_WIN32_TEXTATTR_RST_ALL_AND_SET_PURPLE                                                                                                            \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_purple }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_BLACK")
# undef UWSIGN_WIN32_TEXTATTR_BLACK
# define UWSIGN_WIN32_TEXTATTR_BLACK                                                                                                                             \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_black }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_RED")
# undef UWSIGN_WIN32_TEXTATTR_RED
# define UWSIGN_WIN32_TEXTATTR_RED                                                                                                                               \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_red }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_GREEN")
# undef UWSIGN_WIN32_TEXTATTR_GREEN
# define UWSIGN_WIN32_TEXTATTR_GREEN                                                                                                                             \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_green }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_ORANGE")
# undef UWSIGN_WIN32_TEXTATTR_ORANGE
# define UWSIGN_WIN32_TEXTATTR_ORANGE                                                                                                                            \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_orange }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_BLUE")
# undef UWSIGN_WIN32_TEXTATTR_BLUE
# define UWSIGN_WIN32_TEXTATTR_BLUE                                                                                                                              \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_blue }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_PURPLE")
# undef UWSIGN_WIN32_TEXTATTR_PURPLE
# define UWSIGN_WIN32_TEXTATTR_PURPLE                                                                                                                            \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_purple }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_CYAN")
# undef UWSIGN_WIN32_TEXTATTR_CYAN
# define UWSIGN_WIN32_TEXTATTR_CYAN                                                                                                                              \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_cyan }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_GRAY")
# undef UWSIGN_WIN32_TEXTATTR_GRAY
# define UWSIGN_WIN32_TEXTATTR_GRAY                                                                                                                              \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_gray }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_DK_GRAY")
# undef UWSIGN_WIN32_TEXTATTR_DK_GRAY
# define UWSIGN_WIN32_TEXTATTR_DK_GRAY                                                                                                                           \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_dk_gray }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_LT_RED")
# undef UWSIGN_WIN32_TEXTATTR_LT_RED
# define UWSIGN_WIN32_TEXTATTR_LT_RED                                                                                                                            \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_lt_red }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_LT_GREEN")
# undef UWSIGN_WIN32_TEXTATTR_LT_GREEN
# define UWSIGN_WIN32_TEXTATTR_LT_GREEN                                                                                                                          \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_lt_green }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_YELLOW")
# undef UWSIGN_WIN32_TEXTATTR_YELLOW
# define UWSIGN_WIN32_TEXTATTR_YELLOW                                                                                                                            \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_yellow }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_LT_BLUE")
# undef UWSIGN_WIN32_TEXTATTR_LT_BLUE
# define UWSIGN_WIN32_TEXTATTR_LT_BLUE                                                                                                                           \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_lt_blue }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_LT_PURPLE")
# undef UWSIGN_WIN32_TEXTATTR_LT_PURPLE
# define UWSIGN_WIN32_TEXTATTR_LT_PURPLE                                                                                                                         \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_lt_purple }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_LT_CYAN")
# undef UWSIGN_WIN32_TEXTATTR_LT_CYAN
# define UWSIGN_WIN32_TEXTATTR_LT_CYAN                                                                                                                           \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_lt_cyan }

# pragma push_macro("UWSIGN_WIN32_TEXTATTR_WHITE")
# undef UWSIGN_WIN32_TEXTATTR_WHITE
# define UWSIGN_WIN32_TEXTATTR_WHITE                                                                                                                             \
     ::uwsign::utils::ansies::win32_text_attr { ::uwsign::utils::ansies::text_attr::foreground_white }

#endif
