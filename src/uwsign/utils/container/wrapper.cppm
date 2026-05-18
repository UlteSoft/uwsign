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
#include <climits>
#include <concepts>
#include <memory>
#include <utility>
#include <type_traits>
#include <string_view>
#include <set>  /// @todo replace with btreemap
#include <map>  /// @todo replace with btreemap
#include <deque>
#include <unordered_map>
#include <unordered_set>

export module uwsign.utils.container:wrapper;

import fast_io;
import uwsign.utils.hash;
import :allocator;

#ifndef UWSIGN_MODULE
# define UWSIGN_MODULE
#endif
#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT export
#endif

#include "wrapper.h"
