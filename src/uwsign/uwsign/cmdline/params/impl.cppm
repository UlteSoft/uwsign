/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        impl.cppm
 * @brief       uwsign command line parameter module aggregator
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

export module uwsign.uwsign.cmdline.params;
export import :version;
export import :help;
export import :value;
export import :sign;
export import :verify;
export import :sign_input;
export import :sign_output;
export import :sign_wasm_output;
export import :sign_key;
export import :sign_certificate;
export import :sign_certificate_chain;
export import :sign_bundle;
export import :sign_bundle_format;
export import :sign_signature;
export import :sign_output_signature;
export import :sign_output_certificate;
export import :sign_output_certificate_chain;
export import :sign_replace;
export import :sign_base64;
export import :log_verbose;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "impl.h"
