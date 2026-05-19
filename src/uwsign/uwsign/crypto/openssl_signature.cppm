/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        openssl_signature.cppm
 * @brief       OpenSSL signing helper module
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

module;

// std
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
// macro
#include <uwsign/utils/macro/push_macros.h>
// platform
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>

export module uwsign.uwsign.crypto.openssl_signature;

import fast_io;
import uwsign.utils.container;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "openssl_signature.h"
