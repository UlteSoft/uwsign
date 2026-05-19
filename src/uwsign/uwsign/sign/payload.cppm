/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        payload.cppm
 * @brief       uwsign embedded signature payload module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.sign.payload;

import fast_io;
import uwsign.utils.container;
import uwsign.uwsign.wasm;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "payload.h"
