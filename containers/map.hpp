/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/30 05:54:34 by jihoh            ###   ########.fr       */
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

namespace ft
{
	template <typename Pair>
	struct Slect1st
	{
		typename Pair::first_type &operator()(Pair &x) const
		{
			return x.first;
		}

		const typename Pair::first_type &operator()(const Pair &x) const
		{
			return x.first;
		}
	};

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
		typedef ft::rbtree<key_type, value_type, Slect1st<value_type>, key_compare, allocator_type> tree_type;
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

		template <typename InputIterator>
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
			return (_bst.size() == 0);
		}

		size_type size() const
		{
			return _bst.size();
		}

		size_type max_size() const
		{
			typename tree_type::node_allocator_type _allocator;
			return ((_allocator.max_size() < PTRDIFF_MAX) ? _allocator.max_size() : PTRDIFF_MAX);
		}

		// Element access
		mapped_type &operator[](const key_type &k)
		{
			this->insert(ft::make_pair(k, mapped_type()));
			return this->find(k)->second;
		}

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val.first);
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
			for (iterator it = first++; it != last; it = first++)
			{
				_bst.rbDelete(it._node);
			}
		}

		void swap(map &x)
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
			return value_compare(key_compare());
		}

		// Operations
		iterator find(const key_type &k)
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return iterator(tmp);
			else
				return this->end();
		}

		const_iterator find(const key_type &k) const
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return const_iterator(tmp);
			else
				return this->end();
		}

		size_type count(const key_type &k) const
		{
			size_type n = 0;

			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_bst.equal(k, it->first))
				{
					++n;
				}
			}
			return n;
		}

		iterator lower_bound(const key_type &k)
		{
			iterator it = this->begin();
			while (key_comp()(it->first, k) && it != this->end())
			{
				++it;
			}
			return it;
		}

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = this->begin();
			while (key_comp()(it->first, k) && it != this->end())
			{
				++it;
			}
			return it;
		}

		iterator upper_bound(const key_type &k)
		{
			iterator it = this->begin();
			while (!key_comp()(k, it->first) && it != this->end())
			{
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = this->begin();
			while (!key_comp()(k, it->first) && it != this->end())
			{
				++it;
			}
			return (it);
		}

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
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
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif
