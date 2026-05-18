/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @copyright   APL-2.0 License
 */

module;

// std
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <climits>
#include <concepts>
#include <memory>
#include <bit>
#include <limits>
// macro
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.utils.hash:xxh3;

import fast_io;
import uwsign.utils.intrinsics;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "xxh3.h"
