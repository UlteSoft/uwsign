/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-25
 * @copyright   APL-2.0 License
 */

module;

// std
#include <cstdint>
#include <cstddef>
#include <memory>
#include <new>
#include <algorithm>
#include <limits>
#include <utility>
// macro
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.utils.cmdline:handle;

import fast_io;
import fast_io_crypto;
import uwsign.utils.container;
import uwsign.utils.hash;
import uwsign.utils.debug;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "handle.h"
