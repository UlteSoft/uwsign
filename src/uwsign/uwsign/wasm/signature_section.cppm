/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        signature_section.cppm
 * @brief       WebAssembly uwsign custom section helper module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <utility>
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.uwsign.wasm.signature_section;

import fast_io;
import uwsign.utils.container;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "signature_section.h"
