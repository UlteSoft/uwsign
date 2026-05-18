/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        prefetch.cppm
 * @brief       cpu prefetch instruction
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-21
 * @copyright   APL-2.0 License
 */

module;
// macro
#include <uwsign/utils/macro/push_macros.h>
// platfrom
/// @brief      Including intrin.h in the absence of __builtin_prefetch
#if !UWSIGN_HAS_BUILTIN(__builtin_prefetch)
# include <intrin.h>
#endif

export module uwsign.utils.intrinsics:prefetch;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "prefetch.h"
