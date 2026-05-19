/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        signature_section.h
 * @brief       WebAssembly uwsign custom section helpers
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <cstddef>
# include <cstdint>
# include <cstring>
# include <limits>
# include <utility>
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::wasm
{
    using byte_vector = ::uwsign::utils::container::vector<::std::byte>;
    using u8string_view = ::uwsign::utils::container::u8string_view;

    inline constexpr ::std::size_t wasm_header_size{8uz};
    inline constexpr ::std::uint8_t custom_section_id{};
    inline constexpr ::uwsign::utils::container::u8string_view signature_section_name{u8"wasm_uwsign"};
    inline constexpr ::std::size_t signature_section_name_size{signature_section_name.size()};
    inline constexpr ::uwsign::utils::container::u8string_view legacy_signature_section_name{u8"wasm-uwsign"};
    inline constexpr ::std::size_t legacy_signature_section_name_size{legacy_signature_section_name.size()};
    inline constexpr ::uwsign::utils::container::u8string_view cosign_signature_section_name{u8"wasm-usign"};
    inline constexpr ::std::size_t cosign_signature_section_name_size{cosign_signature_section_name.size()};

    struct byte_view
    {
        ::std::byte const* first{};
        ::std::byte const* last{};

        [[nodiscard]] inline constexpr ::std::size_t size() const noexcept
        {
            if(first == last) [[unlikely]] { return 0uz; }
            return static_cast<::std::size_t>(last - first);
        }

        [[nodiscard]] inline constexpr bool empty() const noexcept
        {
            return first == last;
        }
    };

    struct signature_section_result
    {
        byte_vector stripped_module{};
        ::uwsign::utils::container::vector<byte_vector> signature_payloads{};
    };

    namespace details
    {
        inline constexpr void append_bytes(byte_vector& out, ::std::byte const* first, ::std::byte const* last) noexcept
        {
            if(first == last) [[unlikely]] { return; }
            auto const len{static_cast<::std::size_t>(last - first)};

            auto const old_size{out.size()};
            out.resize(old_size + len);
            ::std::memcpy(out.data() + old_size, first, len);
        }

        inline constexpr void append_bytes(byte_vector& out, void const* first, ::std::size_t len) noexcept
        {
            if(len == 0uz) [[unlikely]] { return; }
            append_bytes(out, static_cast<::std::byte const*>(first), static_cast<::std::byte const*>(first) + len);
        }

        inline constexpr bool validate_header(::std::byte const* first, ::std::byte const* last, u8string_view& error) noexcept
        {
            if(static_cast<::std::size_t>(last - first) < wasm_header_size) [[unlikely]]
            {
                error = u8"module is shorter than the WebAssembly header.";
                return false;
            }

            constexpr unsigned char magic[]{0x00u, 0x61u, 0x73u, 0x6du};
            constexpr unsigned char version[]{0x01u, 0x00u, 0x00u, 0x00u};

            if(::std::memcmp(first, magic, sizeof(magic)) != 0) [[unlikely]]
            {
                error = u8"module does not start with the WebAssembly magic header.";
                return false;
            }

            if(::std::memcmp(first + sizeof(magic), version, sizeof(version)) != 0) [[unlikely]]
            {
                error = u8"unsupported WebAssembly version.";
                return false;
            }

            return true;
        }

        inline constexpr bool read_varuint32(::std::byte const*& curr,
                                             ::std::byte const* last,
                                             ::std::uint32_t& value,
                                             u8string_view& error) noexcept
        {
            auto const first{reinterpret_cast<unsigned char const*>(curr)};
            auto const end{reinterpret_cast<unsigned char const*>(last)};
            using leb128_get_type = decltype(::fast_io::mnp::leb128_get(value));
            constexpr auto reserve_type{::fast_io::io_reserve_type<unsigned char, leb128_get_type>};
            auto const result{::fast_io::scan_contiguous_define(reserve_type, first, end, ::fast_io::mnp::leb128_get(value))};

            if(result.code == ::fast_io::parse_code::ok) [[likely]]
            {
                curr = reinterpret_cast<::std::byte const*>(result.iter);
                return true;
            }

            if(result.code == ::fast_io::parse_code::overflow) [[unlikely]]
            {
                error = static_cast<::std::size_t>(result.iter - first) > 5uz ? u8string_view{u8"varuint32 is longer than 5 bytes."}
                                                                               : u8string_view{u8"varuint32 overflows 32 bits."};
                return false;
            }

            error = u8"unexpected end of data while reading varuint32.";
            return false;
        }

        inline constexpr void append_varuint32(byte_vector& out, ::std::uint32_t value) noexcept
        {
            using leb128_put_type = decltype(::fast_io::mnp::leb128_put(value));
            constexpr auto reserve_type{::fast_io::io_reserve_type<unsigned char, leb128_put_type>};
            unsigned char buffer[::fast_io::print_reserve_size(reserve_type)]{};
            auto const buffer_end{::fast_io::print_reserve_define(reserve_type, buffer, ::fast_io::mnp::leb128_put(value))};
            for(auto curr{buffer}; curr != buffer_end; ++curr) { out.emplace_back(static_cast<::std::byte>(*curr)); }
        }

        inline constexpr bool split_custom_section(byte_view section_payload, byte_view& payload, bool& is_signature_section, u8string_view& error) noexcept
        {
            is_signature_section = false;

            auto curr{section_payload.first};
            ::std::uint32_t name_len{};
            if(!read_varuint32(curr, section_payload.last, name_len, error)) [[unlikely]] { return false; }

            if(static_cast<::std::size_t>(section_payload.last - curr) < name_len) [[unlikely]]
            {
                error = u8"custom section name extends past section payload.";
                return false;
            }

            auto const is_signature_name{name_len == signature_section_name_size &&
                                         ::std::memcmp(curr, signature_section_name.data(), signature_section_name_size) == 0};
            auto const is_legacy_signature_name{name_len == legacy_signature_section_name_size &&
                                                ::std::memcmp(curr, legacy_signature_section_name.data(), legacy_signature_section_name_size) == 0};
            auto const is_cosign_signature_name{name_len == cosign_signature_section_name_size &&
                                                ::std::memcmp(curr, cosign_signature_section_name.data(), cosign_signature_section_name_size) == 0};
            if(!is_signature_name && !is_legacy_signature_name && !is_cosign_signature_name) [[likely]]
            {
                payload = {};
                return true;
            }

            is_signature_section = true;
            payload = {curr + name_len, section_payload.last};
            return true;
        }

        inline constexpr bool checked_u32_size(::std::size_t value, u8string_view& error) noexcept
        {
            if(value > static_cast<::std::size_t>((::std::numeric_limits<::std::uint32_t>::max)())) [[unlikely]]
            {
                error = u8"section size exceeds varuint32 range.";
                return false;
            }

            return true;
        }
    }  // namespace details

    inline constexpr bool strip_and_extract_signature_sections(::std::byte const* first,
                                                               ::std::byte const* last,
                                                               signature_section_result& result,
                                                               u8string_view& error) noexcept
    {
        result = {};

        if(!details::validate_header(first, last, error)) [[unlikely]] { return false; }

        result.stripped_module.reserve(static_cast<::std::size_t>(last - first));
        details::append_bytes(result.stripped_module, first, first + wasm_header_size);

        auto curr{first + wasm_header_size};
        while(curr != last)
        {
            auto const section_start{curr};
            auto const section_id{static_cast<::std::uint8_t>(*curr)};
            ++curr;

            ::std::uint32_t section_size{};
            if(!details::read_varuint32(curr, last, section_size, error)) [[unlikely]] { return false; }

            if(static_cast<::std::size_t>(last - curr) < section_size) [[unlikely]]
            {
                error = u8"section extends past end of module.";
                return false;
            }

            auto const section_end{curr + section_size};

            if(section_id == custom_section_id)
            {
                byte_view payload{};
                bool is_signature_section{};
                if(!details::split_custom_section({curr, section_end}, payload, is_signature_section, error)) [[unlikely]] { return false; }

                if(is_signature_section)
                {
                    byte_vector copied{};
                    copied.reserve(payload.size());
                    details::append_bytes(copied, payload.first, payload.last);
                    result.signature_payloads.emplace_back(::std::move(copied));
                    curr = section_end;
                    continue;
                }
            }

            details::append_bytes(result.stripped_module, section_start, section_end);
            curr = section_end;
        }

        return true;
    }

    inline constexpr bool strip_signature_sections(::std::byte const* first, ::std::byte const* last, byte_vector& out, u8string_view& error) noexcept
    {
        signature_section_result result{};
        if(!strip_and_extract_signature_sections(first, last, result, error)) [[unlikely]] { return false; }
        out = ::std::move(result.stripped_module);
        return true;
    }

    inline constexpr bool extract_signature_sections(::std::byte const* first,
                                                     ::std::byte const* last,
                                                     ::uwsign::utils::container::vector<byte_vector>& out,
                                                     u8string_view& error) noexcept
    {
        signature_section_result result{};
        if(!strip_and_extract_signature_sections(first, last, result, error)) [[unlikely]] { return false; }
        out = ::std::move(result.signature_payloads);
        return true;
    }

    inline constexpr bool append_custom_section(byte_vector& out,
                                                ::std::byte const* module_first,
                                                ::std::byte const* module_last,
                                                char8_t const* name_first,
                                                ::std::size_t name_size,
                                                ::std::byte const* payload_first,
                                                ::std::byte const* payload_last,
                                                u8string_view& error) noexcept
    {
        if(!details::validate_header(module_first, module_last, error)) [[unlikely]] { return false; }

        auto const payload_size{payload_first == payload_last ? 0uz : static_cast<::std::size_t>(payload_last - payload_first)};
        auto const section_payload_size{name_size + payload_size + 5uz};
        if(!details::checked_u32_size(section_payload_size, error)) [[unlikely]] { return false; }

        byte_vector section_payload{};
        section_payload.reserve(section_payload_size);
        details::append_varuint32(section_payload, static_cast<::std::uint32_t>(name_size));
        details::append_bytes(section_payload, name_first, name_size);
        details::append_bytes(section_payload, payload_first, payload_last);

        out = {};
        out.reserve(static_cast<::std::size_t>(module_last - module_first) + section_payload.size() + 6uz);
        details::append_bytes(out, module_first, module_last);
        out.emplace_back(static_cast<::std::byte>(custom_section_id));
        details::append_varuint32(out, static_cast<::std::uint32_t>(section_payload.size()));
        details::append_bytes(out, section_payload.data(), section_payload.data() + section_payload.size());
        return true;
    }

    inline constexpr bool append_signature_section_preserve(byte_vector& out,
                                                            ::std::byte const* module_first,
                                                            ::std::byte const* module_last,
                                                            ::std::byte const* payload_first,
                                                            ::std::byte const* payload_last,
                                                            u8string_view& error) noexcept
    {
        return append_custom_section(out,
                                     module_first,
                                     module_last,
                                     signature_section_name.data(),
                                     signature_section_name_size,
                                     payload_first,
                                     payload_last,
                                     error);
    }

    inline constexpr bool append_signature_section(byte_vector& out,
                                                   ::std::byte const* module_first,
                                                   ::std::byte const* module_last,
                                                   ::std::byte const* payload_first,
                                                   ::std::byte const* payload_last,
                                                   u8string_view& error) noexcept
    {
        byte_vector stripped{};
        if(!strip_signature_sections(module_first, module_last, stripped, error)) [[unlikely]] { return false; }
        return append_signature_section_preserve(out,
                                                 stripped.data(),
                                                 stripped.data() + stripped.size(),
                                                 payload_first,
                                                 payload_last,
                                                 error);
    }
}  // namespace uwsign::uwsign::wasm

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
