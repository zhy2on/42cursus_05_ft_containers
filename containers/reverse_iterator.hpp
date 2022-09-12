/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:47:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/12 20:20:23 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator : public iterator<typename ft::iterator_traits<Iterator>::iterator_category, Iterator>
	{
	public:
		// Member types
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;

		// Member functions
		// constructor
		reverse_iterator()
			: _base_iterator(iterator_type()) // default
		{
		}

		explicit reverse_iterator(iterator_type it)
			: _base_iterator(it) // initialization
		{
		}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
			: _base_iterator(rev_it.base()) // copy-constructor
		{
		}

		// return base iterator
		iterator_type base() const
		{
			return (_base_iterator);
		}

		// operators
		reference operator*() const
		{
			iterator_type tmp = _base_iterator;
			return (*(--tmp));
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(_base_iterator - n));
		}

		reverse_iterator &operator++()
		{
			--(_base_iterator);
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_base_iterator -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(_base_iterator + n));
		}

		reverse_iterator &operator--()
		{
			++(_base_iterator);
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_base_iterator += n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return (base()[-n - 1]);
		}

	private:
		iterator_type _base_iterator; // A copy of the original iterator
	};

	// Non-member function overloads
	// relational operators
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	// operator+
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	// operator-
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
} // namespace ft

#endif