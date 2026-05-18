/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      24bit-xjkp
 * @version     2.0.0
 * @date        2025-03-21
 * @copyright   APL-2.0 License
 */

module;

export module uwsign.utils.intrinsics;
export import :prefetch;
export import :arm_sve;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "impl.h"
