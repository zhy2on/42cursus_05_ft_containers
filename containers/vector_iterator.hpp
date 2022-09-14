/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:49:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/14 14:46:03 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef> // std::ptrdiff_t
#include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator_traits<vector_iterator<T> >::value_type value_type;
		typedef typename ft::iterator_traits<vector_iterator<T> >::difference_type difference_type;
		typedef typename ft::iterator_traits<vector_iterator<T> >::pointer pointer;
		typedef typename ft::iterator_traits<vector_iterator<T> >::reference reference;
		typedef typename ft::iterator_traits<vector_iterator<T> >::iterator_category iterator_category;

		// OCCF
		vector_iterator() // default
			: _ptr(0)
		{
		}

		vector_iterator(pointer ptr) // initialization
			: _ptr(ptr)
		{
		}

		vector_iterator(const vector_iterator &rhs) // copy-constructor
			: _ptr(rhs._ptr)
		{
		}

		virtual ~vector_iterator() // destructor
		{
		}

		vector_iterator &operator=(const vector_iterator &rhs) // copy-assignment
		{
			if (this != &rhs)
			{
				_ptr = rhs._ptr;
			}
			return (*this);
		}

		// a == b, a != b
		bool operator==(const vector_iterator &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(const vector_iterator &rhs) const
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
		vector_iterator &operator++()
		{
			++_ptr;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp(*this);
			++(*this);
			return (tmp);
		}

		// --a, a--
		vector_iterator &operator--()
		{
			--_ptr;
			return (*this);
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		// a + n, a - n
		vector_iterator operator+(const int &n) const
		{
			return (vector_iterator(_ptr + n));
		}

		vector_iterator operator-(const int &n) const
		{
			return (vector_iterator(_ptr - n));
		}

		// a - b
		difference_type operator-(const vector_iterator &rhs) const
		{
			return (_ptr - rhs._ptr);
		}

		// a < b, a > b
		bool operator<(const vector_iterator &rhs) const
		{
			return (_ptr < rhs._ptr);
		}

		bool operator>(const vector_iterator &rhs) const
		{
			return (_ptr > rhs._ptr);
		}

		// a <= b, a >= b
		bool operator<=(const vector_iterator &rhs) const
		{
			return !(this > rhs);
		}

		bool operator>=(const vector_iterator &rhs) const
		{
			return !(this < rhs);
		}

		// a += n, a -= n
		vector_iterator &operator+=(const int &n)
		{
			_ptr += n;
			return (*this);
		}

		vector_iterator &operator-=(const int &n)
		{
			_ptr -= n;
			return (*this);
		}

		reference operator[](const int n) const
		{
			return (_ptr[n]);
		}

	private:
		pointer _ptr;
	};
}

#endif
