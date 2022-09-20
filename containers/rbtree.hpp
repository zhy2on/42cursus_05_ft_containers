/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:39 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/20 18:44:22 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>  // std::less
#include <iostream>
#include "type_traits.hpp"

namespace ft
{
	template <typename Container>
	class rbtree
	{
	public:
		// Member types
		typedef typename Container::key_type key_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::pointer pointer;
		typedef typename Container::key_compare key_compare;
		typedef typename Container::allocator_type allocator_type;

		enum
		{
			RED,
			BLACK
		};

		struct node
		{
			value_type data;
			node *parent;
			node *left;
			node *right;
			int color;
		};

		typedef node node_type;
		typedef node *node_pointer;
		typedef std::allocator<node> node_allocator;

		// Member functions
		// constructor
		rbtree()
		{
			_TNULL = _getnode(NULL, value_type(), BLACK);
			_root = _TNULL;
		}

		// minimum: 노드 기준 가장 왼쪽에 있는 노드 반환
		node_pointer minimum(node_pointer node)
		{
			while (node->left != _TNULL)
			{
				node = node->left;
			}
			return node;
		}

		// maximum: 노드 기준 가장 오른쪽에 있는 노드 반환
		node_pointer maximum(node_pointer node)
		{
			while (node->right != _TNULL)
			{
				node = node->right;
			}
			return node;
		}

		// insert - map
		void insert(const value_type &data)
		{
			node_pointer node = _getnode(NULL, data, RED);

			node_pointer y = NULL;
			node_pointer x = _root;

			while (x != _TNULL)
			{
				y = x;
				if (!_comp(data.first, x->data.first))
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			node->parent = y;
			if (y == NULL)
			{
				root = node;
			}
			else if (_comp(data.first, x->data.first))
			{
				y->left = node;
			}
			else
			{
				y->right = node;
			}

			if (node->parent == NULL)
			{
				node->color = BLACK;
				return;
			}

			if (node->parent->parent == NULL)
			{
				return;
			}

			_insertFix(node);
		}

	private:
		// Member variables
		node_pointer _root;
		node_pointer _TNULL;
		key_compare _comp;

		// Private member functions
		void _initializeNULLNode(node_pointer node, node_pointer parent)
		{
			node->data = NULL;
			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
			node->color = BLACK;
		}

		node_pointer _getnode(node_pointer parent, value_type data, int color)
		{
			node_type tmp;
			node_pointer ptr;

			tmp.parent = parent;
			tmp.data = data;
			tmp.left = NULL;
			tmp.right = NULL;
			tmp.color = color;
			node_allocator(ptr, tmp);
			return ptr;
		}

		void _leftRotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _TNULL)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				_root = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void _rightRotate(node_pointer x)
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _TNULL)
			{
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				_root = y;
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y;
			}
			else
			{
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		void _insertFix(node_pointer k)
		{
			node_pointer u;

			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rightRotate(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_leftRotate(k->parent->parent);
					}
				}
			}
		}
		
	};
} // namespace ft

#endif
