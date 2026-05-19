/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     1.0.0.0
 * @copyright   APL-2.0 License
 */

/****************************************
 *  _   _ __        ____     __ __  __  *
 * | | | |\ \      / /\ \   / /|  \/  | *
 * | | | | \ \ /\ / /  \ \ / / | |\/| | *
 * | |_| |  \ V  V /    \ V /  | |  | | *
 *  \___/    \_/\_/      \_/   |_|  |_| *
 *                                      *
 ****************************************/

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace
{
    namespace fs = ::std::filesystem;

    [[nodiscard]] ::std::string quote_arg(::std::string_view value)
    {
#if defined(_WIN32)
        ::std::string out{"\""};
        for(char const ch: value)
        {
            if(ch == '"') { out += "\\\""; }
            else { out += ch; }
        }
        out += '"';
        return out;
#else
        ::std::string out{"'"};
        for(char const ch: value)
        {
            if(ch == '\'') { out += "'\\''"; }
            else { out += ch; }
        }
        out += "'";
        return out;
#endif
    }

    [[nodiscard]] ::std::string quote_path(fs::path const& value)
    {
        return quote_arg(value.string());
    }

    [[nodiscard]] bool fail(::std::string_view msg)
    {
        ::std::fputs("[fail] cli_integration: ", stderr);
        ::std::fwrite(msg.data(), 1uz, msg.size(), stderr);
        ::std::fputc('\n', stderr);
        return false;
    }

    [[nodiscard]] bool run_shell(::std::string const& cmd)
    {
        auto const rc{::std::system(cmd.c_str())};
        if(rc != 0)
        {
            ::std::fputs("[fail] command failed: ", stderr);
            ::std::fputs(cmd.c_str(), stderr);
            ::std::fputc('\n', stderr);
            return false;
        }
        return true;
    }

    [[nodiscard]] bool run_shell_expect_fail(::std::string const& cmd)
    {
        auto const rc{::std::system(cmd.c_str())};
        if(rc == 0)
        {
            ::std::fputs("[fail] command unexpectedly succeeded: ", stderr);
            ::std::fputs(cmd.c_str(), stderr);
            ::std::fputc('\n', stderr);
            return false;
        }
        return true;
    }

    [[nodiscard]] bool run_in(fs::path const& workdir, ::std::string const& cmd)
    {
        return run_shell("cd " + quote_path(workdir) + " && " + cmd);
    }

    [[nodiscard]] bool run_in_expect_fail(fs::path const& workdir, ::std::string const& cmd)
    {
        return run_shell_expect_fail("cd " + quote_path(workdir) + " && " + cmd);
    }

    [[nodiscard]] bool write_bytes(fs::path const& path, ::std::vector<unsigned char> const& bytes)
    {
        auto file{::std::fopen(path.string().c_str(), "wb")};
        if(file == nullptr) { return fail("failed to open output file"); }

        auto const written{bytes.empty() ? 0uz : ::std::fwrite(bytes.data(), 1uz, bytes.size(), file)};
        auto const close_rc{::std::fclose(file)};
        if(written != bytes.size() || close_rc != 0) { return fail("failed to write output file"); }
        return true;
    }

    [[nodiscard]] bool read_bytes(fs::path const& path, ::std::vector<unsigned char>& out)
    {
        out.clear();
        auto file{::std::fopen(path.string().c_str(), "rb")};
        if(file == nullptr) { return fail("failed to open input file"); }

        if(::std::fseek(file, 0, SEEK_END) != 0)
        {
            ::std::fclose(file);
            return fail("failed to seek input file");
        }

        auto const size_long{::std::ftell(file)};
        if(size_long < 0)
        {
            ::std::fclose(file);
            return fail("failed to get input file size");
        }

        if(::std::fseek(file, 0, SEEK_SET) != 0)
        {
            ::std::fclose(file);
            return fail("failed to rewind input file");
        }

        out.resize(static_cast<::std::size_t>(size_long));
        auto const read_size{out.empty() ? 0uz : ::std::fread(out.data(), 1uz, out.size(), file)};
        auto const close_rc{::std::fclose(file)};
        if(read_size != out.size() || close_rc != 0) { return fail("failed to read input file"); }
        return true;
    }

    [[nodiscard]] bool file_equal(fs::path const& lhs, fs::path const& rhs)
    {
        ::std::vector<unsigned char> lhs_bytes{};
        ::std::vector<unsigned char> rhs_bytes{};
        if(!read_bytes(lhs, lhs_bytes) || !read_bytes(rhs, rhs_bytes)) { return false; }
        return lhs_bytes == rhs_bytes;
    }

    [[nodiscard]] ::std::size_t count_bytes(::std::vector<unsigned char> const& haystack, ::std::string_view needle)
    {
        if(needle.empty()) { return 0uz; }

        ::std::size_t count{};
        auto curr{haystack.begin()};
        auto const needle_first{needle.begin()};
        auto const needle_last{needle.end()};
        for(;;)
        {
            curr = ::std::search(curr, haystack.end(), needle_first, needle_last);
            if(curr == haystack.end()) { return count; }
            ++count;
            ++curr;
        }
    }

    [[nodiscard]] bool contains_bytes(::std::vector<unsigned char> const& haystack, ::std::string_view needle)
    {
        return count_bytes(haystack, needle) != 0uz;
    }

    [[nodiscard]] unsigned base64_decode_value(unsigned char ch) noexcept
    {
        if(ch >= static_cast<unsigned char>('A') && ch <= static_cast<unsigned char>('Z')) { return ch - static_cast<unsigned char>('A'); }
        if(ch >= static_cast<unsigned char>('a') && ch <= static_cast<unsigned char>('z')) { return ch - static_cast<unsigned char>('a') + 26u; }
        if(ch >= static_cast<unsigned char>('0') && ch <= static_cast<unsigned char>('9')) { return ch - static_cast<unsigned char>('0') + 52u; }
        if(ch == static_cast<unsigned char>('+')) { return 62u; }
        if(ch == static_cast<unsigned char>('/')) { return 63u; }
        return 64u;
    }

    [[nodiscard]] bool is_base64_space(unsigned char ch) noexcept
    {
        return ch == static_cast<unsigned char>(' ') || ch == static_cast<unsigned char>('\n') || ch == static_cast<unsigned char>('\r') ||
               ch == static_cast<unsigned char>('\t');
    }

    [[nodiscard]] bool base64_decode(::std::vector<unsigned char> const& encoded, ::std::vector<unsigned char>& out)
    {
        out.clear();
        out.reserve((encoded.size() / 4uz) * 3uz);

        unsigned quartet[4uz]{};
        ::std::size_t quartet_size{};
        bool seen_padding{};

        for(auto const ch: encoded)
        {
            if(is_base64_space(ch)) { continue; }

            unsigned value{};
            if(ch == static_cast<unsigned char>('='))
            {
                value = 64u;
                seen_padding = true;
            }
            else
            {
                if(seen_padding) { return false; }
                value = base64_decode_value(ch);
                if(value == 64u) { return false; }
            }

            quartet[quartet_size++] = value;
            if(quartet_size != 4uz) { continue; }

            if(quartet[0] == 64u || quartet[1] == 64u) { return false; }

            out.emplace_back(static_cast<unsigned char>((quartet[0] << 2u) | (quartet[1] >> 4u)));
            if(quartet[2] != 64u)
            {
                out.emplace_back(static_cast<unsigned char>(((quartet[1] & 0x0Fu) << 4u) | (quartet[2] >> 2u)));
                if(quartet[3] != 64u) { out.emplace_back(static_cast<unsigned char>(((quartet[2] & 0x03u) << 6u) | quartet[3])); }
            }
            else if(quartet[3] != 64u)
            {
                return false;
            }

            quartet_size = 0uz;
        }

        return quartet_size == 0uz;
    }

    [[nodiscard]] bool json_string_field(::std::vector<unsigned char> const& json, ::std::string_view key, ::std::vector<unsigned char>& out)
    {
        out.clear();
        ::std::string const text{json.begin(), json.end()};
        auto const marker{"\"" + ::std::string{key} + "\":\""};
        auto const value_begin{text.find(marker)};
        if(value_begin == ::std::string::npos) { return false; }

        auto const first{value_begin + marker.size()};
        auto const last{text.find('"', first)};
        if(last == ::std::string::npos) { return false; }

        out.assign(text.begin() + static_cast<::std::ptrdiff_t>(first), text.begin() + static_cast<::std::ptrdiff_t>(last));
        return true;
    }

    void append_varuint32(::std::vector<unsigned char>& out, ::std::uint32_t value)
    {
        do
        {
            auto byte{static_cast<unsigned char>(value & 0x7Fu)};
            value >>= 7u;
            if(value != 0u) { byte = static_cast<unsigned char>(byte | 0x80u); }
            out.emplace_back(byte);
        } while(value != 0u);
    }

    [[nodiscard]] ::std::vector<unsigned char> make_custom_section(::std::vector<unsigned char> module,
                                                                   ::std::string_view name,
                                                                   ::std::string_view payload)
    {
        ::std::vector<unsigned char> section_payload{};
        append_varuint32(section_payload, static_cast<::std::uint32_t>(name.size()));
        section_payload.insert(section_payload.end(), name.begin(), name.end());
        section_payload.insert(section_payload.end(), payload.begin(), payload.end());

        module.emplace_back(0u);
        append_varuint32(module, static_cast<::std::uint32_t>(section_payload.size()));
        module.insert(module.end(), section_payload.begin(), section_payload.end());
        return module;
    }

    [[nodiscard]] bool make_tampered(fs::path const& source, fs::path const& target)
    {
        ::std::vector<unsigned char> data{};
        if(!read_bytes(source, data)) { return false; }

        constexpr unsigned char header[]{0x00u, 0x61u, 0x73u, 0x6du, 0x01u, 0x00u, 0x00u, 0x00u};
        if(data.size() < sizeof(header) || ::std::memcmp(data.data(), header, sizeof(header)) != 0) { return fail("signed output is not a wasm module"); }

        constexpr ::std::string_view signature_name{"wasm_uwsign"};
        auto const name_pos_iter{::std::search(data.begin(), data.end(), signature_name.begin(), signature_name.end())};
        if(name_pos_iter == data.end()) { return fail("signed output does not contain wasm_uwsign"); }
        auto const name_pos{static_cast<::std::size_t>(name_pos_iter - data.begin())};

        for(::std::size_t i{sizeof(header)}; i != data.size(); ++i)
        {
            if(name_pos <= i && i < name_pos + signature_name.size()) { continue; }
            data[i] = static_cast<unsigned char>(data[i] ^ 0x01u);
            return write_bytes(target, data);
        }

        return fail("did not find a tamperable byte");
    }

    [[nodiscard]] fs::path sibling_uwsign(char const* argv0)
    {
        ::std::error_code ec{};
        auto self{fs::absolute(fs::path{argv0}, ec)};
        if(ec) { self = fs::path{argv0}; }

        auto bin{self.parent_path() / "uwsign"};
#if defined(_WIN32)
        bin += ".exe";
#endif
        return bin;
    }

    [[nodiscard]] fs::path make_workdir()
    {
        ::std::error_code ec{};
        auto root{fs::temp_directory_path(ec)};
        if(ec) { root = fs::current_path(); }

        auto const tick{::std::chrono::steady_clock::now().time_since_epoch().count()};
        auto dir{root / ("uwsign-cli-" + ::std::to_string(tick))};
        fs::remove_all(dir, ec);
        fs::create_directories(dir, ec);
        return dir;
    }
}  // namespace

int main(int, char** argv)
{
    auto const uwsign_bin{sibling_uwsign(argv[0])};
    if(!fs::exists(uwsign_bin)) { return fail("uwsign binary was not found") ? 0 : 1; }
    if(!run_shell("command -v openssl >/dev/null 2>&1")) { return 1; }

    auto const workdir{make_workdir()};
    if(workdir.empty()) { return fail("failed to create temporary test directory") ? 0 : 1; }

    constexpr unsigned char wasm_header[]{0x00u, 0x61u, 0x73u, 0x6du, 0x01u, 0x00u, 0x00u, 0x00u};
    ::std::vector<unsigned char> control_wasm{wasm_header, wasm_header + sizeof(wasm_header)};
    if(!write_bytes(workdir / "control.wasm", control_wasm)) { return 1; }

    auto const uwsign{quote_path(uwsign_bin)};

    if(!run_in(workdir, "openssl ecparam -name prime256v1 -genkey -noout -out key.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl pkey -in key.pem -pubout -out pub.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl req -new -x509 -key key.pem -out cert.pem -subj '/CN=uwsign-test' -days 1 >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl ecparam -name prime256v1 -genkey -noout -out root-key.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl req -new -x509 -key root-key.pem -out root-cert.pem -subj '/CN=uwsign-test-root' -days 1 >/dev/null 2>&1"))
    {
        return 1;
    }
    if(!run_in(workdir, "openssl ecparam -name prime256v1 -genkey -noout -out leaf-key.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl pkey -in leaf-key.pem -pubout -out leaf-pub.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl req -new -key leaf-key.pem -out leaf.csr -subj '/CN=uwsign-test-leaf' >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir,
               "openssl x509 -req -in leaf.csr -CA root-cert.pem -CAkey root-key.pem -CAcreateserial -out leaf-cert.pem -days 1 -sha256 >/dev/null 2>&1"))
    {
        return 1;
    }

    ::std::error_code ec{};
    fs::copy_file(workdir / "root-cert.pem", workdir / "leaf-chain.pem", fs::copy_options::overwrite_existing, ec);
    if(ec) { return fail("failed to create leaf-chain.pem") ? 0 : 1; }

    if(!run_in(workdir, "openssl ecparam -name prime256v1 -genkey -noout -out other-key.pem >/dev/null 2>&1")) { return 1; }
    if(!run_in(workdir, "openssl req -new -x509 -key other-key.pem -out other-cert.pem -subj '/CN=uwsign-test-other' -days 1 >/dev/null 2>&1")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input control.wasm --output signed1.wasm --key key.pem --certificate cert.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input signed1.wasm --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input signed1.wasm --certificate cert.pem")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input signed1.wasm")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --sign --input control.wasm --output mismatch.wasm --key key.pem --certificate other-cert.pem")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input - --wasm-output stdin_signed.wasm --key key.pem --certificate cert.pem < control.wasm")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input stdin_signed.wasm --key pub.pem")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input control.wasm --wasm-output - --key key.pem --certificate cert.pem > stdout_signed.wasm")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input stdout_signed.wasm --key pub.pem")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input control.wasm --bundle - --key key.pem --certificate cert.pem > stdout_bundle.uwsign")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle stdout_bundle.uwsign --key pub.pem")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input control.wasm --output-signature - --key key.pem --certificate cert.pem > stdout.sig")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --signature stdout.sig --key pub.pem")) { return 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --output-signature b64.sig --output-certificate b64-cert.pem --b64 --key key.pem --certificate cert.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --signature b64.sig --key pub.pem")) { return 1; }

    ::std::vector<unsigned char> b64_cert{};
    ::std::vector<unsigned char> decoded_cert{};
    if(!read_bytes(workdir / "b64-cert.pem", b64_cert) || !base64_decode(b64_cert, decoded_cert)) { return fail("failed to decode base64 certificate") ? 0 : 1; }
    if(!write_bytes(workdir / "b64-cert-decoded.pem", decoded_cert)) { return 1; }
    if(!file_equal(workdir / "cert.pem", workdir / "b64-cert-decoded.pem")) { return fail("decoded certificate mismatch") ? 0 : 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --output chain_signed.wasm --key leaf-key.pem --certificate leaf-cert.pem --certificate-chain leaf-chain.pem --output-certificate-chain exported-chain.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input chain_signed.wasm --key leaf-pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input chain_signed.wasm --certificate leaf-cert.pem --certificate-chain leaf-chain.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input chain_signed.wasm --certificate-chain leaf-chain.pem")) { return 1; }
    if(!file_equal(workdir / "leaf-chain.pem", workdir / "exported-chain.pem")) { return fail("exported certificate chain mismatch") ? 0 : 1; }

    if(!run_in(workdir, uwsign + " --sign --input signed1.wasm --output signed2.wasm --key key.pem --certificate cert.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input signed2.wasm --key pub.pem")) { return 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --wasm-output cosign_style.wasm --bundle bundle.uwsign --output-signature control.sig --output-certificate exported-cert.pem --key key.pem --certificate cert.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle bundle.uwsign --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input cosign_style.wasm --bundle bundle.uwsign --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --signature control.sig --key pub.pem")) { return 1; }
    if(!file_equal(workdir / "cert.pem", workdir / "exported-cert.pem")) { return fail("exported certificate mismatch") ? 0 : 1; }

    if(!run_in(workdir,
               uwsign + " --sign --input control.wasm --wasm-output cosign_legacy.wasm --bundle cosign_legacy.json --bundle-format cosign --key key.pem --certificate cert.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle cosign_legacy.json --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input cosign_legacy.wasm --key pub.pem")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input cosign_legacy.wasm")) { return 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --wasm-output cosign_legacy_pubkey.wasm --bundle cosign_legacy_pubkey.json --bundle-format cosign --key key.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle cosign_legacy_pubkey.json --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input cosign_legacy_pubkey.wasm --key pub.pem")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input cosign_legacy_pubkey.wasm")) { return 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --wasm-output sigstore_pubkey.wasm --bundle sigstore_pubkey.json --bundle-format cosign-v0.3 --key key.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle sigstore_pubkey.json --key pub.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input sigstore_pubkey.wasm --key pub.pem")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input sigstore_pubkey.wasm")) { return 1; }

    if(!run_in(workdir,
               uwsign +
                   " --sign --input control.wasm --wasm-output sigstore_cert.wasm --bundle sigstore_cert.json --bundle-format cosign-v0.3 --key leaf-key.pem --certificate leaf-cert.pem --certificate-chain leaf-chain.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle sigstore_cert.json --certificate leaf-cert.pem --certificate-chain leaf-chain.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input sigstore_cert.wasm --certificate leaf-cert.pem --certificate-chain leaf-chain.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input control.wasm --bundle sigstore_cert.json --certificate-chain leaf-chain.pem")) { return 1; }
    if(!run_in(workdir, uwsign + " --verify --input sigstore_cert.wasm --certificate-chain leaf-chain.pem")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input sigstore_cert.wasm")) { return 1; }

    if(!run_in(workdir, uwsign + " --sign --input signed2.wasm --wasm-output replaced.wasm --bundle replaced.uwsign --replace --key key.pem --certificate cert.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input replaced.wasm --key pub.pem")) { return 1; }

    auto other_custom{make_custom_section(control_wasm, "not-uwsign", "other-custom-bundle")};
    if(!write_bytes(workdir / "other_custom.wasm", other_custom)) { return 1; }
    if(!run_in(workdir, uwsign + " --sign --input other_custom.wasm --wasm-output other_custom_replaced.wasm --replace --key key.pem --certificate cert.pem"))
    {
        return 1;
    }
    if(!run_in(workdir, uwsign + " --verify --input other_custom_replaced.wasm --key pub.pem")) { return 1; }

    ::std::vector<unsigned char> signed2{};
    ::std::vector<unsigned char> replaced{};
    ::std::vector<unsigned char> cosign_style{};
    ::std::vector<unsigned char> cosign_legacy_json{};
    ::std::vector<unsigned char> cosign_legacy_wasm{};
    ::std::vector<unsigned char> cosign_legacy_pubkey_json{};
    ::std::vector<unsigned char> cosign_legacy_pubkey_wasm{};
    ::std::vector<unsigned char> sigstore_pubkey_json{};
    ::std::vector<unsigned char> sigstore_pubkey_wasm{};
    ::std::vector<unsigned char> sigstore_cert_json{};
    ::std::vector<unsigned char> sigstore_cert_wasm{};
    ::std::vector<unsigned char> other_custom_replaced{};

    if(!read_bytes(workdir / "signed2.wasm", signed2) || !read_bytes(workdir / "replaced.wasm", replaced) ||
       !read_bytes(workdir / "cosign_style.wasm", cosign_style) || !read_bytes(workdir / "cosign_legacy.json", cosign_legacy_json) ||
       !read_bytes(workdir / "cosign_legacy.wasm", cosign_legacy_wasm) || !read_bytes(workdir / "cosign_legacy_pubkey.json", cosign_legacy_pubkey_json) ||
       !read_bytes(workdir / "cosign_legacy_pubkey.wasm", cosign_legacy_pubkey_wasm) ||
       !read_bytes(workdir / "sigstore_pubkey.json", sigstore_pubkey_json) || !read_bytes(workdir / "sigstore_pubkey.wasm", sigstore_pubkey_wasm) ||
       !read_bytes(workdir / "sigstore_cert.json", sigstore_cert_json) || !read_bytes(workdir / "sigstore_cert.wasm", sigstore_cert_wasm) ||
       !read_bytes(workdir / "other_custom_replaced.wasm", other_custom_replaced))
    {
        return 1;
    }

    if(count_bytes(signed2, "wasm_uwsign") != 2uz) { return fail("expected two wasm_uwsign sections in signed2.wasm") ? 0 : 1; }
    if(count_bytes(replaced, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in replaced.wasm") ? 0 : 1; }
    if(count_bytes(cosign_style, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in cosign_style.wasm") ? 0 : 1; }
    if(!contains_bytes(cosign_legacy_json, "\"base64Signature\"") || !contains_bytes(cosign_legacy_json, "\"cert\""))
    {
        return fail("cosign legacy bundle did not contain expected fields") ? 0 : 1;
    }
    if(count_bytes(cosign_legacy_wasm, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in cosign_legacy.wasm") ? 0 : 1; }
    ::std::vector<unsigned char> cosign_legacy_pubkey_cert_b64{};
    ::std::vector<unsigned char> cosign_legacy_pubkey_cert{};
    if(!contains_bytes(cosign_legacy_pubkey_json, "\"base64Signature\"") || !json_string_field(cosign_legacy_pubkey_json, "cert", cosign_legacy_pubkey_cert_b64) ||
       !base64_decode(cosign_legacy_pubkey_cert_b64, cosign_legacy_pubkey_cert) ||
       !contains_bytes(cosign_legacy_pubkey_cert, "BEGIN PUBLIC KEY"))
    {
        return fail("cosign legacy public-key bundle did not contain expected fields") ? 0 : 1;
    }
    if(count_bytes(cosign_legacy_pubkey_wasm, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in cosign_legacy_pubkey.wasm") ? 0 : 1; }
    if(!contains_bytes(sigstore_pubkey_json, "\"mediaType\":\"application/vnd.dev.sigstore.bundle.v0.3+json\"") ||
       !contains_bytes(sigstore_pubkey_json, "\"messageSignature\"") || !contains_bytes(sigstore_pubkey_json, "\"publicKey\"") ||
       !contains_bytes(sigstore_pubkey_json, "\"hint\"") || !contains_bytes(sigstore_pubkey_json, "\"digest\"") ||
       contains_bytes(sigstore_pubkey_json, "\"rawBytes\""))
    {
        return fail("sigstore public-key bundle did not contain expected v0.3 fields") ? 0 : 1;
    }
    if(count_bytes(sigstore_pubkey_wasm, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in sigstore_pubkey.wasm") ? 0 : 1; }
    if(!contains_bytes(sigstore_cert_json, "\"mediaType\":\"application/vnd.dev.sigstore.bundle.v0.3+json\"") ||
       !contains_bytes(sigstore_cert_json, "\"messageSignature\"") || !contains_bytes(sigstore_cert_json, "\"x509CertificateChain\"") ||
       !contains_bytes(sigstore_cert_json, "\"certificates\"") || !contains_bytes(sigstore_cert_json, "\"rawBytes\"") ||
       count_bytes(sigstore_cert_json, "\"rawBytes\"") != 2uz)
    {
        return fail("sigstore certificate bundle did not contain expected v0.3 fields") ? 0 : 1;
    }
    if(count_bytes(sigstore_cert_wasm, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in sigstore_cert.wasm") ? 0 : 1; }
    if(!contains_bytes(other_custom_replaced, "not-uwsign")) { return fail("non-uwsign custom section was stripped by --replace") ? 0 : 1; }
    if(count_bytes(other_custom_replaced, "wasm_uwsign") != 1uz) { return fail("expected one wasm_uwsign section in other_custom_replaced.wasm") ? 0 : 1; }

    if(!make_tampered(workdir / "signed2.wasm", workdir / "tampered.wasm")) { return 1; }
    if(!run_in_expect_fail(workdir, uwsign + " --verify --input tampered.wasm --key pub.pem")) { return 1; }

    fs::remove_all(workdir, ec);
    ::std::fputs("[pass] wasm cli integration test\n", stderr);
    return 0;
}
