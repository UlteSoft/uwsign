/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        uwsign.cppm
 * @brief       uwsign C++ startup entry point module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <cstddef>
#include <cstdint>
#include <bit>
#include <limits>
#include <utility>
// macro
#include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.crtmain:uwsign;

import fast_io;
import uwsign.utils.debug;
import uwsign.uwsign_predefine.io;
import uwsign.uwsign_predefine.utils.ansies;
import uwsign.uwsign.cmdline;
import uwsign.uwsign.cmdline.callback;
import uwsign.uwsign.crtmain.global;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "uwsign.h"
