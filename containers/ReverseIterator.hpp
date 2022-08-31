/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:47:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/31 17:48:13 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {
template <class Iterator>
class ReverseIterator {
public:
    // Member types
    typedef Iterator iterator_type;
    typedef
        typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::reference reference;

    // Member functions
    // constructor
    ReverseIterator()
        : _base_iterator(iterator_type()) // default
    {
    }

    explicit ReverseIterator(iterator_type it)
        : _base_iterator(it) // initialization
    {
    }

    template <class Iter>
    ReverseIterator(const ReverseIterator<Iter>& rev_it)
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

    ReverseIterator operator+(difference_type n) const
    {
        return (ReverseIterator(_base_iterator - n));
    }

    ReverseIterator& operator++()
    {
        --(_base_iterator);
        return (*this);
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ReverseIterator& operator+=(difference_type n)
    {
        _base_iterator -= n;
        return (*this);
    }

    ReverseIterator operator-(difference_type n) const
    {
        return (ReverseIterator(_base_iterator + n));
    }

    ReverseIterator& operator--()
    {
        ++(_base_iterator);
        return (*this);
    }

    ReverseIterator operator--(int)
    {
        ReverseIterator tmp = *this;
        --(*this);
        return tmp;
    }

    ReverseIterator& operator-=(difference_type n)
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
bool operator==(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<=(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator>(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>=(const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (lhs.base() <= rhs.base());
}

// operator+
template <class Iterator>
ReverseIterator<Iterator> operator+(
    typename ReverseIterator<Iterator>::difference_type n,
    const ReverseIterator<Iterator>& rev_it)
{
    return (rev_it + n);
}

// operator-
template <class Iterator>
typename ReverseIterator<Iterator>::difference_type operator-(
    const ReverseIterator<Iterator>& lhs,
    const ReverseIterator<Iterator>& rhs)
{
    return (rhs.base() - lhs.base());
}
}