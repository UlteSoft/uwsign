/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2026-03-26
 * @copyright   APL-2.0 License
 */

module;

// std
#include <coroutine>
#include <atomic>
#include <cstddef>
#include <memory>
#include <utility>
// macro
#include <uwsign/utils/macro/push_macros.h>

export module uwsign.utils.thread:native_thread;

import fast_io;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "native_thread.h"
