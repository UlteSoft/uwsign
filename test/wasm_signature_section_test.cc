/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <memory>

#include <uwsign/uwsign/wasm/signature_section.h>

namespace
{
    using byte_vector = ::uwsign::uwsign::wasm::byte_vector;

    [[nodiscard]] byte_vector bytes(::std::initializer_list<unsigned char> values)
    {
        byte_vector out{};
        out.reserve(values.size());
        for(auto const value: values) { out.emplace_back(static_cast<::std::byte>(value)); }
        return out;
    }

    [[nodiscard]] byte_vector ascii_bytes(char const* str)
    {
        byte_vector out{};
        auto const size{__builtin_strlen(str)};
        out.reserve(size);
        auto const first{reinterpret_cast<::std::byte const*>(str)};
        for(::std::size_t i{}; i != size; ++i) { out.emplace_back(first[i]); }
        return out;
    }

    [[nodiscard]] byte_vector minimal_module()
    {
        return bytes({0x00u, 0x61u, 0x73u, 0x6du, 0x01u, 0x00u, 0x00u, 0x00u});
    }

    [[nodiscard]] bool byte_equal(byte_vector const& a, byte_vector const& b) noexcept
    {
        if(a.size() != b.size()) { return false; }
        return a.empty() || __builtin_memcmp(a.data(), b.data(), a.size()) == 0;
    }

    [[nodiscard]] bool contains(byte_vector const& haystack, char const* needle) noexcept
    {
        auto const needle_size{__builtin_strlen(needle)};
        if(needle_size == 0uz) { return true; }
        if(haystack.size() < needle_size) { return false; }

        auto const needle_bytes{reinterpret_cast<::std::byte const*>(needle)};
        auto const search_last{haystack.size() - needle_size};
        for(::std::size_t i{}; i <= search_last; ++i)
        {
            if(__builtin_memcmp(haystack.data() + i, needle_bytes, needle_size) == 0) { return true; }
        }
        return false;
    }

    [[nodiscard]] bool append_custom(byte_vector& out,
                                     byte_vector const& module,
                                     char8_t const* name,
                                     ::std::size_t name_size,
                                     byte_vector const& payload,
                                     ::uwsign::uwsign::wasm::u8string_view& error) noexcept
    {
        ::std::byte empty{};
        auto const payload_first{payload.empty() ? ::std::addressof(empty) : payload.data()};
        auto const payload_last{payload.empty() ? ::std::addressof(empty) : payload.data() + payload.size()};
        return ::uwsign::uwsign::wasm::append_custom_section(out,
                                                            module.data(),
                                                            module.data() + module.size(),
                                                            name,
                                                            name_size,
                                                            payload_first,
                                                            payload_last,
                                                            error);
    }

    [[nodiscard]] bool append_signature_preserve(byte_vector& out,
                                                 byte_vector const& module,
                                                 byte_vector const& payload,
                                                 ::uwsign::uwsign::wasm::u8string_view& error) noexcept
    {
        ::std::byte empty{};
        auto const payload_first{payload.empty() ? ::std::addressof(empty) : payload.data()};
        auto const payload_last{payload.empty() ? ::std::addressof(empty) : payload.data() + payload.size()};
        return ::uwsign::uwsign::wasm::append_signature_section_preserve(out,
                                                                        module.data(),
                                                                        module.data() + module.size(),
                                                                        payload_first,
                                                                        payload_last,
                                                                        error);
    }

    [[nodiscard]] bool append_signature_replace(byte_vector& out,
                                                byte_vector const& module,
                                                byte_vector const& payload,
                                                ::uwsign::uwsign::wasm::u8string_view& error) noexcept
    {
        ::std::byte empty{};
        auto const payload_first{payload.empty() ? ::std::addressof(empty) : payload.data()};
        auto const payload_last{payload.empty() ? ::std::addressof(empty) : payload.data() + payload.size()};
        return ::uwsign::uwsign::wasm::append_signature_section(out,
                                                               module.data(),
                                                               module.data() + module.size(),
                                                               payload_first,
                                                               payload_last,
                                                               error);
    }

    void print_u8(::uwsign::uwsign::wasm::u8string_view str) noexcept
    {
        ::std::fwrite(str.data(), 1uz, str.size(), stderr);
    }

    [[nodiscard]] bool fail(char const* name, ::uwsign::uwsign::wasm::u8string_view reason) noexcept
    {
        ::std::fputs("[fail] ", stderr);
        ::std::fputs(name, stderr);
        ::std::fputs(": ", stderr);
        print_u8(reason);
        ::std::fputc('\n', stderr);
        return false;
    }

    [[nodiscard]] bool test_strip_and_extract() noexcept
    {
        constexpr char const* test_name{"strip_and_extract"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};

        byte_vector with_producers{};
        auto producers_payload{ascii_bytes("toolchain")};
        if(!append_custom(with_producers, module, u8"producers", sizeof(u8"producers") - 1uz, producers_payload, error)) { return fail(test_name, error); }

        byte_vector with_first{};
        auto first_payload{ascii_bytes("first-bundle")};
        if(!append_signature_preserve(with_first, with_producers, first_payload, error)) { return fail(test_name, error); }

        auto mixed{with_first};
        mixed.emplace_back(static_cast<::std::byte>(1u));
        mixed.emplace_back(static_cast<::std::byte>(1u));
        mixed.emplace_back(static_cast<::std::byte>(0u));

        byte_vector with_second{};
        auto second_payload{ascii_bytes("second-bundle")};
        if(!append_signature_preserve(with_second, mixed, second_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(with_second.data(), with_second.data() + with_second.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(result.signature_payloads.size() != 2uz) { return fail(test_name, u8"expected two signature payloads."); }
        if(!byte_equal(result.signature_payloads[0], first_payload)) { return fail(test_name, u8"first payload mismatch."); }
        if(!byte_equal(result.signature_payloads[1], second_payload)) { return fail(test_name, u8"second payload mismatch."); }
        if(contains(result.stripped_module, "wasm_uwsign")) { return fail(test_name, u8"stripped module still contains wasm_uwsign."); }
        if(!contains(result.stripped_module, "producers")) { return fail(test_name, u8"non-signature custom section was removed."); }
        return true;
    }

    [[nodiscard]] bool test_append_replaces_existing() noexcept
    {
        constexpr char const* test_name{"append_replaces_existing"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};

        byte_vector old_signed{};
        if(!append_signature_preserve(old_signed, module, ascii_bytes("old-bundle"), error)) { return fail(test_name, error); }

        byte_vector signed_module{};
        auto new_payload{ascii_bytes("new-bundle")};
        if(!append_signature_replace(signed_module, old_signed, new_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(signed_module.data(), signed_module.data() + signed_module.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(result.signature_payloads.size() != 1uz) { return fail(test_name, u8"expected one replacement signature payload."); }
        if(!byte_equal(result.signature_payloads[0], new_payload)) { return fail(test_name, u8"replacement payload mismatch."); }
        if(!byte_equal(result.stripped_module, minimal_module())) { return fail(test_name, u8"stripped replacement module mismatch."); }
        return true;
    }

    [[nodiscard]] bool test_cosign_section_compatibility() noexcept
    {
        constexpr char const* test_name{"cosign_section_compatibility"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};

        byte_vector cosign_signed{};
        auto old_payload{ascii_bytes("cosign-bundle")};
        if(!append_custom(cosign_signed, module, u8"wasm-usign", sizeof(u8"wasm-usign") - 1uz, old_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(cosign_signed.data(), cosign_signed.data() + cosign_signed.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(result.signature_payloads.size() != 1uz) { return fail(test_name, u8"expected one cosign payload."); }
        if(!byte_equal(result.signature_payloads[0], old_payload)) { return fail(test_name, u8"cosign payload mismatch."); }
        if(contains(result.stripped_module, "wasm-usign")) { return fail(test_name, u8"stripped module still contains wasm-usign."); }

        byte_vector replaced{};
        auto new_payload{ascii_bytes("uwsign-bundle")};
        if(!append_signature_replace(replaced, cosign_signed, new_payload, error)) { return fail(test_name, error); }
        if(contains(replaced, "wasm-usign")) { return fail(test_name, u8"replacement kept wasm-usign section."); }
        if(!contains(replaced, "wasm_uwsign")) { return fail(test_name, u8"replacement did not write wasm_uwsign section."); }

        return true;
    }

    [[nodiscard]] bool test_ignores_other_custom_section_names() noexcept
    {
        constexpr char const* test_name{"ignores_other_custom_section_names"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};

        byte_vector other_signed{};
        auto old_payload{ascii_bytes("other-bundle")};
        if(!append_custom(other_signed, module, u8"not-uwsign", sizeof(u8"not-uwsign") - 1uz, old_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(other_signed.data(), other_signed.data() + other_signed.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(!result.signature_payloads.empty()) { return fail(test_name, u8"non-uwsign section was extracted as a signature."); }
        if(!contains(result.stripped_module, "not-uwsign")) { return fail(test_name, u8"non-uwsign custom section was removed."); }

        byte_vector replaced{};
        auto new_payload{ascii_bytes("uwsign-bundle")};
        if(!append_signature_replace(replaced, other_signed, new_payload, error)) { return fail(test_name, error); }
        if(!contains(replaced, "not-uwsign")) { return fail(test_name, u8"replacement removed non-uwsign custom section."); }
        if(!contains(replaced, "wasm_uwsign")) { return fail(test_name, u8"replacement did not write wasm_uwsign section."); }

        return true;
    }

    [[nodiscard]] bool test_append_preserves_existing() noexcept
    {
        constexpr char const* test_name{"append_preserves_existing"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};

        byte_vector first_signed{};
        auto first_payload{ascii_bytes("first-bundle")};
        if(!append_signature_preserve(first_signed, module, first_payload, error)) { return fail(test_name, error); }

        byte_vector second_signed{};
        auto second_payload{ascii_bytes("second-bundle")};
        if(!append_signature_preserve(second_signed, first_signed, second_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(second_signed.data(), second_signed.data() + second_signed.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(result.signature_payloads.size() != 2uz) { return fail(test_name, u8"expected preserved multi-sign payloads."); }
        if(!byte_equal(result.signature_payloads[0], first_payload)) { return fail(test_name, u8"first preserved payload mismatch."); }
        if(!byte_equal(result.signature_payloads[1], second_payload)) { return fail(test_name, u8"second preserved payload mismatch."); }
        return true;
    }

    [[nodiscard]] bool test_empty_payload_section() noexcept
    {
        constexpr char const* test_name{"empty_payload_section"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto module{minimal_module()};
        byte_vector empty_payload{};

        byte_vector signed_module{};
        if(!append_signature_preserve(signed_module, module, empty_payload, error)) { return fail(test_name, error); }

        ::uwsign::uwsign::wasm::signature_section_result result{};
        if(!::uwsign::uwsign::wasm::strip_and_extract_signature_sections(signed_module.data(), signed_module.data() + signed_module.size(), result, error))
        {
            return fail(test_name, error);
        }

        if(result.signature_payloads.size() != 1uz) { return fail(test_name, u8"expected one empty signature payload."); }
        if(!result.signature_payloads[0].empty()) { return fail(test_name, u8"empty signature payload was not empty."); }
        if(!byte_equal(result.stripped_module, minimal_module())) { return fail(test_name, u8"stripped empty-payload module mismatch."); }
        return true;
    }

    [[nodiscard]] bool test_rejects_invalid_module() noexcept
    {
        constexpr char const* test_name{"rejects_invalid_module"};
        ::uwsign::uwsign::wasm::u8string_view error{};
        auto invalid{ascii_bytes("not wasm")};
        byte_vector stripped{};
        if(::uwsign::uwsign::wasm::strip_signature_sections(invalid.data(), invalid.data() + invalid.size(), stripped, error))
        {
            return fail(test_name, u8"invalid module was accepted.");
        }
        return true;
    }
}  // namespace

int main()
{
    if(!test_strip_and_extract()) { return 1; }
    if(!test_append_replaces_existing()) { return 1; }
    if(!test_cosign_section_compatibility()) { return 1; }
    if(!test_ignores_other_custom_section_names()) { return 1; }
    if(!test_append_preserves_existing()) { return 1; }
    if(!test_empty_payload_section()) { return 1; }
    if(!test_rejects_invalid_module()) { return 1; }

    ::std::fputs("[pass] wasm signature section tests\n", stderr);
    return 0;
}
