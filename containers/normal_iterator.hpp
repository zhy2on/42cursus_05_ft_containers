/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:49:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/30 04:56:09 by jihoh            ###   ########.fr       */
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

		explicit normal_iterator(Iterator iter) // initialization
			: _current(iter)
		{
		}

		template <typename Iter>
		normal_iterator(const normal_iterator<Iter> &rhs) // copy-constructor
			: _current(rhs.base())
		{
		}

		virtual ~normal_iterator() // destructor
		{
		}

		template <typename Iter>
		normal_iterator &operator=(const normal_iterator<Iter> &rhs) // copy-assignment
		{
			_current = rhs.base();
			return *this;
		}

		Iterator base() const
		{
			return _current;
		}

		// operators
		reference operator*() const
		{
			return *_current;
		}

		normal_iterator operator+(difference_type n) const
		{
			return (normal_iterator(_current + n));
		}

		normal_iterator &operator++()
		{
			++_current;
			return *this;
		}

		normal_iterator operator++(int)
		{
			normal_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		normal_iterator &operator+=(difference_type n)
		{
			_current += n;
			return *this;
		}

		normal_iterator operator-(difference_type n) const
		{
			return (normal_iterator(_current - n));
		}

		normal_iterator &operator--()
		{
			--_current;
			return *this;
		}

		normal_iterator operator--(int)
		{
			normal_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		normal_iterator &operator-=(difference_type n)
		{
			_current -= n;
			return *this;
		}

		pointer operator->() const
		{
			return _current;
		}

		reference operator[](const int n) const
		{
			return _current[n];
		}
	};

	// Non-member functions
	template <typename Iterator1, typename Iterator2>
	bool operator==(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<(const normal_iterator<Iterator1> &lhs,
				   const normal_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>(const normal_iterator<Iterator1> &lhs,
				   const normal_iterator<Iterator2> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator>
	normal_iterator<Iterator> operator+(
		typename normal_iterator<Iterator>::difference_type n,
		const normal_iterator<Iterator> &it)
	{
		return normal_iterator<Iterator>(it.base() + n);
	}

	template <typename Iterator1, typename Iterator2>
	typename normal_iterator<Iterator1>::difference_type operator-(
		const normal_iterator<Iterator1> &lhs,
		const normal_iterator<Iterator2> &rhs)
	{
		return lhs.base() - rhs.base();
	}
}

#endif
