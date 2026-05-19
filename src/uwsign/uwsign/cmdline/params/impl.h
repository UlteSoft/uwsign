/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        impl.h
 * @brief       uwsign command line parameter aggregator
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// global
# include "version.h"
# include "help.h"
// value
# include "value.h"
// sign
# include "sign.h"
# include "verify.h"
# include "sign_input.h"
# include "sign_output.h"
# include "sign_wasm_output.h"
# include "sign_key.h"
# include "sign_certificate.h"
# include "sign_certificate_chain.h"
# include "sign_bundle.h"
# include "sign_bundle_format.h"
# include "sign_signature.h"
# include "sign_output_signature.h"
# include "sign_output_certificate.h"
# include "sign_output_certificate_chain.h"
# include "sign_replace.h"
# include "sign_base64.h"
// log
# include "log_verbose.h"
#endif
