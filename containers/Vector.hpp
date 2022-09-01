/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 01:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/02 02:53:02 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include <cstddef> // std::ptrdiff_t
#include <memory> // std::allocator

namespace ft {
template <class T, class Alloc = std::allocator<T>>
class vector {
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef ft::vector_iterator<value_type> iterator;
    typedef ft::vector_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

    // constructor
    explicit vector(const allocator_type& alloc = allocator_type())
        : _allocator(alloc)
        , _capacity(0)
        , _size(0)
        , _data(NULL)
    {
    } // default

    explicit vector(size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc)
        , _capacity(n)
        , _size(n)
    {
        _data = _allocator.allocate(n);
        for (int i = 0; i < n; i++)
            _data[i] = val;
    } // fill

    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc)
        , _capacity(last - first)
        , _size(_capacity)
    {
        _data = _allocator.allocate(_capacity);
        for (InputIterator it = first; it != last; it++)
            *(_data++) = *it;
    } // range

    vector(const vector& x)
    {
        
    } // copy

    // // destructor
    // ~vector();

    // // operator=
    // vector& operator=(const vector& x);

    // Iterators
    iterator begin()
    {
        return (iterator(_data));
    }

    const_iterator begin() const
    {
        return (const_iterator(_data));
    }

    iterator end()
    {
        return (iterator(_data + _size));
    }

    const_iterator end() const
    {
        return (const_iterator(_data + _size));
    }

    reverse_iterator rbegin()
    {
        return (reverse_iterator(end()));
    }

    const_reverse_iterator rbegin() const
    {
        return (const_reverse_iterator(end()));
    }

    reverse_iterator rend()
    {
        return (reverse_iterator(begin()));
    }

    const_reverse_iterator rend() const
    {
        return (const_reverse_iterator(begin()));
    }

    // Capacity
    size_type size() const
    {
        return (_size);
    }

    size_type max_size() const
    {
        return (_allocator.max_size());
    }

    bool empty() const
    {
        return (_size == 0);
    }

    void reserve(size_type n)
    {
        pointer new_cap;

        if (n > _capacity) {
            new_cap = _allocator.allocate(n);
        }
    }

private:
    size_type _size; // current size
    size_type _capacity; // allocated size
    allocator_type _allocator;
    pointer _data;
};
} // namespace ft

#endif