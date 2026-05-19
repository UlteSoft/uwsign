/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        impl.cppm
 * @brief       uwsign WebAssembly helper module aggregator
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

export module uwsign.uwsign.wasm;
export import uwsign.uwsign.wasm.signature_section;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "impl.h"
