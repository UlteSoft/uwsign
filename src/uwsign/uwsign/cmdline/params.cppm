/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        params.cppm
 * @brief       uwsign command line parameter table module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <memory>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.cmdline:params;

import uwsign.utils.cmdline;
import uwsign.uwsign.cmdline.params;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "params.h"
