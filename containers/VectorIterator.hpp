/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:49:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/31 19:15:29 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ft {
template <typename T>
class VectorIterator : std::iterator<std::random_access_iterator_tag, T> {
public:
    // OCCF
    VectorIterator() // default
        : _ptr(0)
    {
    }

    VectorIterator(const VectorIterator& rhs) // copy-constructor
        : _ptr(rhs._ptr)
    {
    }

    virtual ~VectorIterator() // destructor
    {
    }

    VectorIterator& operator=(const VectorIterator& rhs) // copy-assignment
    {
        if (this != &rhs) {
            _ptr = rhs.ptr;
        }
        return (*this);
    }

    // a == b, a != b
    bool operator==(const VectorIterator& rhs) const
    {
        return (_ptr == rhs._ptr);
    }

    bool operator!=(const VectorIterator& rhs) const
    {
        return (_ptr != rhs._ptr);
    }

    // *a, a->
    T& operator*() const
    {
        return (*_ptr);
    }

    T* operator->() const
    {
        return (_ptr);
    }

    // ++a, a++
    VectorIterator& operator++()
    {
        ++ptr;
        return (*this);
    }

    VectorIterator operator++(int)
    {
        VectorIterator tmp(*this);
        ++(*this);
        return (tmp);
    }

    // --a, a--
    VectorIterator& operator--()
    {
        --ptr;
        return (*this);
    }

    VectorIterator operator--(int)
    {
        VectorIterator tmp(*this);
        --(*this);
        return (tmp);
    }

    // a + n, a - n
    VectorIterator operator+(const int& n) const
    {
        return (VectorIterator(_ptr + n));
    }

    VectorIterator operator-(const int& n) const
    {
        return (VectorIterator(_ptr - n));
    }

    // a - b
    std::ptr_diff_t operator-(const VectorIterator &rhs) const
    {
        return (_ptr - rhs._ptr);
    }

    // a < b, a > b
    bool operator<(const VectorIterator &rhs) const
    {
        return (_ptr < rhs._ptr);
    }

    bool operator>(const VectorIterator &rhs) const
    {
        return (_ptr > rhs._ptr);
    }

    // a <= b, a >= b
    bool operator<=(const VectorIterator &rhs) const
    {
        return !(this > rhs);
    }

    bool operator>=(const VectorIterator &rhs) const
    {
        return !(this < rhs);
    }

    // a += n, a -= n
    VectorIterator& operator+=(const int &n)
    {
        _ptr += n;
        return (*this);
    }

    VectorIterator& operator-=(const int &n)
    {
        _ptr -= n;
        return (*this);
    }

    T& operator[](const int n) const
    {
        return (_ptr[n]);
    }

private:
    T* _ptr;

    VectorIterator(T* ptr) // initialization
        : _ptr(ptr)
    {
    }
};
}

#endif