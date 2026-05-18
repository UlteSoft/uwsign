/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-18
 * @copyright   APL-2.0 License
 */

module;

// std
#include <cstdint>
#include <cstddef>
#include <concepts>
#include <memory>

export module uwsign.utils.utf:base;

import fast_io;
import uwsign.utils.container;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "base.h"
