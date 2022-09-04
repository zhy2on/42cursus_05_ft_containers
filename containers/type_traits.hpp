/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:49:24 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/04 19:00:43 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef> // std::ptrdiff_t
#include "vector_iterator.hpp"

namespace ft
{
    // iterator_tag
    struct random_access_iterator_tag
    {
    };

    // iterator_traits
    template <class Iterator>
    class iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>
    {
        typedef typename std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>
    {
        typedef typename std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };

    // enable_if
    template <bool Cond, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // is_integral
    template <class T>
    struct is_integral
    {
        static const bool value = false;
    };

    template <>
    struct is_integral<bool>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char16_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char32_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<wchar_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<signed char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<short int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<long int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<long long int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned short int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned long int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned long long int>
    {
        static const bool value = true;
    };

    // is_iterator(custom)
    template <class T>
    struct is_iterator
    {
        static const bool value = false;
    };

    template <class T>
    struct is_iterator< ft::vector_iterator<T> >
    {
        static const bool value = true;
    };
} // namespace ft

#endif