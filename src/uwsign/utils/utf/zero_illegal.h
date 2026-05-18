/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-05-31
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstdint>
# include <cstddef>
# include <climits>
# include <cstring>
# include <concepts>
# include <memory>
# include <bit>
# include <limits>
# include <algorithm>
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/intrinsics/impl.h>
# include "base.h"
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::utf
{
    inline constexpr ::uwsign::utils::utf::u8result check_has_zero_illegal_unchecked(char8_t const* const str_begin, char8_t const* const str_end) noexcept
    {
#if CHAR_BIT > 8
        auto const section_curr{str_begin};

        for(; section_curr != str_end; ++section_curr)
        {
            auto const section_curr_val{*section_curr};
            section_curr_val &= 0xFFu;
            if(section_curr_val == u8'\0') [[unlikely]] { return {section_curr, ::uwsign::utils::utf::utf_error_code::contains_empty_characters}; }
        }

        return {section_curr, ::uwsign::utils::utf::utf_error_code::success};
#else
        // Find the first occurrence of NUL character (0x00) in the string
        auto const zero_pos{::std::find(str_begin, str_end, u8'\0')};

        if(zero_pos != str_end) [[unlikely]]
        {
            // Found a NUL character, return error with position
            return {zero_pos, ::uwsign::utils::utf::utf_error_code::contains_empty_characters};
        }

        // No NUL characters found, return success
        return {str_end, ::uwsign::utils::utf::utf_error_code::success};
#endif
    }
}

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
