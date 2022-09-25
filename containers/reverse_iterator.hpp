/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:47:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/25 16:51:32 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator
		: public iterator<typename ft::iterator_traits<Iterator>::iterator_category,
						  typename ft::iterator_traits<Iterator>::value_type,
						  typename ft::iterator_traits<Iterator>::difference_type,
						  typename ft::iterator_traits<Iterator>::pointer,
						  typename ft::iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator _base_iterator; // A copy of the original iterator
		typedef typename ft::iterator_traits<Iterator> traits_type;

	public:
		// Member types
		typedef Iterator iterator_type;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type value_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::reference reference;

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

		template <typename Iter>
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
	};

	// Non-member function overloads
	// relational operators
	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	// operator+
	template <typename Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	// operator-
	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
} // namespace ft

#endif
