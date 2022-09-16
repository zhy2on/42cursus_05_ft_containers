/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/16 19:34:29 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"
#include <functional> // std::less

namespace ft
{
    template <class Key,                                           // map::key_type
              class T,                                             // map::mapped_type
              class Compare = std::less<Key>,                      // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        // typedef ft::node<value_type> node_type;
        // typedef node_type *node_ptr;

        typedef ft::map_iter ator<value_type, node_type> iterator;
        typedef ft::map_iterator<const value_type, node_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    };

} // namespace ft

#endif
