/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:59:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/16 18:03:02 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include <cstddef> // std::ptrdiff_t
#include "iterator_traits.hpp"

namespace ft
{
    template <typename T>
    class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator_traits<map_iterator<T>>::value_type value_type;
        typedef typename ft::iterator_traits<map_iterator<T>>::difference_type difference_type;
        typedef typename ft::iterator_traits<map_iterator<T>>::pointer pointer;
        typedef typename ft::iterator_traits<map_iterator<T>>::reference reference;
        typedef typename ft::iterator_traits<map_iterator<T>>::iterator_category iterator_category;
        // OCCF
        map_iterator() // default
            : _ptr(0)
        {
        }

        map_iterator(pointer ptr) // initialization
            : _ptr(ptr)
        {
        }

        map_iterator(const map_iterator &rhs) // copy-constructor
            : _ptr(rhs._ptr)
        {
        }

        virtual ~map_iterator() // destructor
        {
        }

        map_iterator &operator=(const map_iterator &rhs) // copy-assignment
        {
            if (this != &rhs)
            {
                _ptr = rhs._ptr;
            }
            return (*this);
        }

        // a == b, a != b
        bool operator==(const map_iterator &rhs) const
        {
            return (_ptr == rhs._ptr);
        }

        bool operator!=(const map_iterator &rhs) const
        {
            return (_ptr != rhs._ptr);
        }

        // *a, a->
        reference operator*() const
        {
            return (*_ptr);
        }

        pointer operator->() const
        {
            return (_ptr);
        }

        // ++a, a++
        map_iterator &operator++()
        {
            ++_ptr;
            return (*this);
        }

        map_iterator operator++(int)
        {
            map_iterator tmp(*this);
            ++(*this);
            return (tmp);
        }

        // --a, a--
        map_iterator &operator--()
        {
            --_ptr;
            return (*this);
        }

        map_iterator operator--(int)
        {
            map_iterator tmp(*this);
            --(*this);
            return (tmp);
        }

    private:
        pointer _ptr;
    };
} // namespace ft

#endif