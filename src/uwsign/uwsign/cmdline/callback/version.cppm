/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        version.cppm
 * @brief       uwsign version callback module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

#include <memory>
#include <utility>
#include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
#include <uwsign/utils/macro/push_macros.h>
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
# include <linux/version.h>
#endif
#if defined(__APPLE__) || defined(__DARWIN_C_LEVEL)
# include <TargetConditionals.h>
# include <Availability.h>
#endif
#if (defined(__MIPS__) || defined(__mips__) || defined(_MIPS_ARCH))
# include <sgidefs.h>
#endif

export module uwsign.uwsign.cmdline.callback:version;

import fast_io;
import fast_io_crypto;
import uwsign.utils.container;
import uwsign.utils.version;
import uwsign.utils.cmdline;
import uwsign.uwsign_predefine.io;
import uwsign.uwsign_predefine.utils.ansies;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "version.h"
