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

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstdint>
# include <cstddef>
# include <cstring>
# include <climits>
# include <concepts>
# include <memory>
# include <utility>
# include <type_traits>
# include <atomic>
// import
# include <fast_io.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::mutex
{
    /// @brief Native mutex
    using mutex_t = ::fast_io::native_mutex;
    using mutex_guard_t = ::fast_io::operations::decay::stream_ref_decay_lock_guard<mutex_t&>;
    using unlock_mutex_guard_t = ::fast_io::operations::decay::unlock_stream_ref_decay_lock_guard<mutex_t&>;
}
