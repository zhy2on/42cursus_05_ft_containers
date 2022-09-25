/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:38:33 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/25 17:47:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
    template <typename T>
    void swap(T &a, T &b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template <typename InputIterator1, typename InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
            {
                return false;
            }
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, BinaryPredicate pred)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!pred(*first1, *first2))
            {
                return false;
            }
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

} // namespace ft

#endif