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
# include <string_view>
# include <set>  /// @todo replace with btreemap
# include <map>  /// @todo replace with btreemap
# include <deque>
# include <unordered_map>
# include <unordered_set>
// import
# include <fast_io.h>
# include <fast_io_dsal/tuple.h>
# include <fast_io_dsal/array.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/string.h>
# include <fast_io_dsal/vector.h>
# include <fast_io_dsal/list.h>
# include <fast_io_dsal/stack.h>
# include <fast_io_dsal/queue.h>
# include <uwsign/utils/hash/impl.h>
# include "allocator.h"
#endif

#ifndef UWSIGN_MODULE_EXPORT
# define UWSIGN_MODULE_EXPORT
#endif

UWSIGN_MODULE_EXPORT namespace uwsign::utils::container
{
    /// @brief tuple
    using ::fast_io::containers::forward_as_tuple;
    using ::fast_io::containers::get;
    using ::fast_io::containers::is_tuple;
    using ::fast_io::containers::tuple;

    /// @brief array
    template <typename T, ::std::size_t N>
    using array = ::fast_io::containers::array<T, N>;

    /// @brief string_view
    template <::std::integral chartype>
    using basic_string_view = ::fast_io::containers::basic_string_view<chartype>;

    using string_view = ::uwsign::utils::container::basic_string_view<char>;
    using wstring_view = ::uwsign::utils::container::basic_string_view<wchar_t>;
    using u8string_view = ::uwsign::utils::container::basic_string_view<char8_t>;
    using u16string_view = ::uwsign::utils::container::basic_string_view<char16_t>;
    using u32string_view = ::uwsign::utils::container::basic_string_view<char32_t>;

    /// @brief cstring_view
    template <::std::integral chartype>
    using basic_cstring_view = ::fast_io::containers::basic_cstring_view<chartype>;

    using cstring_view = ::uwsign::utils::container::basic_cstring_view<char>;
    using wcstring_view = ::uwsign::utils::container::basic_cstring_view<wchar_t>;
    using u8cstring_view = ::uwsign::utils::container::basic_cstring_view<char8_t>;
    using u16cstring_view = ::uwsign::utils::container::basic_cstring_view<char16_t>;
    using u32cstring_view = ::uwsign::utils::container::basic_cstring_view<char32_t>;

    /// @brief string
    template <::std::integral chartype, typename allocator = ::fast_io::native_global_allocator>
    using basic_string = ::fast_io::containers::basic_string<chartype, allocator>;

    using string = ::uwsign::utils::container::basic_string<char>;
    using wstring = ::uwsign::utils::container::basic_string<wchar_t>;
    using u8string = ::uwsign::utils::container::basic_string<char8_t>;
    using u16string = ::uwsign::utils::container::basic_string<char16_t>;
    using u32string = ::uwsign::utils::container::basic_string<char32_t>;

    template <::std::integral chartype, typename allocator = ::fast_io::native_global_allocator>
    using basic_ostring_ref_uwsign = ::fast_io::io_strlike_reference_wrapper<chartype, ::uwsign::utils::container::basic_string<chartype, allocator>>;

    using ostring_ref_uwsign = ::uwsign::utils::container::basic_ostring_ref_uwsign<char>;
    using wostring_ref_uwsign = ::uwsign::utils::container::basic_ostring_ref_uwsign<wchar_t>;
    using u8ostring_ref_uwsign = ::uwsign::utils::container::basic_ostring_ref_uwsign<char8_t>;
    using u16ostring_ref_uwsign = ::uwsign::utils::container::basic_ostring_ref_uwsign<char16_t>;
    using u32ostring_ref_uwsign = ::uwsign::utils::container::basic_ostring_ref_uwsign<char32_t>;

    template <::std::integral chartype, typename allocator = ::fast_io::native_global_allocator>
    using basic_ostring_ref_uwvm = ::uwsign::utils::container::basic_ostring_ref_uwsign<chartype, allocator>;

    using ostring_ref_uwvm = ::uwsign::utils::container::ostring_ref_uwsign;
    using wostring_ref_uwvm = ::uwsign::utils::container::wostring_ref_uwsign;
    using u8ostring_ref_uwvm = ::uwsign::utils::container::u8ostring_ref_uwsign;
    using u16ostring_ref_uwvm = ::uwsign::utils::container::u16ostring_ref_uwsign;
    using u32ostring_ref_uwvm = ::uwsign::utils::container::u32ostring_ref_uwsign;

    namespace tlc
    {
        template <::std::integral chartype, typename allocator = ::fast_io::native_thread_local_allocator>
        using basic_string = ::uwsign::utils::container::basic_string<chartype, allocator>;

        using string = ::uwsign::utils::container::tlc::basic_string<char>;
        using wstring = ::uwsign::utils::container::tlc::basic_string<wchar_t>;
        using u8string = ::uwsign::utils::container::tlc::basic_string<char8_t>;
        using u16string = ::uwsign::utils::container::tlc::basic_string<char16_t>;
        using u32string = ::uwsign::utils::container::tlc::basic_string<char32_t>;

        template <::std::integral chartype, typename allocator = ::fast_io::native_thread_local_allocator>
        using basic_ostring_ref_uwsign_tlc = ::fast_io::io_strlike_reference_wrapper<chartype, ::uwsign::utils::container::tlc::basic_string<chartype, allocator>>;

        using ostring_ref_uwsign_tlc = basic_ostring_ref_uwsign_tlc<char>;
        using wostring_ref_uwsign_tlc = basic_ostring_ref_uwsign_tlc<wchar_t>;
        using u8ostring_ref_uwsign_tlc = basic_ostring_ref_uwsign_tlc<char8_t>;
        using u16ostring_ref_uwsign_tlc = basic_ostring_ref_uwsign_tlc<char16_t>;
        using u32ostring_ref_uwsign_tlc = basic_ostring_ref_uwsign_tlc<char32_t>;

        template <::std::integral chartype, typename allocator = ::fast_io::native_thread_local_allocator>
        using basic_ostring_ref_uwvm_tlc = ::uwsign::utils::container::tlc::basic_ostring_ref_uwsign_tlc<chartype, allocator>;

        using ostring_ref_uwvm_tlc = ostring_ref_uwsign_tlc;
        using wostring_ref_uwvm_tlc = wostring_ref_uwsign_tlc;
        using u8ostring_ref_uwvm_tlc = u8ostring_ref_uwsign_tlc;
        using u16ostring_ref_uwvm_tlc = u16ostring_ref_uwsign_tlc;
        using u32ostring_ref_uwvm_tlc = u32ostring_ref_uwsign_tlc;
    }  // namespace tlc

    /// @brief vector
    template <::std::movable T, typename Alloc = ::fast_io::native_global_allocator>
    using vector = ::fast_io::containers::vector<T, Alloc>;

    namespace tlc
    {
        template <::std::movable T, typename Alloc = ::fast_io::native_thread_local_allocator>
        using vector = ::uwsign::utils::container::vector<T, Alloc>;
    }

    /// @brief deque
    template <typename T, typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<T>>
    using deque = ::std::deque<T, Alloc>;

    namespace tlc
    {
        template <typename T, typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<T>>
        using deque = ::uwsign::utils::container::deque<T, Alloc>;
    }

    /// @brief list
    template <typename T, typename Alloc = ::fast_io::native_global_allocator>
    using list = ::fast_io::containers::list<T, Alloc>;

    namespace tlc
    {
        template <typename T, typename Alloc = ::fast_io::native_thread_local_allocator>
        using list = ::uwsign::utils::container::list<T, Alloc>;
    }

    /// @brief stack
    template <typename T, typename Container = ::uwsign::utils::container::vector<T>>
    using stack = ::fast_io::containers::stack<Container>;

    namespace tlc
    {
        template <typename T, typename Container = ::uwsign::utils::container::tlc::vector<T>>
        using stack = ::uwsign::utils::container::stack<Container>;
    }

    /// @brief queue
    template <typename T, typename Container = ::uwsign::utils::container::deque<T>>
    using queue = ::fast_io::containers::queue<Container>;

    namespace tlc
    {
        template <typename T, typename Container = ::uwsign::utils::container::tlc::deque<T>>
        using queue = ::uwsign::utils::container::queue<Container>;
    }

    /// @brief owned pointer
    template <typename T>
    struct fast_io_owned_ptr_deleter
    {
        inline constexpr void operator() (T* ptr) const noexcept
        {
            if(ptr == nullptr) [[unlikely]] { return; }
            ::std::destroy_at(ptr);
            ::fast_io::native_typed_global_allocator<T>::deallocate(ptr);
        }
    };

    template <typename T>
    struct delete_owned_ptr_deleter
    {
        inline constexpr void operator() (T* ptr) const noexcept
        { delete ptr; }
    };

    template <typename T, typename Deleter = ::uwsign::utils::container::fast_io_owned_ptr_deleter<T>>
    struct basic_owned_ptr
    {
        using element_type = T;
        using deleter_type = Deleter;

        T* ptr{};

        inline constexpr basic_owned_ptr() noexcept = default;
        inline constexpr basic_owned_ptr(::std::nullptr_t) noexcept
        {
        }

        inline constexpr explicit basic_owned_ptr(T* p) noexcept
            : ptr{p}
        {
        }

        basic_owned_ptr(basic_owned_ptr const&) = delete;
        basic_owned_ptr& operator= (basic_owned_ptr const&) = delete;

        inline constexpr basic_owned_ptr(basic_owned_ptr&& other) noexcept
            : ptr{other.release()}
        {
        }

        inline constexpr basic_owned_ptr& operator= (basic_owned_ptr&& other) noexcept
        {
            if(this == ::std::addressof(other)) [[unlikely]] { return *this; }
            reset(other.release());
            return *this;
        }

        inline constexpr ~basic_owned_ptr() noexcept
        { reset(); }

        [[nodiscard]] inline constexpr T* get() const noexcept
        { return ptr; }

        [[nodiscard]] inline constexpr explicit operator bool() const noexcept
        { return ptr != nullptr; }

        [[nodiscard]] inline constexpr bool operator== (::std::nullptr_t) const noexcept
        { return ptr == nullptr; }

        [[nodiscard]] inline constexpr bool operator!= (::std::nullptr_t) const noexcept
        { return ptr != nullptr; }

        [[nodiscard]] inline constexpr T& operator*() const noexcept
        { return *ptr; }

        [[nodiscard]] inline constexpr T* operator->() const noexcept
        { return ptr; }

        [[nodiscard]] inline constexpr T* release() noexcept
        {
            auto const old_ptr{ptr};
            ptr = nullptr;
            return old_ptr;
        }

        inline constexpr void reset(T* p = nullptr) noexcept
        {
            if(ptr == p) [[unlikely]] { return; }

            auto const old_ptr{ptr};
            ptr = p;
            if(old_ptr != nullptr) [[unlikely]] { Deleter{}(old_ptr); }
        }

        inline constexpr void swap(basic_owned_ptr& other) noexcept
        { ::std::swap(ptr, other.ptr); }
    };

    template <typename T>
    using owned_ptr = ::uwsign::utils::container::basic_owned_ptr<T>;

    template <typename T>
    using delete_owned_ptr = ::uwsign::utils::container::basic_owned_ptr<T, ::uwsign::utils::container::delete_owned_ptr_deleter<T>>;

    template <typename T, typename... Args>
    [[nodiscard]] inline auto make_owned(Args&&... args) -> ::uwsign::utils::container::owned_ptr<T>
    {
        auto ptr{::fast_io::native_typed_global_allocator<T>::allocate(1)};
        try
        {
            ::std::construct_at(ptr, ::std::forward<Args>(args)...);
        }
        catch(...)
        {
            ::fast_io::native_typed_global_allocator<T>::deallocate(ptr);
            throw;
        }
        return ::uwsign::utils::container::owned_ptr<T>{ptr};
    }

    /// @brief ordered
    template <typename Key, typename Compare = ::std::less<Key>, typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<Key>>
    using set = ::std::set<Key, Compare, Alloc>;  /// @todo replace with btree set

    template <typename Key,
              typename Val,
              typename Compare = ::std::less<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<::std::pair<Key const, Val>>>
    using map = ::std::map<Key, Val, Compare, Alloc>;  /// @todo replace with btree map

    namespace tlc
    {
        template <typename Key, typename Compare = ::std::less<Key>, typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<Key>>
        using set = ::uwsign::utils::container::set<Key, Compare, Alloc>;

        template <typename Key,
                  typename Val,
                  typename Compare = ::std::less<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<::std::pair<Key const, Val>>>
        using map = ::uwsign::utils::container::map<Key, Val, Compare, Alloc>;
    }  // namespace tlc

    /// @brief unordered
    template <typename Key,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<Key>>
    using unordered_flat_set = ::std::unordered_set<Key, Hash, Pred, Alloc>;

    template <typename Key,
              typename Val,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<::std::pair<Key const, Val>>>
    using unordered_flat_map = ::std::unordered_map<Key, Val, Hash, Pred, Alloc>;

    template <typename Key,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<Key>>
    using unordered_node_set = ::std::unordered_set<Key, Hash, Pred, Alloc>;

    template <typename Key,
              typename Val,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<::std::pair<Key const, Val>>>
    using unordered_node_map = ::std::unordered_map<Key, Val, Hash, Pred, Alloc>;

    template <typename Key,
              typename Val,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<::std::pair<Key const, Val>>>
    using concurrent_node_map = ::std::unordered_map<Key, Val, Hash, Pred, Alloc>;

    template <typename Key,
              typename Hash = ::std::hash<Key>,
              typename Pred = ::std::equal_to<Key>,
              typename Alloc = ::uwsign::utils::container::fast_io_global_std_allocator<Key>>
    using concurrent_node_set = ::std::unordered_set<Key, Hash, Pred, Alloc>;

    namespace tlc
    {
        template <typename Key,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<Key>>
        using unordered_flat_set = ::uwsign::utils::container::unordered_flat_set<Key, Hash, Pred, Alloc>;

        template <typename Key,
                  typename Val,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<::std::pair<Key const, Val>>>
        using unordered_flat_map = ::uwsign::utils::container::unordered_flat_map<Key, Val, Hash, Pred, Alloc>;

        template <typename Key,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<Key>>
        using unordered_node_set = ::uwsign::utils::container::unordered_node_set<Key, Hash, Pred, Alloc>;

        template <typename Key,
                  typename Val,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<::std::pair<Key const, Val>>>
        using unordered_node_map = ::uwsign::utils::container::unordered_node_map<Key, Val, Hash, Pred, Alloc>;

        template <typename Key,
                  typename Val,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<::std::pair<Key const, Val>>>
        using concurrent_node_map = ::uwsign::utils::container::concurrent_node_map<Key, Val, Hash, Pred, Alloc>;

        template <typename Key,
                  typename Hash = ::std::hash<Key>,
                  typename Pred = ::std::equal_to<Key>,
                  typename Alloc = ::uwsign::utils::container::fast_io_thread_local_std_allocator<Key>>
        using concurrent_node_set = ::uwsign::utils::container::concurrent_node_set<Key, Hash, Pred, Alloc>;
    }  // namespace tlc

    /// @brief predicates
    /// Perform transparent comparisons using std::basic_string_view, supporting heterogeneous lookups while avoiding allocations.
    namespace pred
    {
        template <::std::integral chartype>
        struct basic_string_view_hash
        {
            using is_transparent = void;  // enable heterogeneous lookup

            inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_string_view<chartype> sv) const noexcept
            { return ::std::hash<::uwsign::utils::container::basic_string_view<chartype>>{}(sv); }

            inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_cstring_view<chartype> sv) const noexcept
            {
                return ::std::hash<::uwsign::utils::container::basic_string_view<chartype>>{}(
                    ::uwsign::utils::container::basic_string_view<chartype>{sv.data(), sv.size()});
            }

            inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_string<chartype> const& s) const noexcept
            {
                return ::std::hash<::uwsign::utils::container::basic_string_view<chartype>>{}(
                    ::uwsign::utils::container::basic_string_view<chartype>{s.data(), s.size()});
            }

            inline constexpr ::std::size_t operator() (chartype const* s) const noexcept
            {
                return ::std::hash<::uwsign::utils::container::basic_string_view<chartype>>{}(
                    ::uwsign::utils::container::basic_string_view<chartype>{::fast_io::mnp::os_c_str(s)});
            }
        };

        template <::std::integral chartype>
        struct basic_string_view_equal
        {
            using is_transparent = void;  // enable heterogeneous lookup

            template <typename L, typename R>
                requires requires(L const& lhs, R const& rhs) {
                    {
                        ::uwsign::utils::container::basic_string_view<chartype> { lhs.data(), lhs.size() }
                    };
                    {
                        ::uwsign::utils::container::basic_string_view<chartype> { rhs.data(), rhs.size() }
                    };
                }
            inline constexpr bool operator() (L const& lhs, R const& rhs) const noexcept
            {
                using strvw = ::uwsign::utils::container::basic_string_view<chartype>;
                return strvw{lhs.data(), lhs.size()} == strvw{rhs.data(), rhs.size()};
            }
        };

        template <::std::integral chartype>
        struct basic_string_view_less
        {
            using is_transparent = void;  // enable heterogeneous lookup

            template <typename L, typename R>
                requires requires(L const& lhs, R const& rhs) {
                    {
                        ::uwsign::utils::container::basic_string_view<chartype> { lhs.data(), lhs.size() }
                    };
                    {
                        ::uwsign::utils::container::basic_string_view<chartype> { rhs.data(), rhs.size() }
                    };
                }
            inline constexpr bool operator() (L const& lhs, R const& rhs) const noexcept
            {
                using strvw = ::uwsign::utils::container::basic_string_view<chartype>;
                return strvw{lhs.data(), lhs.size()} < strvw{rhs.data(), rhs.size()};
            }
        };

        using string_view_equal = basic_string_view_equal<char>;
        using wstring_view_equal = basic_string_view_equal<wchar_t>;
        using u8string_view_equal = basic_string_view_equal<char8_t>;
        using u16string_view_equal = basic_string_view_equal<char16_t>;
        using u32string_view_equal = basic_string_view_equal<char32_t>;

        using string_view_less = basic_string_view_less<char>;
        using wstring_view_less = basic_string_view_less<wchar_t>;
        using u8string_view_less = basic_string_view_less<char8_t>;
        using u16string_view_less = basic_string_view_less<char16_t>;
        using u32string_view_less = basic_string_view_less<char32_t>;

        using string_view_hash = basic_string_view_hash<char>;
        using wstring_view_hash = basic_string_view_hash<wchar_t>;
        using u8string_view_hash = basic_string_view_hash<char8_t>;
        using u16string_view_hash = basic_string_view_hash<char16_t>;
        using u32string_view_hash = basic_string_view_hash<char32_t>;

    }  // namespace pred
}

UWSIGN_MODULE_EXPORT namespace std
{
    template <::std::integral char_type>
    struct hash<::uwsign::utils::container::basic_string_view<char_type>>
    {
        inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_string_view<char_type> obj) const noexcept
        {
#if CHAR_BIT > 8
            // use std hash
            using strvw = ::std::basic_string_view<char_type>;
            return ::std::hash<strvw>{}(strvw{obj});
#else
            ::std::size_t sz;
            if constexpr(requires { obj.size_bytes(); }) { sz = obj.size_bytes(); }
            else
            {
                sz = obj.size() * sizeof(char_type);
            }
            return static_cast<::std::size_t>(::uwsign::utils::hash::xxh3_64bits(reinterpret_cast<::std::byte const*>(obj.data()), sz));
#endif
        }
    };

    template <::std::integral char_type>
    struct hash<::uwsign::utils::container::basic_cstring_view<char_type>>
    {
        inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_cstring_view<char_type> obj) const noexcept
        {
#if CHAR_BIT > 8
            // use std hash
            using strvw = ::std::basic_string_view<char_type>;
            return ::std::hash<strvw>{}(strvw{obj});
#else
            ::std::size_t sz;
            if constexpr(requires { obj.size_bytes(); }) { sz = obj.size_bytes(); }
            else
            {
                sz = obj.size() * sizeof(char_type);
            }
            return static_cast<::std::size_t>(::uwsign::utils::hash::xxh3_64bits(reinterpret_cast<::std::byte const*>(obj.data()), sz));
#endif
        }
    };

    template <::std::integral char_type, typename Alloc>
    struct hash<::uwsign::utils::container::basic_string<char_type, Alloc>>
    {
        inline constexpr ::std::size_t operator() (::uwsign::utils::container::basic_string<char_type, Alloc> const& obj) const noexcept
        {
#if CHAR_BIT > 8
            // use std hash
            using strvw = ::std::basic_string_view<char_type>;
            return ::std::hash<strvw>{}(strvw{obj});
#else
            ::std::size_t sz;
            if constexpr(requires { obj.size_bytes(); }) { sz = obj.size_bytes(); }
            else
            {
                sz = obj.size() * sizeof(char_type);
            }
            return static_cast<::std::size_t>(::uwsign::utils::hash::xxh3_64bits(reinterpret_cast<::std::byte const*>(obj.data()), sz));
#endif
        }
    };
}
