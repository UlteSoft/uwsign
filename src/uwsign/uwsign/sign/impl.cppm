/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        impl.cppm
 * @brief       uwsign signing implementation module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <memory>
#include <utility>
#include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.sign;
export import :payload;

import fast_io;
import uwsign.utils.container;
import uwsign.utils.cmdline;
import uwsign.uwsign_predefine.io;
import uwsign.uwsign_predefine.utils.ansies;
import uwsign.uwsign.cmdline;
import uwsign.uwsign.crypto;
import uwsign.uwsign.wasm;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "impl.h"
