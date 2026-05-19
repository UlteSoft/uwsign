/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        impl.h
 * @brief       uwsign signing implementation
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
# include <exception>
# include <memory>
# include <utility>
// macro
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_push_macro.h>
# include <uwsign/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_device.h>
# include <uwsign/utils/container/impl.h>
# include <uwsign/utils/cmdline/impl.h>
# include <uwsign/uwsign_predefine/io/impl.h>
# include <uwsign/uwsign_predefine/utils/ansies/impl.h>
# include <uwsign/uwsign/cmdline/impl.h>
# include <uwsign/uwsign/crypto/openssl_signature.h>
# include <uwsign/uwsign/sign/payload.h>
# include <uwsign/uwsign/wasm/signature_section.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::sign
{
    enum class execution_result : int
    {
        ok = 0,
        failed = 1
    };

    using byte_vector = ::uwsign::utils::container::vector<::std::byte>;
    using u8string = ::uwsign::utils::container::u8string;
    using u8string_view = ::uwsign::utils::container::u8string_view;
    using u8cstring_view = ::uwsign::utils::container::u8cstring_view;

    struct command_options
    {
        bool sign_mode{};
        bool verify_mode{};
        bool replace_signature_sections{};
        bool base64_output{};
        bool cosign_legacy_bundle_format{};
        bool sigstore_bundle_format{};
        u8cstring_view input{};
        u8cstring_view output{};
        u8cstring_view wasm_output{};
        u8cstring_view key{};
        u8cstring_view certificate{};
        u8cstring_view certificate_chain{};
        u8cstring_view bundle_format{};
        u8cstring_view bundle{};
        u8cstring_view signature{};
        u8cstring_view output_signature{};
        u8cstring_view output_certificate{};
        u8cstring_view output_certificate_chain{};
    };

    namespace details
    {
        inline constexpr bool byte_equal(::std::byte const* a, ::std::byte const* b, ::std::size_t size) noexcept
        {
            return size == 0uz || ::std::memcmp(a, b, size) == 0;
        }

        inline constexpr ::uwsign::utils::container::u8string_view as_u8string_view(::uwsign::utils::cmdline::parameter const* p) noexcept
        {
            return p == nullptr ? ::uwsign::utils::container::u8string_view{} : p->name;
        }

        template <typename Stm>
        inline constexpr void print_error(Stm&& stm, u8string_view msg) noexcept
        {
            ::fast_io::io::perr(::std::forward<Stm>(stm),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                msg,
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                u8"\n");
        }

        template <typename Stm>
        inline constexpr void print_error(Stm&& stm, char8_t const* msg) noexcept
        {
            print_error(::std::forward<Stm>(stm), u8string_view{::fast_io::mnp::os_c_str(msg)});
        }

        template <typename Stm>
        inline constexpr void print_info(Stm&& stm, char8_t const* msg) noexcept
        {
            ::fast_io::io::perr(::std::forward<Stm>(stm),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                u8"uwsign: ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_LT_GREEN),
                                u8"[info]  ",
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                ::fast_io::mnp::os_c_str(msg),
                                ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                u8"\n");
        }

        inline bool get_value_after(::uwsign::utils::cmdline::parameter_parsing_results const* curr,
                                    ::uwsign::utils::cmdline::parameter_parsing_results const* end,
                                    u8cstring_view& out) noexcept
        {
            auto const next{curr + 1u};
            if(next == end || next->type != ::uwsign::utils::cmdline::parameter_parsing_results_type::occupied_arg) [[unlikely]] { return false; }
            out = next->str;
            return true;
        }

        [[nodiscard]] inline constexpr bool is_stdio_path(u8cstring_view path) noexcept
        {
            return path == u8"-";
        }

        inline constexpr void count_stdio_path(::std::size_t& count, u8cstring_view path) noexcept
        {
            if(!path.empty() && is_stdio_path(path)) { ++count; }
        }

        [[nodiscard]] inline constexpr ::std::size_t count_input_stdio_paths(command_options const& options) noexcept
        {
            ::std::size_t count{};
            count_stdio_path(count, options.input);
            count_stdio_path(count, options.key);
            count_stdio_path(count, options.certificate);
            count_stdio_path(count, options.certificate_chain);

            if(options.verify_mode)
            {
                count_stdio_path(count, options.bundle);
                count_stdio_path(count, options.signature);
            }

            return count;
        }

        [[nodiscard]] inline constexpr ::std::size_t count_output_stdio_paths(command_options const& options) noexcept
        {
            ::std::size_t count{};
            auto const output_path{!options.wasm_output.empty() ? options.wasm_output : options.output};
            count_stdio_path(count, output_path);
            count_stdio_path(count, options.bundle);
            count_stdio_path(count, options.output_signature);
            count_stdio_path(count, options.output_certificate);
            count_stdio_path(count, options.output_certificate_chain);
            return count;
        }

        inline bool collect_options(command_options& options, u8string_view& error) noexcept
        {
            options = {};

            auto const begin{::uwsign::uwsign::cmdline::parsing_result.cbegin()};
            auto const end{::uwsign::uwsign::cmdline::parsing_result.cend()};

            for(auto curr{begin + 1u}; curr != end; ++curr)
            {
                if(curr->type != ::uwsign::utils::cmdline::parameter_parsing_results_type::parameter || curr->para == nullptr) { continue; }

                auto const name{as_u8string_view(curr->para)};
                if(name == u8"--sign") { options.sign_mode = true; }
                else if(name == u8"--verify") { options.verify_mode = true; }
                else if(name == u8"--replace") { options.replace_signature_sections = true; }
                else if(name == u8"--b64") { options.base64_output = true; }
                else if(name == u8"--bundle-format")
                {
                    if(!get_value_after(curr, end, options.bundle_format)) [[unlikely]]
                    {
                        error = u8"--bundle-format requires a format value.";
                        return false;
                    }
                }
                else if(name == u8"--input")
                {
                    if(!get_value_after(curr, end, options.input)) [[unlikely]]
                    {
                        error = u8"--input requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--output")
                {
                    if(!get_value_after(curr, end, options.output)) [[unlikely]]
                    {
                        error = u8"--output requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--wasm-output")
                {
                    if(!get_value_after(curr, end, options.wasm_output)) [[unlikely]]
                    {
                        error = u8"--wasm-output requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--key")
                {
                    if(!get_value_after(curr, end, options.key)) [[unlikely]]
                    {
                        error = u8"--key requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--certificate")
                {
                    if(!get_value_after(curr, end, options.certificate)) [[unlikely]]
                    {
                        error = u8"--certificate requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--certificate-chain")
                {
                    if(!get_value_after(curr, end, options.certificate_chain)) [[unlikely]]
                    {
                        error = u8"--certificate-chain requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--bundle")
                {
                    if(!get_value_after(curr, end, options.bundle)) [[unlikely]]
                    {
                        error = u8"--bundle requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--signature")
                {
                    if(!get_value_after(curr, end, options.signature)) [[unlikely]]
                    {
                        error = u8"--signature requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--output-signature")
                {
                    if(!get_value_after(curr, end, options.output_signature)) [[unlikely]]
                    {
                        error = u8"--output-signature requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--output-certificate")
                {
                    if(!get_value_after(curr, end, options.output_certificate)) [[unlikely]]
                    {
                        error = u8"--output-certificate requires a file value.";
                        return false;
                    }
                }
                else if(name == u8"--output-certificate-chain")
                {
                    if(!get_value_after(curr, end, options.output_certificate_chain)) [[unlikely]]
                    {
                        error = u8"--output-certificate-chain requires a file value.";
                        return false;
                    }
                }
            }

            if(options.sign_mode == options.verify_mode) [[unlikely]]
            {
                error = options.sign_mode ? u8string_view{u8"--sign and --verify cannot be used together."}
                                          : u8string_view{u8"missing command: use --sign or --verify."};
                return false;
            }

            if(options.input.empty()) [[unlikely]]
            {
                error = u8"--input is required.";
                return false;
            }

            if(!options.bundle_format.empty())
            {
                if(options.bundle_format == u8"uwsign")
                {
                    options.cosign_legacy_bundle_format = false;
                    options.sigstore_bundle_format = false;
                }
                else if(options.bundle_format == u8"cosign" || options.bundle_format == u8"cosign-legacy")
                {
                    options.cosign_legacy_bundle_format = true;
                    options.sigstore_bundle_format = false;
                }
                else if(options.bundle_format == u8"sigstore" || options.bundle_format == u8"cosign-v0.3" ||
                        options.bundle_format == u8"cosign-new")
                {
                    options.cosign_legacy_bundle_format = false;
                    options.sigstore_bundle_format = true;
                }
                else
                {
                    error = u8"--bundle-format must be 'uwsign', 'cosign', or 'cosign-v0.3'.";
                    return false;
                }
            }

            if(options.sign_mode)
            {
                if(options.output.empty() && options.wasm_output.empty() && options.bundle.empty() && options.output_signature.empty() &&
                   options.output_certificate.empty() && options.output_certificate_chain.empty()) [[unlikely]]
                {
                    error = u8"--sign requires an output: --output, --wasm-output, --bundle, --output-signature, --output-certificate, or --output-certificate-chain.";
                    return false;
                }

                if(options.key.empty()) [[unlikely]]
                {
                    error = u8"--key is required for --sign.";
                    return false;
                }

                if(!options.output_certificate.empty() && options.certificate.empty()) [[unlikely]]
                {
                    error = u8"--output-certificate requires --certificate while signing.";
                    return false;
                }

                if(!options.certificate_chain.empty() && options.certificate.empty()) [[unlikely]]
                {
                    error = u8"--certificate-chain requires --certificate while signing.";
                    return false;
                }

                if(!options.output_certificate_chain.empty() && options.certificate_chain.empty()) [[unlikely]]
                {
                    error = u8"--output-certificate-chain requires --certificate-chain while signing.";
                    return false;
                }

                if(count_output_stdio_paths(options) > 1uz) [[unlikely]]
                {
                    error = u8"only one signing output can use stdout ('-').";
                    return false;
                }
            }
            else
            {
                if(!options.signature.empty() && options.key.empty() && options.certificate.empty()) [[unlikely]]
                {
                    error = u8"--signature verification requires --key or --certificate.";
                    return false;
                }

                if(options.signature.empty() && options.key.empty() && options.certificate.empty() && options.certificate_chain.empty()) [[unlikely]]
                {
                    error = u8"--verify requires --key, --certificate, or --certificate-chain; embedded certificates are not trusted by themselves.";
                    return false;
                }

                if(!options.certificate_chain.empty() && options.certificate.empty() && !options.signature.empty()) [[unlikely]]
                {
                    error = u8"--certificate-chain requires --certificate for detached signature verification.";
                    return false;
                }
            }

            if(count_input_stdio_paths(options) > 1uz) [[unlikely]]
            {
                error = u8"only one input can use stdin ('-').";
                return false;
            }

            return true;
        }

        inline byte_vector load_stdin()
        {
            byte_vector out{};
            constexpr ::std::size_t buffer_size{65536uz};
            ::std::byte buffer[buffer_size];
            auto in{::fast_io::in()};

            for(;;)
            {
                auto const read_end{::fast_io::operations::read_some_bytes(in, buffer, buffer + buffer_size)};
                if(read_end == buffer) { return out; }
                ::uwsign::uwsign::wasm::details::append_bytes(out, buffer, read_end);
            }
        }

        inline byte_vector load_file(u8cstring_view path)
        {
            if(is_stdio_path(path)) { return load_stdin(); }

            ::fast_io::native_file_loader loader{path};
            byte_vector out{};
            out.reserve(loader.size());
            if(loader.size() != 0uz)
            {
                ::uwsign::uwsign::wasm::details::append_bytes(out,
                                                              reinterpret_cast<::std::byte const*>(loader.data()),
                                                              reinterpret_cast<::std::byte const*>(loader.data() + loader.size()));
            }
            return out;
        }

        inline void write_file(u8cstring_view path, byte_vector const& bytes)
        {
            ::std::byte empty{};
            auto const first{bytes.empty() ? ::std::addressof(empty) : bytes.data()};
            auto const last{first + bytes.size()};

            if(is_stdio_path(path))
            {
                auto out{::fast_io::out()};
                ::fast_io::operations::write_all_bytes(out, first, last);
                return;
            }

            ::fast_io::u8native_file out{path, ::fast_io::open_mode::out | ::fast_io::open_mode::trunc};
            ::fast_io::operations::write_all_bytes(out, first, last);
        }

        [[nodiscard]] inline constexpr bool is_base64_space(::std::byte c) noexcept
        {
            auto const ch{static_cast<unsigned char>(c)};
            return ch == static_cast<unsigned char>(' ') || ch == static_cast<unsigned char>('\n') || ch == static_cast<unsigned char>('\r') ||
                   ch == static_cast<unsigned char>('\t');
        }

        [[nodiscard]] inline constexpr unsigned base64_decode_value(::std::byte c) noexcept
        {
            auto const ch{static_cast<unsigned char>(c)};
            if(ch >= static_cast<unsigned char>('A') && ch <= static_cast<unsigned char>('Z')) { return ch - static_cast<unsigned char>('A'); }
            if(ch >= static_cast<unsigned char>('a') && ch <= static_cast<unsigned char>('z')) { return ch - static_cast<unsigned char>('a') + 26u; }
            if(ch >= static_cast<unsigned char>('0') && ch <= static_cast<unsigned char>('9')) { return ch - static_cast<unsigned char>('0') + 52u; }
            if(ch == static_cast<unsigned char>('+')) { return 62u; }
            if(ch == static_cast<unsigned char>('/')) { return 63u; }
            return 64u;
        }

        inline void base64_encode(byte_vector const& bytes, byte_vector& out)
        {
            static constexpr char8_t table[]{u8"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
            out = {};
            out.reserve(((bytes.size() + 2uz) / 3uz) * 4uz);
            if(bytes.empty()) { return; }

            auto curr{bytes.data()};
            auto const last{bytes.data() + bytes.size()};
            while(static_cast<::std::size_t>(last - curr) >= 3uz)
            {
                auto const b0{static_cast<unsigned char>(curr[0])};
                auto const b1{static_cast<unsigned char>(curr[1])};
                auto const b2{static_cast<unsigned char>(curr[2])};
                out.emplace_back(static_cast<::std::byte>(table[b0 >> 2u]));
                out.emplace_back(static_cast<::std::byte>(table[((b0 & 0x03u) << 4u) | (b1 >> 4u)]));
                out.emplace_back(static_cast<::std::byte>(table[((b1 & 0x0Fu) << 2u) | (b2 >> 6u)]));
                out.emplace_back(static_cast<::std::byte>(table[b2 & 0x3Fu]));
                curr += 3uz;
            }

            auto const rest{static_cast<::std::size_t>(last - curr)};
            if(rest == 1uz)
            {
                auto const b0{static_cast<unsigned char>(curr[0])};
                out.emplace_back(static_cast<::std::byte>(table[b0 >> 2u]));
                out.emplace_back(static_cast<::std::byte>(table[(b0 & 0x03u) << 4u]));
                out.emplace_back(static_cast<::std::byte>('='));
                out.emplace_back(static_cast<::std::byte>('='));
            }
            else if(rest == 2uz)
            {
                auto const b0{static_cast<unsigned char>(curr[0])};
                auto const b1{static_cast<unsigned char>(curr[1])};
                out.emplace_back(static_cast<::std::byte>(table[b0 >> 2u]));
                out.emplace_back(static_cast<::std::byte>(table[((b0 & 0x03u) << 4u) | (b1 >> 4u)]));
                out.emplace_back(static_cast<::std::byte>(table[(b1 & 0x0Fu) << 2u]));
                out.emplace_back(static_cast<::std::byte>('='));
            }
        }

        inline bool base64_decode(byte_vector const& encoded, byte_vector& out) noexcept
        {
            out = {};
            out.reserve((encoded.size() / 4uz) * 3uz);

            unsigned quartet[4uz]{};
            ::std::size_t quartet_size{};
            bool seen_padding{};

            for(auto const c: encoded)
            {
                if(is_base64_space(c)) { continue; }

                unsigned value{};
                if(static_cast<unsigned char>(c) == static_cast<unsigned char>('='))
                {
                    value = 64u;
                    seen_padding = true;
                }
                else
                {
                    if(seen_padding) [[unlikely]] { return false; }
                    value = base64_decode_value(c);
                    if(value == 64u) [[unlikely]] { return false; }
                }

                quartet[quartet_size++] = value;
                if(quartet_size != 4uz) { continue; }

                if(quartet[0] == 64u || quartet[1] == 64u) [[unlikely]] { return false; }

                out.emplace_back(static_cast<::std::byte>((quartet[0] << 2u) | (quartet[1] >> 4u)));
                if(quartet[2] != 64u)
                {
                    out.emplace_back(static_cast<::std::byte>(((quartet[1] & 0x0Fu) << 4u) | (quartet[2] >> 2u)));
                    if(quartet[3] != 64u)
                    {
                        out.emplace_back(static_cast<::std::byte>(((quartet[2] & 0x03u) << 6u) | quartet[3]));
                    }
                }
                else if(quartet[3] != 64u) [[unlikely]]
                {
                    return false;
                }

                quartet_size = 0uz;
            }

            return quartet_size == 0uz;
        }

        inline constexpr void append_u8(byte_vector& out, char8_t const* first, ::std::size_t size) noexcept
        {
            ::uwsign::uwsign::wasm::details::append_bytes(out,
                                                          reinterpret_cast<::std::byte const*>(first),
                                                          reinterpret_cast<::std::byte const*>(first + size));
        }

        inline void append_u8_z(byte_vector& out, char8_t const* str) noexcept
        {
            append_u8(out, str, __builtin_strlen(reinterpret_cast<char const*>(str)));
        }

        inline void copy_bytes(byte_vector const& src, byte_vector& dst)
        {
            dst = {};
            dst.reserve(src.size());
            if(!src.empty()) { ::uwsign::uwsign::wasm::details::append_bytes(dst, src.data(), src.data() + src.size()); }
        }

        inline void make_certificate_chain_with_embedded_intermediates(byte_vector& out,
                                                                       ::uwsign::uwsign::wasm::byte_view embedded_intermediates,
                                                                       byte_vector const& trusted_chain)
        {
            out = {};
            out.reserve(embedded_intermediates.size() + trusted_chain.size());
            if(!embedded_intermediates.empty())
            {
                ::uwsign::uwsign::wasm::details::append_bytes(out, embedded_intermediates.first, embedded_intermediates.last);
            }
            if(!trusted_chain.empty())
            {
                ::uwsign::uwsign::wasm::details::append_bytes(out, trusted_chain.data(), trusted_chain.data() + trusted_chain.size());
            }
        }

        inline void make_certificate_chain_with_embedded_intermediates(byte_vector& out, byte_vector const& embedded_intermediates, byte_vector const& trusted_chain)
        {
            out = {};
            out.reserve(embedded_intermediates.size() + trusted_chain.size());
            if(!embedded_intermediates.empty())
            {
                ::uwsign::uwsign::wasm::details::append_bytes(out, embedded_intermediates.data(), embedded_intermediates.data() + embedded_intermediates.size());
            }
            if(!trusted_chain.empty())
            {
                ::uwsign::uwsign::wasm::details::append_bytes(out, trusted_chain.data(), trusted_chain.data() + trusted_chain.size());
            }
        }

        [[nodiscard]] inline constexpr bool is_json_space(::std::byte c) noexcept
        {
            auto const ch{static_cast<unsigned char>(c)};
            return ch == static_cast<unsigned char>(' ') || ch == static_cast<unsigned char>('\n') || ch == static_cast<unsigned char>('\r') ||
                   ch == static_cast<unsigned char>('\t');
        }

        [[nodiscard]] inline constexpr bool json_byte_equal(::std::byte c, char8_t ch) noexcept
        {
            return static_cast<unsigned char>(c) == static_cast<unsigned char>(ch);
        }

        [[nodiscard]] inline constexpr ::std::byte const* skip_json_space(::std::byte const* curr, ::std::byte const* last) noexcept
        {
            while(curr != last && is_json_space(*curr)) { ++curr; }
            return curr;
        }

        [[nodiscard]] inline ::std::byte const* find_bytes(::std::byte const* first,
                                                           ::std::byte const* last,
                                                           char8_t const* needle,
                                                           ::std::size_t needle_size) noexcept
        {
            if(needle_size == 0uz) { return first; }
            for(auto curr{first}; static_cast<::std::size_t>(last - curr) >= needle_size; ++curr)
            {
                if(::std::memcmp(curr, needle, needle_size) == 0) { return curr; }
            }

            return last;
        }

        [[nodiscard]] inline ::std::byte const* find_json_key(::std::byte const* first,
                                                              ::std::byte const* last,
                                                              char8_t const* key,
                                                              ::std::size_t key_size) noexcept
        {
            for(auto curr{first}; static_cast<::std::size_t>(last - curr) >= key_size + 2uz; ++curr)
            {
                if(json_byte_equal(curr[0], u8'"') && ::std::memcmp(curr + 1, key, key_size) == 0 &&
                   json_byte_equal(curr[key_size + 1uz], u8'"'))
                {
                    return curr;
                }
            }

            return last;
        }

        inline bool read_json_string(::std::byte const* first,
                                     ::std::byte const* last,
                                     byte_vector& out,
                                     ::std::byte const*& next,
                                     u8string_view& error) noexcept
        {
            out = {};
            next = first;
            if(first == last || !json_byte_equal(*first, u8'"')) [[unlikely]]
            {
                error = u8"JSON string expected.";
                return false;
            }

            auto curr{first + 1};
            while(curr != last)
            {
                auto const c{*curr++};
                if(json_byte_equal(c, u8'"'))
                {
                    next = curr;
                    return true;
                }

                if(!json_byte_equal(c, u8'\\'))
                {
                    out.emplace_back(c);
                    continue;
                }

                if(curr == last) [[unlikely]]
                {
                    error = u8"JSON string escape is truncated.";
                    return false;
                }

                auto const esc{*curr++};
                switch(static_cast<unsigned char>(esc))
                {
                    case static_cast<unsigned char>('"'): out.emplace_back(static_cast<::std::byte>('"')); break;
                    case static_cast<unsigned char>('\\'): out.emplace_back(static_cast<::std::byte>('\\')); break;
                    case static_cast<unsigned char>('/'): out.emplace_back(static_cast<::std::byte>('/')); break;
                    case static_cast<unsigned char>('b'): out.emplace_back(static_cast<::std::byte>('\b')); break;
                    case static_cast<unsigned char>('f'): out.emplace_back(static_cast<::std::byte>('\f')); break;
                    case static_cast<unsigned char>('n'): out.emplace_back(static_cast<::std::byte>('\n')); break;
                    case static_cast<unsigned char>('r'): out.emplace_back(static_cast<::std::byte>('\r')); break;
                    case static_cast<unsigned char>('t'): out.emplace_back(static_cast<::std::byte>('\t')); break;
                    default:
                    {
                        error = u8"unsupported JSON string escape.";
                        return false;
                    }
                }
            }

            error = u8"JSON string is not terminated.";
            return false;
        }

        inline bool find_json_string_value(::std::byte const* first,
                                           ::std::byte const* last,
                                           char8_t const* key,
                                           ::std::size_t key_size,
                                           byte_vector& out,
                                           ::std::byte const*& next,
                                           u8string_view& error) noexcept
        {
            auto const key_pos{find_json_key(first, last, key, key_size)};
            if(key_pos == last) { return false; }

            auto curr{skip_json_space(key_pos + key_size + 2uz, last)};
            if(curr == last || !json_byte_equal(*curr, u8':')) [[unlikely]]
            {
                error = u8"JSON key is not followed by ':'.";
                return false;
            }

            curr = skip_json_space(curr + 1, last);
            return read_json_string(curr, last, out, next, error);
        }

        inline bool find_json_string_value(::std::byte const* first,
                                           ::std::byte const* last,
                                           char8_t const* key,
                                           ::std::size_t key_size,
                                           byte_vector& out,
                                           u8string_view& error) noexcept
        {
            ::std::byte const* next{};
            return find_json_string_value(first, last, key, key_size, out, next, error);
        }

        inline void append_json_escaped_base64_field(byte_vector& out, char8_t const* key, byte_vector const& raw)
        {
            byte_vector b64{};
            base64_encode(raw, b64);
            append_u8_z(out, u8"\"");
            append_u8_z(out, key);
            append_u8_z(out, u8"\":\"");
            if(!b64.empty()) { ::uwsign::uwsign::wasm::details::append_bytes(out, b64.data(), b64.data() + b64.size()); }
            append_u8_z(out, u8"\"");
        }

        inline void append_json_base64_value(byte_vector& out, byte_vector const& raw)
        {
            byte_vector b64{};
            base64_encode(raw, b64);
            append_u8_z(out, u8"\"");
            if(!b64.empty()) { ::uwsign::uwsign::wasm::details::append_bytes(out, b64.data(), b64.data() + b64.size()); }
            append_u8_z(out, u8"\"");
        }

        inline void append_json_base64_c_array(byte_vector& out, char8_t const* key, ::std::byte const* raw, ::std::size_t raw_size)
        {
            byte_vector bytes{};
            bytes.reserve(raw_size);
            if(raw_size != 0uz) { ::uwsign::uwsign::wasm::details::append_bytes(bytes, raw, raw + raw_size); }

            append_u8_z(out, u8"\"");
            append_u8_z(out, key);
            append_u8_z(out, u8"\":");
            append_json_base64_value(out, bytes);
        }

        inline void make_cosign_legacy_bundle(byte_vector const& signature, byte_vector const& certificate, byte_vector& out)
        {
            out = {};
            out.reserve(signature.size() + certificate.size() + 128uz);
            append_u8_z(out, u8"{");
            append_json_escaped_base64_field(out, u8"base64Signature", signature);
            if(!certificate.empty())
            {
                append_u8_z(out, u8",");
                append_json_escaped_base64_field(out, u8"cert", certificate);
            }
            append_u8_z(out, u8"}");
        }

        inline bool make_sigstore_bundle(byte_vector const& signature,
                                         ::std::byte const* digest,
                                         ::std::size_t digest_size,
                                         byte_vector const& private_key,
                                         byte_vector const& certificate,
                                         byte_vector const& certificate_chain,
                                         byte_vector& out,
                                         u8string_view& error) noexcept
        {
            out = {};
            if(digest_size != 32uz) [[unlikely]]
            {
                error = u8"Sigstore bundle requires a SHA-256 message digest.";
                return false;
            }

            byte_vector raw_certificate{};
            ::uwsign::utils::container::vector<byte_vector> raw_chain{};
            byte_vector raw_public_key{};
            if(!certificate.empty())
            {
                auto status{::uwsign::uwsign::crypto::certificate_pem_to_der(certificate.data(), certificate.size(), raw_certificate)};
                if(!status.ok) [[unlikely]]
                {
                    error = status.message;
                    return false;
                }

                if(!certificate_chain.empty())
                {
                    status = ::uwsign::uwsign::crypto::certificates_pem_to_der_list(certificate_chain.data(), certificate_chain.size(), raw_chain);
                    if(!status.ok) [[unlikely]]
                    {
                        error = status.message;
                        return false;
                    }
                }
            }
            else
            {
                auto status{::uwsign::uwsign::crypto::export_public_key_der_from_private_key_pem(private_key.data(), private_key.size(), raw_public_key)};
                if(!status.ok) [[unlikely]]
                {
                    error = status.message;
                    return false;
                }
            }

            out.reserve(signature.size() + raw_certificate.size() + raw_public_key.size() + certificate_chain.size() + 512uz);
            append_u8_z(out, u8"{\"mediaType\":\"application/vnd.dev.sigstore.bundle.v0.3+json\",\"verificationMaterial\":{");
            if(!raw_certificate.empty() || !raw_chain.empty())
            {
                append_u8_z(out, u8"\"x509CertificateChain\":{\"certificates\":[");
                append_u8_z(out, u8"{\"rawBytes\":");
                append_json_base64_value(out, raw_certificate);
                append_u8_z(out, u8"}");
                for(auto const& cert_der: raw_chain)
                {
                    append_u8_z(out, u8",{\"rawBytes\":");
                    append_json_base64_value(out, cert_der);
                    append_u8_z(out, u8"}");
                }
                append_u8_z(out, u8"]}");
            }
            else
            {
                ::std::byte public_key_digest[32uz]{};
                auto status{::uwsign::uwsign::crypto::sha256(raw_public_key.data(), raw_public_key.size(), public_key_digest)};
                if(!status.ok) [[unlikely]]
                {
                    error = status.message;
                    return false;
                }

                byte_vector digest_bytes{};
                digest_bytes.reserve(sizeof(public_key_digest));
                ::uwsign::uwsign::wasm::details::append_bytes(digest_bytes, public_key_digest, public_key_digest + sizeof(public_key_digest));

                byte_vector hint{};
                base64_encode(digest_bytes, hint);
                append_u8_z(out, u8"\"publicKey\":{\"hint\":\"");
                if(!hint.empty()) { ::uwsign::uwsign::wasm::details::append_bytes(out, hint.data(), hint.data() + hint.size()); }
                append_u8_z(out, u8"\"}");
            }

            append_u8_z(out, u8"},\"messageSignature\":{\"messageDigest\":{\"algorithm\":\"SHA2_256\",");
            append_json_base64_c_array(out, u8"digest", digest, digest_size);
            append_u8_z(out, u8"},");
            append_json_escaped_base64_field(out, u8"signature", signature);
            append_u8_z(out, u8"}}");
            return true;
        }

        inline bool append_pem_certificate_from_raw_base64(byte_vector& out, byte_vector const& raw_base64) noexcept
        {
            if(raw_base64.empty()) [[unlikely]] { return false; }

            append_u8_z(out, u8"-----BEGIN CERTIFICATE-----\n");
            auto curr{raw_base64.data()};
            auto const last{raw_base64.data() + raw_base64.size()};
            while(curr != last)
            {
                auto const chunk_size{static_cast<::std::size_t>(last - curr) < 64uz ? static_cast<::std::size_t>(last - curr) : 64uz};
                ::uwsign::uwsign::wasm::details::append_bytes(out, curr, curr + chunk_size);
                append_u8_z(out, u8"\n");
                curr += chunk_size;
            }
            append_u8_z(out, u8"-----END CERTIFICATE-----\n");
            return true;
        }

        struct cosign_bundle_payload
        {
            byte_vector signature{};
            byte_vector certificate{};
            byte_vector certificate_chain{};
            byte_vector digest{};
            bool has_digest{};
        };

        inline bool parse_cosign_legacy_bundle(::std::byte const* first,
                                               ::std::byte const* last,
                                               cosign_bundle_payload& out,
                                               u8string_view& error) noexcept
        {
            byte_vector signature_b64{};
            if(!find_json_string_value(first, last, u8"base64Signature", sizeof(u8"base64Signature") - 1uz, signature_b64, error))
            {
                return false;
            }

            if(!base64_decode(signature_b64, out.signature) || out.signature.empty()) [[unlikely]]
            {
                error = u8"cosign legacy bundle has an invalid base64Signature.";
                return false;
            }

            byte_vector cert_field{};
            u8string_view cert_error{};
            if(find_json_string_value(first, last, u8"cert", sizeof(u8"cert") - 1uz, cert_field, cert_error))
            {
                byte_vector decoded_cert{};
                if(base64_decode(cert_field, decoded_cert) && !decoded_cert.empty())
                {
                    out.certificate = ::std::move(decoded_cert);
                }
                else
                {
                    out.certificate = ::std::move(cert_field);
                }
            }

            return true;
        }

        inline bool parse_sigstore_message_bundle(::std::byte const* first,
                                                  ::std::byte const* last,
                                                  cosign_bundle_payload& out,
                                                  u8string_view& error) noexcept
        {
            auto const message_signature_pos{find_json_key(first, last, u8"messageSignature", sizeof(u8"messageSignature") - 1uz)};
            if(message_signature_pos == last) { return false; }

            byte_vector signature_b64{};
            if(!find_json_string_value(message_signature_pos, last, u8"signature", sizeof(u8"signature") - 1uz, signature_b64, error))
            {
                return false;
            }

            if(!base64_decode(signature_b64, out.signature) || out.signature.empty()) [[unlikely]]
            {
                error = u8"Sigstore bundle has an invalid message signature.";
                return false;
            }

            byte_vector digest_b64{};
            u8string_view digest_error{};
            if(find_json_string_value(message_signature_pos, last, u8"digest", sizeof(u8"digest") - 1uz, digest_b64, digest_error))
            {
                out.has_digest = base64_decode(digest_b64, out.digest) && out.digest.size() == 32uz;
                if(!out.has_digest) [[unlikely]]
                {
                    error = u8"Sigstore bundle has an unsupported message digest.";
                    return false;
                }
            }

            auto cert_search_begin{first};
            auto const x509_chain_pos{find_json_key(first, message_signature_pos, u8"x509CertificateChain", sizeof(u8"x509CertificateChain") - 1uz)};
            auto const certificate_pos{find_json_key(first, message_signature_pos, u8"certificate", sizeof(u8"certificate") - 1uz)};
            if(x509_chain_pos != message_signature_pos) { cert_search_begin = x509_chain_pos; }
            else if(certificate_pos != message_signature_pos) { cert_search_begin = certificate_pos; }

            if(cert_search_begin != first)
            {
                auto curr{cert_search_begin};
                bool first_cert{true};
                for(;;)
                {
                    byte_vector raw_b64{};
                    ::std::byte const* next{};
                    u8string_view raw_error{};
                    if(!find_json_string_value(curr, message_signature_pos, u8"rawBytes", sizeof(u8"rawBytes") - 1uz, raw_b64, next, raw_error)) { break; }

                    if(first_cert)
                    {
                        if(!append_pem_certificate_from_raw_base64(out.certificate, raw_b64)) [[unlikely]]
                        {
                            error = u8"Sigstore bundle certificate is empty.";
                            return false;
                        }
                        first_cert = false;
                    }
                    else if(!append_pem_certificate_from_raw_base64(out.certificate_chain, raw_b64)) [[unlikely]]
                    {
                        error = u8"Sigstore bundle certificate chain is invalid.";
                        return false;
                    }

                    curr = next;
                }
            }

            return true;
        }

        inline bool parse_cosign_bundle(byte_vector const& payload, cosign_bundle_payload& out, u8string_view& error) noexcept
        {
            out = {};
            auto first{payload.data()};
            auto last{payload.data() + payload.size()};
            first = skip_json_space(first, last);
            if(first == last || !json_byte_equal(*first, u8'{')) { return false; }

            if(parse_cosign_legacy_bundle(first, last, out, error)) { return true; }
            out = {};
            return parse_sigstore_message_bundle(first, last, out, error);
        }

        inline bool digest_stripped_module(byte_vector const& stripped_module, ::std::byte* digest, u8string_view& error) noexcept
        {
            auto const status{::uwsign::uwsign::crypto::sha256(stripped_module.data(), stripped_module.size(), digest)};
            if(!status.ok) [[unlikely]]
            {
                error = status.message;
                return false;
            }

            return true;
        }

        inline bool sign_command(command_options const& options, auto&& stm) noexcept
        {
            try
            {
                auto module{load_file(options.input)};
                ::uwsign::uwsign::wasm::signature_section_result stripped{};
                u8string_view error{};
                if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(module.data(), module.data() + module.size(), stripped, error)) [[unlikely]]
                {
                    print_error(stm, error);
                    return false;
                }

                auto private_key{load_file(options.key)};
                byte_vector certificate{};
                if(!options.certificate.empty()) { certificate = load_file(options.certificate); }
                byte_vector certificate_chain{};
                if(!options.certificate_chain.empty()) { certificate_chain = load_file(options.certificate_chain); }

                ::std::byte digest[32uz]{};
                u8string_view digest_error{};
                if(!digest_stripped_module(stripped.stripped_module, digest, digest_error)) [[unlikely]]
                {
                    print_error(stm, digest_error);
                    return false;
                }

                byte_vector signature{};
                char8_t const* algorithm{};
                ::uwsign::uwsign::crypto::openssl_status sign_status{};
                if(certificate.empty())
                {
                    sign_status = ::uwsign::uwsign::crypto::sign_with_private_key(private_key.data(),
                                                                                  private_key.size(),
                                                                                  stripped.stripped_module.data(),
                                                                                  stripped.stripped_module.size(),
                                                                                  signature,
                                                                                  algorithm);
                }
                else
                {
                    sign_status = ::uwsign::uwsign::crypto::sign_with_private_key_and_certificate(private_key.data(),
                                                                                                  private_key.size(),
                                                                                                  certificate.data(),
                                                                                                  certificate.size(),
                                                                                                  stripped.stripped_module.data(),
                                                                                                  stripped.stripped_module.size(),
                                                                                                  signature,
                                                                                                  algorithm);
                }
                if(!sign_status.ok) [[unlikely]]
                {
                    print_error(stm, sign_status.message);
                    return false;
                }

                byte_vector payload{};
                if(!::uwsign::uwsign::sign::payload::encode(algorithm,
                                                            digest,
                                                            sizeof(digest),
                                                            signature.data(),
                                                            signature.size(),
                                                            certificate.data(),
                                                            certificate.size(),
                                                            certificate_chain.data(),
                                                            certificate_chain.size(),
                                                            payload,
                                                            error)) [[unlikely]]
                {
                    print_error(stm, error);
                    return false;
                }

                if(!options.output_signature.empty())
                {
                    byte_vector signature_output{};
                    if(options.base64_output)
                    {
                        base64_encode(signature, signature_output);
                        write_file(options.output_signature, signature_output);
                    }
                    else
                    {
                        write_file(options.output_signature, signature);
                    }
                    print_info(stm, u8"Detached signature written.");
                }

                if(!options.output_certificate.empty())
                {
                    if(certificate.empty()) [[unlikely]]
                    {
                        print_error(stm, u8"--output-certificate requires --certificate while signing.");
                        return false;
                    }
                    byte_vector certificate_output{};
                    if(options.base64_output)
                    {
                        base64_encode(certificate, certificate_output);
                        write_file(options.output_certificate, certificate_output);
                    }
                    else
                    {
                        write_file(options.output_certificate, certificate);
                    }
                    print_info(stm, u8"Certificate written.");
                }

                if(!options.output_certificate_chain.empty())
                {
                    if(certificate_chain.empty()) [[unlikely]]
                    {
                        print_error(stm, u8"--output-certificate-chain requires --certificate-chain while signing.");
                        return false;
                    }
                    byte_vector certificate_chain_output{};
                    if(options.base64_output)
                    {
                        base64_encode(certificate_chain, certificate_chain_output);
                        write_file(options.output_certificate_chain, certificate_chain_output);
                    }
                    else
                    {
                        write_file(options.output_certificate_chain, certificate_chain);
                    }
                    print_info(stm, u8"Certificate chain written.");
                }

                byte_vector verification_material{};
                if(options.cosign_legacy_bundle_format && certificate.empty())
                {
                    auto const public_key_status{
                        ::uwsign::uwsign::crypto::export_public_key_from_private_key_pem(private_key.data(), private_key.size(), verification_material)};
                    if(!public_key_status.ok) [[unlikely]]
                    {
                        print_error(stm, public_key_status.message);
                        return false;
                    }
                }

                byte_vector output_payload{};
                if(options.sigstore_bundle_format)
                {
                    if(!make_sigstore_bundle(signature,
                                             digest,
                                             sizeof(digest),
                                             private_key,
                                             certificate,
                                             certificate_chain,
                                             output_payload,
                                             error)) [[unlikely]]
                    {
                        print_error(stm, error);
                        return false;
                    }
                }
                else if(options.cosign_legacy_bundle_format)
                {
                    make_cosign_legacy_bundle(signature, certificate.empty() ? verification_material : certificate, output_payload);
                }
                else
                {
                    copy_bytes(payload, output_payload);
                }

                if(!options.bundle.empty())
                {
                    write_file(options.bundle, output_payload);
                    print_info(stm, u8"Verification bundle written.");
                }

                auto const output_path{!options.wasm_output.empty() ? options.wasm_output : options.output};
                if(!output_path.empty())
                {
                    byte_vector signed_module{};
                    bool append_ok{};
                    if(options.replace_signature_sections)
                    {
                        append_ok = ::uwsign::uwsign::wasm::append_signature_section(signed_module,
                                                                                     module.data(),
                                                                                     module.data() + module.size(),
                                                                                     output_payload.data(),
                                                                                     output_payload.data() + output_payload.size(),
                                                                                     error);
                    }
                    else
                    {
                        append_ok = ::uwsign::uwsign::wasm::append_signature_section_preserve(signed_module,
                                                                                              module.data(),
                                                                                              module.data() + module.size(),
                                                                                              output_payload.data(),
                                                                                              output_payload.data() + output_payload.size(),
                                                                                              error);
                    }

                    if(!append_ok) [[unlikely]]
                    {
                        print_error(stm, error);
                        return false;
                    }

                    write_file(output_path, signed_module);
                    print_info(stm, u8"WASM signature section appended.");
                }

                return true;
            }
            catch(::std::exception const& e)
            {
                ::fast_io::io::perr(stm,
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                    u8"uwsign: ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    ::fast_io::mnp::code_cvt_os_c_str(e.what()),
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                    u8"\n");
                return false;
            }
        }

        inline bool verify_one_payload(::uwsign::uwsign::sign::payload::signature_payload_view const& decoded,
                                       byte_vector const& stripped_module,
                                       byte_vector const& public_key,
                                       byte_vector const& certificate,
                                       byte_vector const& certificate_chain,
                                       auto&& stm) noexcept
        {
            ::std::byte digest[32uz]{};
            u8string_view error{};
            if(!digest_stripped_module(stripped_module, digest, error)) [[unlikely]]
            {
                print_error(stm, error);
                return false;
            }

            if(!byte_equal(digest, decoded.digest.first, sizeof(digest))) [[unlikely]] { return false; }

            bool valid{};
            ::uwsign::uwsign::crypto::openssl_status status{};
            if(!certificate.empty())
            {
                if(!certificate_chain.empty())
                {
                    status = ::uwsign::uwsign::crypto::verify_with_certificate_chain_pem(certificate.data(),
                                                                                         certificate.size(),
                                                                                         certificate_chain.data(),
                                                                                         certificate_chain.size(),
                                                                                         stripped_module.data(),
                                                                                         stripped_module.size(),
                                                                                         decoded.signature.first,
                                                                                         decoded.signature.size(),
                                                                                         valid);
                }
                else
                {
                    status = ::uwsign::uwsign::crypto::verify_with_certificate_pem(certificate.data(),
                                                                                   certificate.size(),
                                                                                   stripped_module.data(),
                                                                                   stripped_module.size(),
                                                                                   decoded.signature.first,
                                                                                   decoded.signature.size(),
                                                                                   valid);
                }
            }
            else if(!public_key.empty())
            {
                status = ::uwsign::uwsign::crypto::verify_with_public_key_pem(public_key.data(),
                                                                              public_key.size(),
                                                                              stripped_module.data(),
                                                                              stripped_module.size(),
                                                                              decoded.signature.first,
                                                                              decoded.signature.size(),
                                                                              valid);
            }
            else if(!decoded.certificate.empty())
            {
                if(!certificate_chain.empty())
                {
                    byte_vector chain{};
                    make_certificate_chain_with_embedded_intermediates(chain, decoded.certificate_chain, certificate_chain);
                    status = ::uwsign::uwsign::crypto::verify_with_certificate_chain_pem(decoded.certificate.first,
                                                                                         decoded.certificate.size(),
                                                                                         chain.data(),
                                                                                         chain.size(),
                                                                                         stripped_module.data(),
                                                                                         stripped_module.size(),
                                                                                         decoded.signature.first,
                                                                                         decoded.signature.size(),
                                                                                         valid);
                }
                else
                {
                    return false;
                }
            }
            else
            {
                print_error(stm, u8"no trusted public key, certificate, or certificate chain is available for verification.");
                return false;
            }

            if(!status.ok) [[unlikely]]
            {
                print_error(stm, status.message);
                return false;
            }

            return valid;
        }

        inline bool verify_detached_signature(byte_vector const& stripped_module,
                                              byte_vector const& signature,
                                              byte_vector const& public_key,
                                              byte_vector const& certificate,
                                              byte_vector const& certificate_chain,
                                              auto&& stm,
                                              bool report_errors = true) noexcept
        {
            bool valid{};
            ::uwsign::uwsign::crypto::openssl_status status{};
            if(!certificate.empty())
            {
                if(!certificate_chain.empty())
                {
                    status = ::uwsign::uwsign::crypto::verify_with_certificate_chain_pem(certificate.data(),
                                                                                         certificate.size(),
                                                                                         certificate_chain.data(),
                                                                                         certificate_chain.size(),
                                                                                         stripped_module.data(),
                                                                                         stripped_module.size(),
                                                                                         signature.data(),
                                                                                         signature.size(),
                                                                                         valid);
                }
                else
                {
                    status = ::uwsign::uwsign::crypto::verify_with_certificate_pem(certificate.data(),
                                                                                   certificate.size(),
                                                                                   stripped_module.data(),
                                                                                   stripped_module.size(),
                                                                                   signature.data(),
                                                                                   signature.size(),
                                                                                   valid);
                }
            }
            else if(!public_key.empty())
            {
                status = ::uwsign::uwsign::crypto::verify_with_public_key_pem(public_key.data(),
                                                                              public_key.size(),
                                                                              stripped_module.data(),
                                                                              stripped_module.size(),
                                                                              signature.data(),
                                                                              signature.size(),
                                                                              valid);
            }
            else
            {
                if(report_errors) { print_error(stm, u8"detached signature verification requires --key or --certificate."); }
                return false;
            }

            if(!status.ok) [[unlikely]]
            {
                if(report_errors) { print_error(stm, status.message); }
                return false;
            }

            return valid;
        }

        inline bool verify_detached_signature_auto(byte_vector const& stripped_module,
                                                   byte_vector const& signature,
                                                   byte_vector const& public_key,
                                                   byte_vector const& certificate,
                                                   byte_vector const& certificate_chain,
                                                   auto&& stm) noexcept
        {
            if(verify_detached_signature(stripped_module, signature, public_key, certificate, certificate_chain, stm, false)) { return true; }

            byte_vector decoded_signature{};
            if(!base64_decode(signature, decoded_signature)) { return false; }
            if(decoded_signature.empty()) { return false; }
            return verify_detached_signature(stripped_module, decoded_signature, public_key, certificate, certificate_chain, stm);
        }

        inline bool verify_cosign_bundle_payload(cosign_bundle_payload const& decoded,
                                                 byte_vector const& stripped_module,
                                                 byte_vector const& public_key,
                                                 byte_vector const& certificate,
                                                 byte_vector const& certificate_chain,
                                                 auto&& stm) noexcept
        {
            if(decoded.has_digest)
            {
                ::std::byte digest[32uz]{};
                u8string_view error{};
                if(!digest_stripped_module(stripped_module, digest, error)) [[unlikely]]
                {
                    print_error(stm, error);
                    return false;
                }

                if(!byte_equal(digest, decoded.digest.data(), sizeof(digest))) [[unlikely]] { return false; }
            }

            if(!certificate.empty())
            {
                if(verify_detached_signature(stripped_module, decoded.signature, public_key, certificate, certificate_chain, stm, false))
                {
                    return true;
                }
                return false;
            }

            if(!public_key.empty())
            {
                return verify_detached_signature(stripped_module, decoded.signature, public_key, certificate, certificate_chain, stm, false);
            }

            if(decoded.certificate.empty() || certificate_chain.empty()) { return false; }

            byte_vector chain{};
            make_certificate_chain_with_embedded_intermediates(chain, decoded.certificate_chain, certificate_chain);
            return verify_detached_signature(stripped_module, decoded.signature, public_key, decoded.certificate, chain, stm, false);
        }

        inline bool verify_command(command_options const& options, auto&& stm) noexcept
        {
            try
            {
                auto module{load_file(options.input)};
                ::uwsign::uwsign::wasm::signature_section_result stripped{};
                u8string_view error{};
                if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(module.data(), module.data() + module.size(), stripped, error)) [[unlikely]]
                {
                    print_error(stm, error);
                    return false;
                }

                byte_vector public_key{};
                byte_vector certificate{};
                byte_vector certificate_chain{};
                if(!options.key.empty()) { public_key = load_file(options.key); }
                if(!options.certificate.empty()) { certificate = load_file(options.certificate); }
                if(!options.certificate_chain.empty()) { certificate_chain = load_file(options.certificate_chain); }

                if(!options.signature.empty())
                {
                    auto detached_signature{load_file(options.signature)};
                    if(!verify_detached_signature_auto(stripped.stripped_module, detached_signature, public_key, certificate, certificate_chain, stm)) [[unlikely]]
                    {
                        print_error(stm, u8"detached signature verification failed.");
                        return false;
                    }

                    print_info(stm, u8"Detached WASM signature verified.");
                    return true;
                }

                if(!options.bundle.empty())
                {
                    stripped.signature_payloads.clear();
                    stripped.signature_payloads.emplace_back(load_file(options.bundle));
                }

                if(stripped.signature_payloads.empty()) [[unlikely]]
                {
                    print_error(stm, u8"no wasm_uwsign custom section or --bundle found.");
                    return false;
                }

                bool any_valid{};
                u8string_view last_decode_error{};
                for(auto curr{stripped.signature_payloads.crbegin()}; curr != stripped.signature_payloads.crend(); ++curr)
                {
                    auto const& curr_payload{*curr};
                    ::uwsign::uwsign::sign::payload::signature_payload_view decoded{};
                    if(::uwsign::uwsign::sign::payload::decode(curr_payload.data(), curr_payload.data() + curr_payload.size(), decoded, error))
                    {
                        if(verify_one_payload(decoded, stripped.stripped_module, public_key, certificate, certificate_chain, stm))
                        {
                            any_valid = true;
                            break;
                        }

                        continue;
                    }

                    last_decode_error = error;

                    cosign_bundle_payload cosign_payload{};
                    u8string_view cosign_error{};
                    if(!parse_cosign_bundle(curr_payload, cosign_payload, cosign_error))
                    {
                        if(!cosign_error.empty()) { last_decode_error = cosign_error; }
                        continue;
                    }

                    if(verify_cosign_bundle_payload(cosign_payload, stripped.stripped_module, public_key, certificate, certificate_chain, stm))
                    {
                        any_valid = true;
                        break;
                    }
                }

                if(!any_valid) [[unlikely]]
                {
                    if(!last_decode_error.empty())
                    {
                        print_error(stm, last_decode_error);
                    }
                    print_error(stm, u8"signature verification failed.");
                    return false;
                }

                print_info(stm, u8"WASM signature verified.");
                return true;
            }
            catch(::std::exception const& e)
            {
                ::fast_io::io::perr(stm,
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL_AND_SET_WHITE),
                                    u8"uwsign: ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_WHITE),
                                    ::fast_io::mnp::code_cvt_os_c_str(e.what()),
                                    ::fast_io::mnp::cond(::uwsign::uwsign::utils::ansies::put_color, UWSIGN_COLOR_U8_RST_ALL),
                                    u8"\n");
                return false;
            }
        }
    }  // namespace details

    inline execution_result execute_from_cmdline() noexcept
    {
        auto u8log_output_osr{::fast_io::operations::output_stream_ref(::uwsign::uwsign::io::u8log_output)};
        ::fast_io::operations::decay::stream_ref_decay_lock_guard u8log_output_lg{
            ::fast_io::operations::decay::output_stream_mutex_ref_decay(u8log_output_osr)};
        auto u8log_output_ul{::fast_io::operations::decay::output_stream_unlocked_ref_decay(u8log_output_osr)};

        command_options options{};
        u8string_view error{};
        if(!details::collect_options(options, error)) [[unlikely]]
        {
            details::print_error(u8log_output_ul, error);
            return execution_result::failed;
        }

        auto const ok{options.sign_mode ? details::sign_command(options, u8log_output_ul) : details::verify_command(options, u8log_output_ul)};
        return ok ? execution_result::ok : execution_result::failed;
    }
}  // namespace uwsign::uwsign::sign

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
# include <uwsign/uwsign_predefine/utils/ansies/uwsign_color_pop_macro.h>
#endif
