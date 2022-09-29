/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/29 15:04:00 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp" // ft::pair
#include "rbtree.hpp"
#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"
#include <functional> // std::less
#include <cstddef>	  // std::ptrdiff_t, std::size_t
#include <iostream>

namespace ft
{
	template <typename Key,											  // map::key_type
			  typename T,											  // map::mapped_type
			  typename Compare = std::less<Key>,					  // map::key_compare
			  typename Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
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
		typedef ft::rbtree_iterator<value_type> iterator;
		typedef ft::rbtree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

	protected:
		typedef ft::rbtree<key_type, mapped_type> tree_type;
		typedef typename tree_type::node_type node_type;
		typedef typename tree_type::node_ptr node_ptr;

	public:
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

		// OCCF
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		}

		map(const map &x)
		{
			*this = x;
		}

		~map()
		{
			this->clear();
		}

		map &operator=(const map &x)
		{
			if (this != &x)
			{
				this->clear();
				for (const_iterator it = x.begin(); it != x.end(); it++)
				{
					this->insert(*it);
				}
			}
			return *this;
		}

		// Member functions
		// Iterators
		iterator begin()
		{
			if (this->empty())
				return this->end();
			return (iterator(node_type::minimum(_bst.getRoot())));
		}

		const_iterator begin() const
		{
			if (this->empty())
				return this->end();
			return (const_iterator(node_type::minimum(_bst.getRoot())));
		}

		iterator end()
		{
			return iterator(_bst.getTNULL());
		}

		const_iterator end() const
		{
			return const_iterator(_bst.getTNULL());
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		// Capacity
		bool empty() const
		{
			return (_bst.getRoot()->color == RED);
		}

		size_type size() const
		{
			size_t n = 0;
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				++n;
			}
			return n;
		}

		size_type max_size() const
		{
			typename tree_type::node_allocator_type _allocator;
			return ((_allocator.max_size() < PTRDIFF_MAX) ? _allocator.max_size() : PTRDIFF_MAX);
		}

		// Element access
		mapped_type &operator[](const key_type &k)
		{
			ft::pair<iterator, bool> ret;
			ret = this->insert(ft::make_pair(k, mapped_type()));
			return ret.first->second;
		}

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val.first);
			if (!tmp)
			{
				_bst.rbInsert(val);
				return ft::make_pair(iterator(tmp), true);
			}
			else
			{
				return ft::make_pair(iterator(this->end()), false);
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return this->insert(val).first;
		}

		template <class InputIterator>
		void insert(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		}

		void erase(iterator position)
		{
			_bst.rbDelete(position._node);
		}

		size_type erase(const key_type &k)
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
			{
				_bst.rbDelete(tmp);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; ++it)
			{
				this->erase(it);
			}
		}

		void swap(map &x)
		{
			ft::swap(_bst.getRoot(), x._bst.getRoot());
		}

		void clear()
		{
			while (!this->empty())
			{
				this->erase(this->begin());
			}
		}

		// Observers
		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		// Operations
		iterator find(const key_type &k)
		{
			iterator tmp = _bst.searchKey(k);
			if (tmp)
				return iterator(tmp);
			else
				return this->end();
		}

		const_iterator find(const key_type &k) const
		{
			const_iterator tmp = _bst.searchKey(k);
			if (tmp)
				return const_iterator(tmp);
			else
				return this->end();
		}

		size_type count(const key_type &k) const
		{
			size_type n = 0;

			for (const_iterator it = this->begin(); it != this->end(); it++)
			{
				if (_bst._equal(k, it->first))
				{
					n++;
				}
			}
			return n;
		}

	private:
		tree_type _bst;
	};

} // namespace ft

#endif
