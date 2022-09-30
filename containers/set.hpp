/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/30 18:34:34 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "utility.hpp" // ft::pair
#include "rbtree.hpp"
#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"
#include <functional> // std::less
#include <cstddef>	  // std::ptrdiff_t, std::size_t
#include <iostream>

namespace ft
{
	template <typename T>
	struct Identity
	{
		T &operator()(T &x) const
		{
			return x;
		}

		const T &operator()(const T &x) const
		{
			return x;
		}
	};

	template <typename Key,							   // set::key_type/value_type
			  typename Compare = std::less<Key>,	   // set::key_compare/value_compare
			  typename Alloc = std::allocator<Key> // set::allocator_type
			  >
	class set
	{
	public:
		// Member types
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::rbtree_const_iterator<value_type> iterator;
		typedef ft::rbtree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

	protected:
		typedef ft::rbtree<key_type, value_type, Identity<value_type>, key_compare, allocator_type> tree_type;
		typedef typename tree_type::node_type node_type;
		typedef typename tree_type::node_ptr node_ptr;

	public:

		// OCCF
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
		}

		template <typename InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		}

		set(const set &x)
		{
			*this = x;
		}

		~set()
		{
			this->clear();
		}

		set &operator=(const set &x)
		{
			if (this != &x)
			{
				this->clear();
				for (const_iterator it = x.begin(); it != x.end(); ++it)
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
			return iterator(node_type::minimum(_bst.getRoot()));
		}

		const_iterator begin() const
		{
			if (this->empty())
				return this->end();
			return const_iterator(node_type::minimum(_bst.getRoot()));
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
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity
		bool empty() const
		{
			return (_bst.size() == 0);
		}

		size_type size() const
		{
			return _bst.size();
		}

		size_type max_size() const
		{
			typename tree_type::node_allocator_type _allocator;
			return (_allocator.max_size() < PTRDIFF_MAX) ? _allocator.max_size() : PTRDIFF_MAX;
		}

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val);
			if (tmp)
			{
				return ft::make_pair(iterator(tmp), false);
			}
			else
			{
				tmp = _bst.rbInsert(val);
				return ft::make_pair(iterator(tmp), true);
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return this->insert(val).first;
		}

		template <typename InputIterator>
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
			_bst.rbDelete(const_cast<node_ptr>(position._node));
		}

		size_type erase(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val);
			if (tmp)
			{
				_bst.rbDelete(const_cast<node_ptr>(tmp));
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			for (iterator it = first++; it != last; it = first++)
			{
				_bst.rbDelete(const_cast<node_ptr>(it._node));
			}
		}

		void swap(set &x)
		{
			_bst.swap(x._bst);
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
			return key_compare();
		}

		// Operations
		iterator find(const key_type &k) const
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return iterator(tmp);
			else
				return this->end();
		}

		size_type count(const key_type &k) const
		{
			size_type n = 0;

			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_bst.equal(k, *it))
				{
					++n;
				}
			}
			return n;
		}

		iterator lower_bound(const key_type &k) const
		{
			iterator it = this->begin();
			while (key_comp()(*it, k) && it != this->end())
			{
				++it;
			}
			return it;
		}

		iterator upper_bound(const key_type &k) const
		{
			iterator it = this->begin();
			while (!key_comp()(k, *it) && it != this->end())
			{
				++it;
			}
			return it;
		}

		ft::pair<iterator, iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		// Allocator
		allocator_type get_allocator() const
		{
			return allocator_type();
		}

	private:
		tree_type _bst;
	};

	// Non-member functions
	// Relational operatiors
	template <typename Key, typename Compare, typename Alloc>
	bool operator==(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator!=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator<(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator<=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator>(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator>=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Key, typename Compare, typename Alloc>
	void swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif
