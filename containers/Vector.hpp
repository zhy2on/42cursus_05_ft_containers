/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 01:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/31 15:45:58 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "reverse_iterator.hpp"
#include <memory>
#include <vector>

namespace ft {
template <class T, class Alloc = std::allocator<T>>
class Vector {
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef std::random_access_iterator_tag iterator;
    typedef std::random_access_iterator_tag const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

public:
    // constructor
    explicit Vector(const allocator_type& alloc = allocator_type()); // default (1)

    explicit Vector(size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type()); // fill (2)

    template <class InputIterator>
    Vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type()); // range (3)

    Vector(const Vector& x); // copy (4)

    // destructor
    ~Vector();

    // operator=
    Vector& operator=(const Vector& x);

    // Iterators
    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    const_iterator cbegin() const noexcept;

    const_iterator cend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;

    const_reverse_iterator crend() const noexcept;

    // Capacity

private:
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
    pointer _data;
};
}

#endif