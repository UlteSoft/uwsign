/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        log_verbose.cppm
 * @brief       uwsign verbose log command line parameter module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <memory>
#include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.cmdline.params:log_verbose;

import fast_io;
import uwsign.utils.container;
import uwsign.utils.cmdline;
import uwsign.uwsign_predefine.io;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "log_verbose.h"
