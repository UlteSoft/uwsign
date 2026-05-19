/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        payload.h
 * @brief       uwsign embedded signature payload format
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
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/uwsign/wasm/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::sign::payload
{
    using byte_vector = ::uwsign::utils::container::vector<::std::byte>;
    using byte_view = ::uwsign::uwsign::wasm::byte_view;
    using u8string_view = ::uwsign::utils::container::u8string_view;

    inline constexpr ::std::byte payload_magic[]{
        static_cast<::std::byte>(u8'U'),
        static_cast<::std::byte>(u8'W'),
        static_cast<::std::byte>(u8'S'),
        static_cast<::std::byte>(u8'I'),
        static_cast<::std::byte>(u8'G'),
        static_cast<::std::byte>(u8'N'),
        static_cast<::std::byte>(0),
        static_cast<::std::byte>(1),
    };

    struct signature_payload_view
    {
        byte_view algorithm{};
        byte_view digest{};
        byte_view signature{};
        byte_view certificate{};
        byte_view certificate_chain{};
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

        inline constexpr void append_varuint32(byte_vector& out, ::std::uint32_t value) noexcept
        {
            unsigned char buffer[::fast_io::print_reserve_size(::fast_io::io_reserve_type<unsigned char, decltype(::fast_io::mnp::leb128_put(value))>)]{};
            auto const buffer_end{::fast_io::print_reserve_define(::fast_io::io_reserve_type<unsigned char, decltype(::fast_io::mnp::leb128_put(value))>,
                                                                  buffer,
                                                                  ::fast_io::mnp::leb128_put(value))};
            for(auto curr{buffer}; curr != buffer_end; ++curr) { out.emplace_back(static_cast<::std::byte>(*curr)); }
        }

        inline constexpr bool read_varuint32(::std::byte const*& curr, ::std::byte const* last, ::std::uint32_t& value, u8string_view& error) noexcept
        {
            auto const first{reinterpret_cast<unsigned char const*>(curr)};
            auto const end{reinterpret_cast<unsigned char const*>(last)};
            auto const result{::fast_io::scan_contiguous_define(::fast_io::io_reserve_type<unsigned char, decltype(::fast_io::mnp::leb128_get(value))>,
                                                                first,
                                                                end,
                                                                ::fast_io::mnp::leb128_get(value))};
            if(result.code == ::fast_io::parse_code::ok) [[likely]]
            {
                curr = reinterpret_cast<::std::byte const*>(result.iter);
                return true;
            }

            if(result.code == ::fast_io::parse_code::overflow) [[unlikely]]
            {
                error = u8"signature payload varuint32 overflows 32 bits.";
                return false;
            }

            error = u8"unexpected end of signature payload.";
            return false;
        }

        inline constexpr bool append_field(byte_vector& out, ::std::byte const* first, ::std::size_t size, u8string_view& error) noexcept
        {
            if(size > static_cast<::std::size_t>((::std::numeric_limits<::std::uint32_t>::max)())) [[unlikely]]
            {
                error = u8"signature payload field is too large.";
                return false;
            }

            append_varuint32(out, static_cast<::std::uint32_t>(size));
            if(size != 0uz) { append_bytes(out, first, size); }
            return true;
        }

        inline constexpr bool read_field(::std::byte const*& curr, ::std::byte const* last, byte_view& field, u8string_view& error) noexcept
        {
            ::std::uint32_t field_size{};
            if(!read_varuint32(curr, last, field_size, error)) [[unlikely]] { return false; }

            if(static_cast<::std::size_t>(last - curr) < field_size) [[unlikely]]
            {
                error = u8"signature payload field extends past end.";
                return false;
            }

            field = {curr, curr + field_size};
            curr += field_size;
            return true;
        }
    }  // namespace details

    inline constexpr bool encode(char8_t const* algorithm,
                                 ::std::byte const* digest_first,
                                 ::std::size_t digest_size,
                                 ::std::byte const* signature_first,
                                 ::std::size_t signature_size,
                                 ::std::byte const* certificate_first,
                                 ::std::size_t certificate_size,
                                 ::std::byte const* certificate_chain_first,
                                 ::std::size_t certificate_chain_size,
                                 byte_vector& out,
                                 u8string_view& error) noexcept
    {
        out = {};

        auto const algorithm_size{__builtin_strlen(reinterpret_cast<char const*>(algorithm))};
        auto const total_size{sizeof(payload_magic) + algorithm_size + digest_size + signature_size + certificate_size + certificate_chain_size + 25uz};
        out.reserve(total_size);

        details::append_bytes(out, payload_magic, sizeof(payload_magic));
        if(!details::append_field(out, reinterpret_cast<::std::byte const*>(algorithm), algorithm_size, error)) [[unlikely]] { return false; }
        if(!details::append_field(out, digest_first, digest_size, error)) [[unlikely]] { return false; }
        if(!details::append_field(out, signature_first, signature_size, error)) [[unlikely]] { return false; }
        if(!details::append_field(out, certificate_first, certificate_size, error)) [[unlikely]] { return false; }
        if(!details::append_field(out, certificate_chain_first, certificate_chain_size, error)) [[unlikely]] { return false; }
        return true;
    }

    inline constexpr bool encode(char8_t const* algorithm,
                                 ::std::byte const* digest_first,
                                 ::std::size_t digest_size,
                                 ::std::byte const* signature_first,
                                 ::std::size_t signature_size,
                                 ::std::byte const* certificate_first,
                                 ::std::size_t certificate_size,
                                 byte_vector& out,
                                 u8string_view& error) noexcept
    { return encode(algorithm, digest_first, digest_size, signature_first, signature_size, certificate_first, certificate_size, nullptr, 0uz, out, error); }

    inline constexpr bool decode(::std::byte const* first, ::std::byte const* last, signature_payload_view& out, u8string_view& error) noexcept
    {
        out = {};

        if(static_cast<::std::size_t>(last - first) < sizeof(payload_magic)) [[unlikely]]
        {
            error = u8"signature payload is shorter than the uwsign magic.";
            return false;
        }

        if(::std::memcmp(first, payload_magic, sizeof(payload_magic)) != 0) [[unlikely]]
        {
            error = u8"signature payload magic does not match uwsign v1.";
            return false;
        }

        auto curr{first + sizeof(payload_magic)};
        if(!details::read_field(curr, last, out.algorithm, error)) [[unlikely]] { return false; }
        if(!details::read_field(curr, last, out.digest, error)) [[unlikely]] { return false; }
        if(!details::read_field(curr, last, out.signature, error)) [[unlikely]] { return false; }
        if(!details::read_field(curr, last, out.certificate, error)) [[unlikely]] { return false; }
        if(!details::read_field(curr, last, out.certificate_chain, error)) [[unlikely]] { return false; }

        if(curr != last) [[unlikely]]
        {
            error = u8"signature payload has trailing bytes.";
            return false;
        }

        if(out.digest.size() != 32uz) [[unlikely]]
        {
            error = u8"signature payload digest length is not SHA-256.";
            return false;
        }

        if(out.signature.empty()) [[unlikely]]
        {
            error = u8"signature payload has an empty signature.";
            return false;
        }

        return true;
    }
}  // namespace uwsign::uwsign::sign::payload

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
