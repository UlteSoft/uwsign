/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        openssl_signature.h
 * @brief       OpenSSL signing helpers
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
# include <memory>
# include <utility>
// macro
# include <uwsign/utils/macro/push_macros.h>
// platform
# include <openssl/bio.h>
# include <openssl/buffer.h>
# include <openssl/err.h>
# include <openssl/evp.h>
# include <openssl/opensslv.h>
# include <openssl/pem.h>
# include <openssl/rsa.h>
# include <openssl/sha.h>
# include <openssl/x509.h>
# include <openssl/x509_vfy.h>
// import
# include <fast_io.h>
# include <uwsign/utils/container/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::crypto
{
    using byte_vector = ::uwsign::utils::container::vector<::std::byte>;

    struct openssl_status
    {
        bool ok{};
        ::uwsign::utils::container::u8string_view message{};
    };

    namespace details
    {
        template <typename T, auto FreeFunc>
        struct ossl_ptr
        {
            T* ptr{};

            inline constexpr ossl_ptr() noexcept = default;
            inline explicit constexpr ossl_ptr(T* p) noexcept : ptr{p} {}
            ossl_ptr(ossl_ptr const&) = delete;
            ossl_ptr& operator= (ossl_ptr const&) = delete;

            inline constexpr ossl_ptr(ossl_ptr&& other) noexcept : ptr{other.ptr}
            {
                other.ptr = nullptr;
            }

            inline ossl_ptr& operator= (ossl_ptr&& other) noexcept
            {
                if(this == ::std::addressof(other)) [[unlikely]] { return *this; }
                reset();
                ptr = other.ptr;
                other.ptr = nullptr;
                return *this;
            }

            inline ~ossl_ptr()
            {
                reset();
            }

            inline void reset(T* p = nullptr) noexcept
            {
                if(ptr != nullptr) { FreeFunc(ptr); }
                ptr = p;
            }

            [[nodiscard]] inline constexpr T* get() const noexcept
            {
                return ptr;
            }

            [[nodiscard]] inline constexpr explicit operator bool() const noexcept
            {
                return ptr != nullptr;
            }

            [[nodiscard]] inline constexpr T* release() noexcept
            {
                auto const p{ptr};
                ptr = nullptr;
                return p;
            }
        };

        using bio_ptr = ossl_ptr<BIO, BIO_free>;
        using evp_pkey_ptr = ossl_ptr<EVP_PKEY, EVP_PKEY_free>;
        using evp_md_ctx_ptr = ossl_ptr<EVP_MD_CTX, EVP_MD_CTX_free>;
        using x509_ptr = ossl_ptr<X509, X509_free>;
        using x509_store_ptr = ossl_ptr<X509_STORE, X509_STORE_free>;
        using x509_store_ctx_ptr = ossl_ptr<X509_STORE_CTX, X509_STORE_CTX_free>;

        struct x509_stack_ptr
        {
            STACK_OF(X509)* ptr{};

            inline constexpr x509_stack_ptr() noexcept = default;
            inline explicit constexpr x509_stack_ptr(STACK_OF(X509) * p) noexcept : ptr{p} {}
            x509_stack_ptr(x509_stack_ptr const&) = delete;
            x509_stack_ptr& operator= (x509_stack_ptr const&) = delete;

            inline constexpr x509_stack_ptr(x509_stack_ptr&& other) noexcept : ptr{other.ptr}
            {
                other.ptr = nullptr;
            }

            inline x509_stack_ptr& operator= (x509_stack_ptr&& other) noexcept
            {
                if(this == ::std::addressof(other)) [[unlikely]] { return *this; }
                reset();
                ptr = other.ptr;
                other.ptr = nullptr;
                return *this;
            }

            inline ~x509_stack_ptr()
            {
                reset();
            }

            inline void reset(STACK_OF(X509)* p = nullptr) noexcept
            {
                if(ptr != nullptr) { sk_X509_pop_free(ptr, X509_free); }
                ptr = p;
            }

            [[nodiscard]] inline constexpr STACK_OF(X509)* get() const noexcept
            {
                return ptr;
            }

            [[nodiscard]] inline constexpr explicit operator bool() const noexcept
            {
                return ptr != nullptr;
            }
        };

        inline bio_ptr make_mem_bio(::std::byte const* first, ::std::size_t size) noexcept
        {
            if(size == 0uz) [[unlikely]] { return bio_ptr{BIO_new_mem_buf("", 0)}; }
            if(size > static_cast<::std::size_t>((::std::numeric_limits<int>::max)())) [[unlikely]] { return {}; }
            return bio_ptr{BIO_new_mem_buf(first, static_cast<int>(size))};
        }

        inline bool copy_mem_bio(BIO* bio, byte_vector& out) noexcept
        {
            out = {};

            BUF_MEM* mem{};
            BIO_get_mem_ptr(bio, ::std::addressof(mem));
            if(mem == nullptr || mem->length == 0uz) [[unlikely]] { return false; }

            out.resize(mem->length);
            ::std::memcpy(out.data(), mem->data, mem->length);
            return true;
        }

        inline evp_pkey_ptr read_private_key(::std::byte const* first, ::std::size_t size) noexcept
        {
            auto bio{make_mem_bio(first, size)};
            if(!bio) [[unlikely]] { return {}; }
            return evp_pkey_ptr{PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, nullptr)};
        }

        inline evp_pkey_ptr read_public_key(::std::byte const* first, ::std::size_t size) noexcept
        {
            auto bio{make_mem_bio(first, size)};
            if(!bio) [[unlikely]] { return {}; }
            return evp_pkey_ptr{PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr)};
        }

        inline evp_pkey_ptr read_public_key_der(::std::byte const* first, ::std::size_t size) noexcept
        {
            if(size > static_cast<::std::size_t>((::std::numeric_limits<long>::max)())) [[unlikely]] { return {}; }

            auto curr{reinterpret_cast<unsigned char const*>(first)};
            auto const last{curr + size};
            auto key{evp_pkey_ptr{d2i_PUBKEY(nullptr, ::std::addressof(curr), static_cast<long>(size))}};
            if(!key || curr != last) [[unlikely]] { return {}; }
            return key;
        }

        inline x509_ptr read_certificate(::std::byte const* first, ::std::size_t size) noexcept
        {
            auto bio{make_mem_bio(first, size)};
            if(!bio) [[unlikely]] { return {}; }
            return x509_ptr{PEM_read_bio_X509(bio.get(), nullptr, nullptr, nullptr)};
        }

        inline x509_ptr read_certificate_der(::std::byte const* first, ::std::size_t size) noexcept
        {
            if(size > static_cast<::std::size_t>((::std::numeric_limits<long>::max)())) [[unlikely]] { return {}; }

            auto curr{reinterpret_cast<unsigned char const*>(first)};
            auto const last{curr + size};
            auto cert{x509_ptr{d2i_X509(nullptr, ::std::addressof(curr), static_cast<long>(size))}};
            if(!cert || curr != last) [[unlikely]] { return {}; }
            return cert;
        }

        inline x509_stack_ptr read_certificate_chain(::std::byte const* first, ::std::size_t size) noexcept
        {
            auto bio{make_mem_bio(first, size)};
            if(!bio) [[unlikely]] { return {}; }

            auto chain{x509_stack_ptr{sk_X509_new_null()}};
            if(!chain) [[unlikely]] { return {}; }

            for(;;)
            {
                auto cert{x509_ptr{PEM_read_bio_X509(bio.get(), nullptr, nullptr, nullptr)}};
                if(!cert) { break; }
                if(sk_X509_push(chain.get(), cert.get()) == 0) [[unlikely]] { return {}; }
                static_cast<void>(cert.release());
            }

            if(sk_X509_num(chain.get()) == 0) [[unlikely]] { return {}; }
            return chain;
        }

        inline evp_pkey_ptr public_key_from_certificate(::std::byte const* first, ::std::size_t size) noexcept
        {
            auto cert{read_certificate(first, size)};
            if(!cert) [[unlikely]] { return {}; }
            return evp_pkey_ptr{X509_get_pubkey(cert.get())};
        }

        [[nodiscard]] inline bool same_public_key(EVP_PKEY* lhs, EVP_PKEY* rhs) noexcept
        {
            if(lhs == nullptr || rhs == nullptr) [[unlikely]] { return false; }
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
            return EVP_PKEY_eq(lhs, rhs) == 1;
#else
            return EVP_PKEY_cmp(lhs, rhs) == 1;
#endif
        }

        inline bool push_up_ref_certificate(STACK_OF(X509) * stack, X509* cert) noexcept
        {
            if(stack == nullptr || cert == nullptr) [[unlikely]] { return false; }
            if(X509_up_ref(cert) != 1) [[unlikely]] { return false; }
            if(sk_X509_push(stack, cert) == 0) [[unlikely]]
            {
                X509_free(cert);
                return false;
            }
            return true;
        }

        inline bool verify_certificate_chain(X509* leaf, STACK_OF(X509)* chain) noexcept
        {
            if(leaf == nullptr || chain == nullptr || sk_X509_num(chain) == 0) [[unlikely]] { return false; }

            auto store{x509_store_ptr{X509_STORE_new()}};
            if(!store) [[unlikely]] { return false; }

            auto const cert_count{sk_X509_num(chain)};
            auto const trust_anchor{sk_X509_value(chain, cert_count - 1)};
            if(trust_anchor == nullptr) [[unlikely]] { return false; }
            if(X509_STORE_add_cert(store.get(), trust_anchor) != 1) [[unlikely]]
            {
                auto const err{ERR_peek_last_error()};
                if(ERR_GET_REASON(err) != X509_R_CERT_ALREADY_IN_HASH_TABLE) { return false; }
                ERR_clear_error();
            }

            auto untrusted{x509_stack_ptr{sk_X509_new_null()}};
            if(!untrusted) [[unlikely]] { return false; }
            for(int i{}; i + 1 < cert_count; ++i)
            {
                auto cert{sk_X509_value(chain, i)};
                if(cert == nullptr) [[unlikely]] { return false; }
                if(X509_cmp(leaf, cert) == 0) { continue; }
                if(!push_up_ref_certificate(untrusted.get(), cert)) [[unlikely]] { return false; }
            }

            auto ctx{x509_store_ctx_ptr{X509_STORE_CTX_new()}};
            if(!ctx) [[unlikely]] { return false; }

            if(X509_STORE_CTX_init(ctx.get(), store.get(), leaf, untrusted.get()) != 1) [[unlikely]] { return false; }
            return X509_verify_cert(ctx.get()) == 1;
        }

        [[nodiscard]] inline constexpr char8_t const* key_algorithm_name(EVP_PKEY const* key) noexcept
        {
            switch(EVP_PKEY_get_base_id(key))
            {
                case EVP_PKEY_RSA: return u8"rsa-pkcs1-sha256";
                case EVP_PKEY_RSA_PSS: return u8"rsa-pss-sha256";
                case EVP_PKEY_EC: return u8"ecdsa-sha256";
#if defined(EVP_PKEY_ED25519)
                case EVP_PKEY_ED25519: return u8"ed25519";
#endif
#if defined(EVP_PKEY_ED448)
                case EVP_PKEY_ED448: return u8"ed448";
#endif
                default: return nullptr;
            }
        }

        [[nodiscard]] inline openssl_status validate_signature_key(EVP_PKEY const* key) noexcept
        {
            if(key == nullptr) [[unlikely]] { return {false, u8"OpenSSL key is null."}; }

            switch(EVP_PKEY_get_base_id(key))
            {
                case EVP_PKEY_RSA:
                case EVP_PKEY_RSA_PSS:
                    if(EVP_PKEY_bits(key) < 2048) [[unlikely]] { return {false, u8"RSA signing keys must be at least 2048 bits."}; }
                    break;
                case EVP_PKEY_EC: break;
#if defined(EVP_PKEY_ED25519)
                case EVP_PKEY_ED25519: break;
#endif
#if defined(EVP_PKEY_ED448)
                case EVP_PKEY_ED448: break;
#endif
                default: return {false, u8"unsupported OpenSSL signing key type."};
            }

            auto const security_bits{EVP_PKEY_get_security_bits(key)};
            if(security_bits < 112) [[unlikely]] { return {false, u8"signing key strength is below 112 security bits."}; }
            return {true, {}};
        }

        [[nodiscard]] inline constexpr EVP_MD const* md_for_key(EVP_PKEY const* key) noexcept
        {
            switch(EVP_PKEY_get_base_id(key))
            {
#if defined(EVP_PKEY_ED25519)
                case EVP_PKEY_ED25519: return nullptr;
#endif
#if defined(EVP_PKEY_ED448)
                case EVP_PKEY_ED448: return nullptr;
#endif
                default: return EVP_sha256();
            }
        }

        inline openssl_status configure_signature_context(EVP_PKEY_CTX* pkey_ctx, EVP_PKEY const* key) noexcept
        {
            if(pkey_ctx == nullptr || key == nullptr) [[unlikely]] { return {false, u8"OpenSSL signature context is null."}; }

            if(EVP_PKEY_get_base_id(key) == EVP_PKEY_RSA_PSS)
            {
                if(EVP_PKEY_CTX_set_rsa_padding(pkey_ctx, RSA_PKCS1_PSS_PADDING) <= 0) [[unlikely]]
                {
                    return {false, u8"OpenSSL failed to set RSA-PSS padding."};
                }
                if(EVP_PKEY_CTX_set_rsa_mgf1_md(pkey_ctx, EVP_sha256()) <= 0) [[unlikely]]
                {
                    return {false, u8"OpenSSL failed to set RSA-PSS MGF1 digest."};
                }
                if(EVP_PKEY_CTX_set_rsa_pss_saltlen(pkey_ctx, RSA_PSS_SALTLEN_DIGEST) <= 0) [[unlikely]]
                {
                    return {false, u8"OpenSSL failed to set RSA-PSS salt length."};
                }
            }

            return {true, {}};
        }

        inline openssl_status x509_to_der(X509* cert, byte_vector& der) noexcept
        {
            der = {};

            auto const len{i2d_X509(cert, nullptr)};
            if(len <= 0) [[unlikely]] { return {false, u8"OpenSSL failed to encode X.509 certificate DER."}; }

            der.resize(static_cast<::std::size_t>(len));
            auto curr{reinterpret_cast<unsigned char*>(der.data())};
            if(i2d_X509(cert, ::std::addressof(curr)) != len) [[unlikely]]
            {
                der = {};
                return {false, u8"OpenSSL failed to write X.509 certificate DER."};
            }

            return {true, {}};
        }

        inline openssl_status pkey_to_der(EVP_PKEY* key, byte_vector& der) noexcept
        {
            der = {};

            auto const len{i2d_PUBKEY(key, nullptr)};
            if(len <= 0) [[unlikely]] { return {false, u8"OpenSSL failed to encode public key DER."}; }

            der.resize(static_cast<::std::size_t>(len));
            auto curr{reinterpret_cast<unsigned char*>(der.data())};
            if(i2d_PUBKEY(key, ::std::addressof(curr)) != len) [[unlikely]]
            {
                der = {};
                return {false, u8"OpenSSL failed to write public key DER."};
            }

            return {true, {}};
        }
    }  // namespace details

    inline openssl_status sha256(::std::byte const* first, ::std::size_t size, ::std::byte* digest32) noexcept
    {
        if(SHA256(reinterpret_cast<unsigned char const*>(first), size, reinterpret_cast<unsigned char*>(digest32)) == nullptr) [[unlikely]]
        {
            return {false, u8"OpenSSL SHA256 failed."};
        }

        return {true, {}};
    }

    inline openssl_status sign(EVP_PKEY* key, ::std::byte const* first, ::std::size_t size, byte_vector& signature) noexcept
    {
        auto ctx{details::evp_md_ctx_ptr{EVP_MD_CTX_new()}};
        if(!ctx) [[unlikely]] { return {false, u8"OpenSSL failed to allocate EVP_MD_CTX."}; }

        auto const key_status{details::validate_signature_key(key)};
        if(!key_status.ok) [[unlikely]] { return key_status; }

        EVP_PKEY_CTX* pkey_ctx{};
        auto const md{details::md_for_key(key)};
        if(EVP_DigestSignInit(ctx.get(), ::std::addressof(pkey_ctx), md, nullptr, key) <= 0) [[unlikely]]
        {
            return {false, u8"OpenSSL EVP_DigestSignInit failed."};
        }
        auto const config_status{details::configure_signature_context(pkey_ctx, key)};
        if(!config_status.ok) [[unlikely]] { return config_status; }

        ::std::size_t sig_len{};
        if(EVP_DigestSign(ctx.get(), nullptr, ::std::addressof(sig_len), reinterpret_cast<unsigned char const*>(first), size) <= 0) [[unlikely]]
        {
            return {false, u8"OpenSSL EVP_DigestSign size query failed."};
        }

        signature.resize(sig_len);
        if(EVP_DigestSign(ctx.get(),
                          reinterpret_cast<unsigned char*>(signature.data()),
                          ::std::addressof(sig_len),
                          reinterpret_cast<unsigned char const*>(first),
                          size) <= 0) [[unlikely]]
        {
            return {false, u8"OpenSSL EVP_DigestSign failed."};
        }

        signature.resize(sig_len);
        return {true, {}};
    }

    inline openssl_status verify(EVP_PKEY* key,
                                 ::std::byte const* first,
                                 ::std::size_t size,
                                 ::std::byte const* sig_first,
                                 ::std::size_t sig_size,
                                 bool& valid) noexcept
    {
        valid = false;

        auto ctx{details::evp_md_ctx_ptr{EVP_MD_CTX_new()}};
        if(!ctx) [[unlikely]] { return {false, u8"OpenSSL failed to allocate EVP_MD_CTX."}; }

        auto const key_status{details::validate_signature_key(key)};
        if(!key_status.ok) [[unlikely]] { return key_status; }

        EVP_PKEY_CTX* pkey_ctx{};
        auto const md{details::md_for_key(key)};
        if(EVP_DigestVerifyInit(ctx.get(), ::std::addressof(pkey_ctx), md, nullptr, key) <= 0) [[unlikely]]
        {
            return {false, u8"OpenSSL EVP_DigestVerifyInit failed."};
        }
        auto const config_status{details::configure_signature_context(pkey_ctx, key)};
        if(!config_status.ok) [[unlikely]] { return config_status; }

        auto const res{EVP_DigestVerify(ctx.get(),
                                        reinterpret_cast<unsigned char const*>(sig_first),
                                        sig_size,
                                        reinterpret_cast<unsigned char const*>(first),
                                        size)};
        if(res < 0) [[unlikely]] { return {false, u8"OpenSSL EVP_DigestVerify failed."}; }

        valid = res == 1;
        return {true, {}};
    }

    inline openssl_status sign_with_private_key(::std::byte const* private_key_first,
                                                ::std::size_t private_key_size,
                                                ::std::byte const* data_first,
                                                ::std::size_t data_size,
                                                byte_vector& signature,
                                                char8_t const*& algorithm) noexcept
    {
        auto key{details::read_private_key(private_key_first, private_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM private key."}; }

        algorithm = details::key_algorithm_name(key.get());
        if(algorithm == nullptr) [[unlikely]] { return {false, u8"unsupported OpenSSL signing key type."}; }
        return sign(key.get(), data_first, data_size, signature);
    }

    inline openssl_status sign_with_private_key_and_certificate(::std::byte const* private_key_first,
                                                                ::std::size_t private_key_size,
                                                                ::std::byte const* certificate_first,
                                                                ::std::size_t certificate_size,
                                                                ::std::byte const* data_first,
                                                                ::std::size_t data_size,
                                                                byte_vector& signature,
                                                                char8_t const*& algorithm) noexcept
    {
        auto key{details::read_private_key(private_key_first, private_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM private key."}; }

        auto cert_key{details::public_key_from_certificate(certificate_first, certificate_size)};
        if(!cert_key) [[unlikely]] { return {false, u8"failed to read PEM certificate public key."}; }
        if(!details::same_public_key(key.get(), cert_key.get())) [[unlikely]]
        {
            return {false, u8"private key does not match the signing certificate."};
        }

        algorithm = details::key_algorithm_name(key.get());
        if(algorithm == nullptr) [[unlikely]] { return {false, u8"unsupported OpenSSL signing key type."}; }
        return sign(key.get(), data_first, data_size, signature);
    }

    inline openssl_status export_public_key_from_private_key_pem(::std::byte const* private_key_first,
                                                                 ::std::size_t private_key_size,
                                                                 byte_vector& public_key_pem) noexcept
    {
        public_key_pem = {};

        auto key{details::read_private_key(private_key_first, private_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM private key."}; }

        auto bio{details::bio_ptr{BIO_new(BIO_s_mem())}};
        if(!bio) [[unlikely]] { return {false, u8"OpenSSL failed to allocate BIO."}; }

        if(PEM_write_bio_PUBKEY(bio.get(), key.get()) != 1) [[unlikely]]
        {
            return {false, u8"OpenSSL failed to export PEM public key."};
        }

        if(!details::copy_mem_bio(bio.get(), public_key_pem)) [[unlikely]] { return {false, u8"OpenSSL exported an empty public key."}; }
        return {true, {}};
    }

    inline openssl_status export_public_key_der_from_private_key_pem(::std::byte const* private_key_first,
                                                                     ::std::size_t private_key_size,
                                                                     byte_vector& public_key_der) noexcept
    {
        auto key{details::read_private_key(private_key_first, private_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM private key."}; }

        return details::pkey_to_der(key.get(), public_key_der);
    }

    inline openssl_status public_key_pem_to_der(::std::byte const* public_key_first, ::std::size_t public_key_size, byte_vector& public_key_der) noexcept
    {
        auto key{details::read_public_key(public_key_first, public_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM public key."}; }

        return details::pkey_to_der(key.get(), public_key_der);
    }

    inline openssl_status public_key_der_to_pem(::std::byte const* public_key_first, ::std::size_t public_key_size, byte_vector& public_key_pem) noexcept
    {
        public_key_pem = {};

        auto key{details::read_public_key_der(public_key_first, public_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read DER public key."}; }

        auto bio{details::bio_ptr{BIO_new(BIO_s_mem())}};
        if(!bio) [[unlikely]] { return {false, u8"OpenSSL failed to allocate BIO."}; }

        if(PEM_write_bio_PUBKEY(bio.get(), key.get()) != 1) [[unlikely]]
        {
            return {false, u8"OpenSSL failed to export PEM public key."};
        }

        if(!details::copy_mem_bio(bio.get(), public_key_pem)) [[unlikely]] { return {false, u8"OpenSSL exported an empty public key."}; }
        return {true, {}};
    }

    inline openssl_status certificate_pem_to_der(::std::byte const* certificate_first,
                                                 ::std::size_t certificate_size,
                                                 byte_vector& certificate_der) noexcept
    {
        auto cert{details::read_certificate(certificate_first, certificate_size)};
        if(!cert) [[unlikely]] { return {false, u8"failed to read PEM certificate."}; }

        return details::x509_to_der(cert.get(), certificate_der);
    }

    inline openssl_status certificate_der_to_pem(::std::byte const* certificate_first,
                                                 ::std::size_t certificate_size,
                                                 byte_vector& certificate_pem) noexcept
    {
        certificate_pem = {};

        auto cert{details::read_certificate_der(certificate_first, certificate_size)};
        if(!cert) [[unlikely]] { return {false, u8"failed to read DER certificate."}; }

        auto bio{details::bio_ptr{BIO_new(BIO_s_mem())}};
        if(!bio) [[unlikely]] { return {false, u8"OpenSSL failed to allocate BIO."}; }

        if(PEM_write_bio_X509(bio.get(), cert.get()) != 1) [[unlikely]]
        {
            return {false, u8"OpenSSL failed to export PEM certificate."};
        }

        if(!details::copy_mem_bio(bio.get(), certificate_pem)) [[unlikely]] { return {false, u8"OpenSSL exported an empty certificate."}; }
        return {true, {}};
    }

    inline openssl_status certificates_pem_to_der_list(::std::byte const* certificate_chain_first,
                                                       ::std::size_t certificate_chain_size,
                                                       ::uwsign::utils::container::vector<byte_vector>& certificates_der) noexcept
    {
        certificates_der = {};

        auto chain{details::read_certificate_chain(certificate_chain_first, certificate_chain_size)};
        if(!chain) [[unlikely]] { return {false, u8"failed to read PEM certificate chain."}; }

        auto const cert_count{sk_X509_num(chain.get())};
        certificates_der.reserve(static_cast<::std::size_t>(cert_count));
        for(int i{}; i != cert_count; ++i)
        {
            auto cert{sk_X509_value(chain.get(), i)};
            if(cert == nullptr) [[unlikely]]
            {
                certificates_der = {};
                return {false, u8"certificate chain contains a null certificate."};
            }

            byte_vector der{};
            auto status{details::x509_to_der(cert, der)};
            if(!status.ok) [[unlikely]]
            {
                certificates_der = {};
                return status;
            }

            certificates_der.emplace_back(::std::move(der));
        }

        return {true, {}};
    }

    inline openssl_status verify_with_public_key(EVP_PKEY* key,
                                                 ::std::byte const* data_first,
                                                 ::std::size_t data_size,
                                                 ::std::byte const* sig_first,
                                                 ::std::size_t sig_size,
                                                 bool& valid) noexcept
    {
        return verify(key, data_first, data_size, sig_first, sig_size, valid);
    }

    inline openssl_status verify_with_public_key_pem(::std::byte const* public_key_first,
                                                     ::std::size_t public_key_size,
                                                     ::std::byte const* data_first,
                                                     ::std::size_t data_size,
                                                     ::std::byte const* sig_first,
                                                     ::std::size_t sig_size,
                                                     bool& valid) noexcept
    {
        auto key{details::read_public_key(public_key_first, public_key_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM public key."}; }

        return verify_with_public_key(key.get(), data_first, data_size, sig_first, sig_size, valid);
    }

    inline openssl_status verify_with_certificate_pem(::std::byte const* certificate_first,
                                                      ::std::size_t certificate_size,
                                                      ::std::byte const* data_first,
                                                      ::std::size_t data_size,
                                                      ::std::byte const* sig_first,
                                                      ::std::size_t sig_size,
                                                      bool& valid) noexcept
    {
        auto key{details::public_key_from_certificate(certificate_first, certificate_size)};
        if(!key) [[unlikely]] { return {false, u8"failed to read PEM certificate public key."}; }

        return verify_with_public_key(key.get(), data_first, data_size, sig_first, sig_size, valid);
    }

    inline openssl_status verify_certificate_chain_pem(::std::byte const* certificate_first,
                                                       ::std::size_t certificate_size,
                                                       ::std::byte const* certificate_chain_first,
                                                       ::std::size_t certificate_chain_size,
                                                       bool& valid) noexcept
    {
        valid = false;

        auto leaf{details::read_certificate(certificate_first, certificate_size)};
        if(!leaf) [[unlikely]] { return {false, u8"failed to read PEM certificate."}; }

        auto chain{details::read_certificate_chain(certificate_chain_first, certificate_chain_size)};
        if(!chain) [[unlikely]] { return {false, u8"failed to read PEM certificate chain."}; }

        valid = details::verify_certificate_chain(leaf.get(), chain.get());
        return {true, {}};
    }

    inline openssl_status verify_with_certificate_chain_pem(::std::byte const* certificate_first,
                                                            ::std::size_t certificate_size,
                                                            ::std::byte const* certificate_chain_first,
                                                            ::std::size_t certificate_chain_size,
                                                            ::std::byte const* data_first,
                                                            ::std::size_t data_size,
                                                            ::std::byte const* sig_first,
                                                            ::std::size_t sig_size,
                                                            bool& valid) noexcept
    {
        bool chain_valid{};
        auto status{verify_certificate_chain_pem(certificate_first, certificate_size, certificate_chain_first, certificate_chain_size, chain_valid)};
        if(!status.ok) [[unlikely]]
        {
            valid = false;
            return status;
        }

        if(!chain_valid) [[unlikely]]
        {
            valid = false;
            return {true, {}};
        }

        return verify_with_certificate_pem(certificate_first, certificate_size, data_first, data_size, sig_first, sig_size, valid);
    }
}  // namespace uwsign::uwsign::crypto

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
