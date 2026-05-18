/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-06-30
 * @copyright   APL-2.0 License
 */

module;

// std
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <concepts>
#include <memory>
// platform
#if (!defined(__NEWLIB__) || defined(__CYGWIN__)) && !defined(_WIN32) && !defined(_PICOLIBC__) && !(defined(__MSDOS__) || defined(__DJGPP__)) &&               \
    !defined(__wasm__)
# include <unistd.h>
# include <sys/ioctl.h>
#endif

export module uwsign.utils.console:width;

import fast_io;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "width.h"
