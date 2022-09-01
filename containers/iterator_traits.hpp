/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:34:38 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/02 00:58:22 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>

namespace ft {
template <class Iterator>
class iterator_traits {
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*> {
    typedef typename ptrdiff_t difference_type;
    typedef typename T value_type;
    typedef typename T* pointer;
    typedef typename T& reference;
    typedef typename std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
    typedef typename ptrdiff_t difference_type;
    typedef typename T value_type;
    typedef const typename T* pointer;
    typedef const typename T& reference;
    typedef typename std::random_access_iterator_tag iterator_category;
};
} // namespace ft

#endif