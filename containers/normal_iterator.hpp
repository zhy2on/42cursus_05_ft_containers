/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:49:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/22 16:58:23 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef> // std::ptrdiff_t
#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class normal_iterator
	{
	protected:
		Iterator _current;
		typedef typename ft::iterator_traits<Iterator> traits_type;
	
	public:
		typedef typename traits_type::value_type value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::reference reference;
		typedef typename traits_type::iterator_category iterator_category;

		// OCCF
		normal_iterator() // default
			: _current(0)
		{
		}

		normal_iterator(pointer ptr) // initialization
			: _current(ptr)
		{
		}

		normal_iterator(const normal_iterator &rhs) // copy-constructor
			: _current(rhs._current)
		{
		}

		virtual ~normal_iterator() // destructor
		{
		}

		normal_iterator &operator=(const normal_iterator &rhs) // copy-assignment
		{
			if (this != &rhs)
			{
				_current = rhs._current;
			}
			return (*this);
		}

		// a == b, a != b
		bool operator==(const normal_iterator &rhs) const
		{
			return (_current == rhs._current);
		}

		bool operator!=(const normal_iterator &rhs) const
		{
			return (_current != rhs._current);
		}

		// *a, a->
		reference operator*() const
		{
			return (*_current);
		}

		pointer operator->() const
		{
			return (_current);
		}

		// ++a, a++
		normal_iterator &operator++()
		{
			++_current;
			return (*this);
		}

		normal_iterator operator++(int)
		{
			normal_iterator tmp(*this);
			++(*this);
			return (tmp);
		}

		// --a, a--
		normal_iterator &operator--()
		{
			--_current;
			return (*this);
		}

		normal_iterator operator--(int)
		{
			normal_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		// a + n, a - n
		normal_iterator operator+(const int &n) const
		{
			return (normal_iterator(_current + n));
		}

		normal_iterator operator-(const int &n) const
		{
			return (normal_iterator(_current - n));
		}

		// a - b
		difference_type operator-(const normal_iterator &rhs) const
		{
			return (_current - rhs._current);
		}

		// a < b, a > b
		bool operator<(const normal_iterator &rhs) const
		{
			return (_current < rhs._current);
		}

		bool operator>(const normal_iterator &rhs) const
		{
			return (_current > rhs._current);
		}

		// a <= b, a >= b
		bool operator<=(const normal_iterator &rhs) const
		{
			return !(this > rhs);
		}

		bool operator>=(const normal_iterator &rhs) const
		{
			return !(this < rhs);
		}

		// a += n, a -= n
		normal_iterator &operator+=(const int &n)
		{
			_current += n;
			return (*this);
		}

		normal_iterator &operator-=(const int &n)
		{
			_current -= n;
			return (*this);
		}

		reference operator[](const int n) const
		{
			return (_current[n]);
		}
	};
}

#endif
