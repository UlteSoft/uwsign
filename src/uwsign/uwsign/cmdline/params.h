/*************************************************************
 * UlteSoft WebAssembly Signer                               *
 * Copyright (c) 2026-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2.0 License (see LICENSE file).    *
 *************************************************************/

/**
 * @file        params.h
 * @brief       uwsign command line parameter table
 * @author      MacroModel
 * @version     v1.0.0.0
 * @copyright   APL-2.0 License
 */

#pragma once

#ifndef UWSIGN_MODULE
// std
# include <memory>
// macro
# include <uwsign/utils/macro/push_macros.h>
// import
# include <uwsign/utils/cmdline/impl.h>
# include <uwsign/uwsign/cmdline/params/impl.h>
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::uwsign::cmdline
{
    namespace details
    {
        inline constexpr ::uwsign::utils::cmdline::parameter const* parameter_unsort[]{
            // global
            ::std::addressof(::uwsign::uwsign::cmdline::params::version),
            ::std::addressof(::uwsign::uwsign::cmdline::params::help),

            // sign
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign),
            ::std::addressof(::uwsign::uwsign::cmdline::params::verify),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_input),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_output),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_wasm_output),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_key),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_certificate),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_certificate_chain),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_bundle),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_bundle_format),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_signature),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_output_signature),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_output_certificate),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_output_certificate_chain),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_replace),
            ::std::addressof(::uwsign::uwsign::cmdline::params::sign_base64),

            // log
            ::std::addressof(::uwsign::uwsign::cmdline::params::log_verbose),
        };
    }  // namespace details

    inline constexpr auto parameters{::uwsign::utils::cmdline::parameter_sort(details::parameter_unsort)};

    inline constexpr ::std::size_t parameter_lookup_table_size{::uwsign::utils::cmdline::calculate_alias_parameters_size(parameters)};
    inline constexpr auto parameter_lookup_table{::uwsign::utils::cmdline::expand_alias_parameters_and_check<parameter_lookup_table_size>(parameters)};

    inline constexpr ::std::size_t parameter_max_principal_name_size{::uwsign::utils::cmdline::calculate_max_principal_name_size(parameters)};
    inline constexpr ::std::size_t parameter_max_name_size{::uwsign::utils::cmdline::calculate_max_para_size(parameter_lookup_table)};

    inline constexpr auto hash_table_size{::uwsign::utils::cmdline::calculate_hash_table_size(parameter_lookup_table)};
    inline constexpr auto hash_table{
        ::uwsign::utils::cmdline::generate_hash_table<hash_table_size.hash_table_size, hash_table_size.extra_size, hash_table_size.real_max_conflict_size>(
            parameter_lookup_table)};

    inline constexpr ::std::size_t hash_table_byte_sz{sizeof(hash_table)};
}  // namespace uwsign::uwsign::cmdline

#ifndef UWSIGN_MODULE
// macro
# include <uwsign/utils/macro/pop_macros.h>
#endif
