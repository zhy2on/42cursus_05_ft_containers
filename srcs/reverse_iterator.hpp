/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:47:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/27 21:18:44 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {
template <class Iterator>
class reverse_iterator {
public:
	// Member types
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	// Member functions
	// OCCF
	reverse_iterator()
		: _base_iterator(iterator_type())
	{
	}
	explicit reverse_iterator(iterator_type it)
		: _base_iterator(it)
	{
	}
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: _base_iterator(
			rev_it.base())
	{
	}
	~reverse_iterator() { }

	// others
	iterator_type base() const
	{
		return (_base_iterator);
	}

	reference operator*() const
	{
		iterator_type tmp = _base_iterator;
		return (*(--tmp));
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (reverse_iterator(_base_iterator - n));
	}

	reverse_iterator& operator++()
	{
		--(_base_iterator);
		return (*this);
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	reverse_iterator& operator+=(difference_type n)
	{
		_base_iterator -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (reverse_iterator(_base_iterator + n));
	}

	reverse_iterator& operator--()
	{
		++(_base_iterator);
		return (*this);
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	reverse_iterator& operator-=(difference_type n)
	{
		_base_iterator += n;
		return (*this);
	}

	pointer operator->() const
	{
		iterator_type tmp(_base_iterator);
		tmp--;
		return (tmp.operator->());
		// return &(operator*());
	}

	reference operator[](difference_type n) const
	{
		return (base()[-n - 1]);
	}

private:
	iterator_type _base_iterator; // A copy of the original iterator
};
}