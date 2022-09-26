/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:59:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/26 22:39:02 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR
#define RBTREE_ITERATOR

#include <cstddef> // std::ptrdiff_t
#include "rbtree.hpp"
#include "iterator_traits.hpp" // iterator_tag

namespace ft
{
    template <typename Val>
    class rbtree_iterator
    {
    protected:
		typename ft::rbtree_node<Val>::node_ptr _node;
	
	public:
		typedef Val value_type;
		typedef Val *pointer;
		typedef Val &reference;

		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef typename ft::rbtree_node<Val>::node_ptr node_ptr;

        // OCCF
		rbtree_iterator() // default
			: _node(NULL)
		{
		}

		explicit rbtree_iterator(node_ptr x) // initialization
			: _node(x)
		{
		}

		template <typename T>
		rbtree_iterator(const rbtree_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		virtual ~rbtree_iterator() // destructor
		{
		}

		template <typename T>
		rbtree_iterator &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		rbtree_iterator &operator++()
		{
			_node = ft::rbtree_node<value_type>::increment(_node);
			return *this;
		}

		rbtree_iterator operator++(int)
		{
			rbtree_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		rbtree_iterator &operator--()
		{
			_node = ft::rbtree_node<value_type>::decrement(_node);
			return *this;
		}

		rbtree_iterator operator--(int)
		{
			rbtree_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}
    };

	template <typename Val>
    class rbtree_const_iterator
    {
    protected:
		typename ft::rbtree_node<Val>::const_node_ptr _node;
	
	public:
		typedef Val value_type;
		typedef const Val *pointer;
		typedef const Val &reference;

		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef typename ft::rbtree_node<Val>::const_node_ptr node_ptr;

        // OCCF
		rbtree_const_iterator() // default
			: _node(NULL)
		{
		}

		explicit rbtree_const_iterator(node_ptr x) // initialization
			: _node(x)
		{
		}

		template <typename T>
		rbtree_const_iterator(const rbtree_const_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		virtual ~rbtree_const_iterator() // destructor
		{
		}

		template <typename T>
		rbtree_const_iterator &operator=(const rbtree_const_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		rbtree_const_iterator &operator++()
		{
			_node = ft::rbtree_node<value_type>::increment(_node);
			return *this;
		}

		rbtree_const_iterator operator++(int)
		{
			rbtree_const_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		rbtree_const_iterator &operator--()
		{
			_node = ft::rbtree_node<value_type>::decrement(_node);
			return *this;
		}

		rbtree_const_iterator operator--(int)
		{
			rbtree_const_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}
    };
} // namespace ft

#endif
