/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-24
 * @copyright   APL-2.0 License
 */

module;

/// @note   To maintain compatibility with fast_io, the fast_io style of writing is adopted here.
#include "impl.h"

export module uwsign.utils.allocator.fast_io_strict;

export namespace uwsign::utils::allocator::fast_io_strict
{
    using ::uwsign::utils::allocator::fast_io_strict::fast_io_allocator_to_strict;

    using ::uwsign::utils::allocator::fast_io_strict::fast_io_strict_generic_allocator_adapter;
    using ::uwsign::utils::allocator::fast_io_strict::fast_io_strict_typed_generic_allocator_adapter;

    using ::uwsign::utils::allocator::fast_io_strict::native_strict_global_allocator;
    using ::uwsign::utils::allocator::fast_io_strict::native_strict_thread_local_allocator;
    using ::uwsign::utils::allocator::fast_io_strict::native_strict_typed_global_allocator;
    using ::uwsign::utils::allocator::fast_io_strict::native_strict_typed_thread_local_allocator;
}  // namespace uwsign::utils::allocator::fast_io_strict
