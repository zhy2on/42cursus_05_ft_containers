/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/21 22:27:09 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp" // ft::pair
#include "rbtree.hpp"
#include <functional> // std::less
#include <cstddef>	  // std::ptrdiff_t, std::size_t
#include <iostream>

namespace ft
{
	template <class Key,										   // map::key_type
			  class T,											   // map::mapped_type
			  class Compare = std::less<Key>,					   // map::key_compare
			  class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
	public:
		// Member types
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		// typedef ft::map_iterator<value_type, node_type> iterator;
		// typedef ft::map_iterator<const value_type, node_type> const_iterator;
		// typedef ft::reverse_iterator<iterator> reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		class value_compare
		{
			friend class map;

		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {} // constructed with map's comparison object

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return _comp(x.first, y.first);
			}
		};

		map()
			: _comp_val(value_compare(_comp_key))
		{
		}

		// Member functions
		void insert(value_type k)
		{
			_bst.insertNode(k);
		}

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

	private:
		key_compare _comp_key;
		value_compare _comp_val;
		// ft::rbtree<map<Key, T, Compare, Alloc> > _bst;
		ft::rbtree<map> _bst;
	};

} // namespace ft

#endif
