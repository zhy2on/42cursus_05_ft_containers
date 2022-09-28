/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:59:25 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/29 02:18:31 by jihoh            ###   ########.fr       */
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
	public:
		typedef Val value_type;
		typedef Val *pointer;
		typedef Val &reference;
		typedef rbtree_iterator<Val> self_type;

		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef ft::rbtree_node<Val> node_type;
		typedef typename node_type::node_ptr node_ptr;

        // OCCF
		rbtree_iterator() // default
			: _node(0)
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
		self_type &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		self_type &operator++()
		{
			_node = node_type::increment(_node);
			return *this;
		}

		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		self_type &operator--()
		{
			if (_node->color == ft::RED && _node->parent->parent)
			{
				_node = _node->right;
			}
			else if (!node_type::isTNULL(_node->left))
			{
				node_ptr y = _node->left;
				while (!node_type::isTNULL(_node->right))
				{
					y = y->right;
				}
				_node = y;
			}
			else
			{
				node_ptr y = _node->parent;
				while (_node == y->left)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}

		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node;
    };

	template <typename Val>
    class rbtree_const_iterator
    {
	public:
		typedef Val value_type;
		typedef const Val *pointer;
		typedef const Val &reference;
		typedef rbtree_const_iterator<Val> self_type;

		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef ft::rbtree_node<Val> node_type;
		typedef typename node_type::const_node_ptr node_ptr;

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
		self_type &operator=(const rbtree_const_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		self_type &operator++()
		{
			if (!node_type::isTNULL(_node->right))
			{
				_node = _node->right;
				while (!node_type::isTNULL(_node->left))
				{
					_node = _node->left;
				}
			}
			else
			{
				node_ptr y = _node->parent;
				while (_node == y->right)
				{
					_node = y;
					y = y->parent;
				}
				if (_node->right != y)
				{
					_node = y;
				}
			}
			return *this;
		}

		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		rbtree_const_iterator &operator--()
		{
			if (_node->color == ft::RED && _node->parent->parent)
			{
				_node = _node->right;
			}
			else if (!node_type::isTNULL(_node->left))
			{
				node_ptr y = _node->left;
				while (!node_type::isTNULL(_node->right))
				{
					y = y->right;
				}
				_node = y;
			}
			else
			{
				node_ptr y = _node->parent;
				while (_node == y->left)
				{
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}

		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node;
	};
} // namespace ft

#endif
