/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:39 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/21 23:20:18 by jihoh            ###   ########.fr       */
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
		typedef typename Container::value_type value_type;
		typedef typename Container::allocator_type allocator_type;
		typedef typename Container::value_compare value_compare;
		
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

			node(value_type data, int color)
				: parent(NULL), left(NULL), right(NULL), color(color), data(data)
			{
			}
		};

		typedef node node_type;
		typedef node *node_pointer;
		typedef std::allocator<node> node_allocator_type;

		// Member functions
		// constructor
		rbtree(value_compare comp_val)
			: _comp_val(comp_val)
		{
			_TNULL = _node_alloc.allocate(1);
			node_type tmp(value_type(), BLACK);
			_node_alloc.construct(_TNULL, tmp);
			_root = _TNULL;
		}

		// getRoot
		const node_pointer getRoot() const
		{
			return _root;
		}

		// void inorder(node_pointer target)
		// {
		// 	if (target == _TNULL)
		// 		return;
		// 	inorder(target->left);
		// 	std::cout << target->data.first << " ";
		// 	inorder(target->right);
		// }

		// minimum: leftmost node
		node_pointer minimum(const node_pointer x) const
		{
			while (x->left != _TNULL)
			{
				x = x->left;
			}
			return x;
		}

		// maximum: rightmost node
		node_pointer maximum(const node_pointer x) const
		{
			while (x->right != _TNULL)
			{
				x = x->right;
			}
			return x;
		}

		// insertNode
		void insertNode(const value_type &data)
		{
			node_pointer z = _getnode(NULL, data, RED);
			node_pointer y = NULL;
			node_pointer x = _root;

			while (x != _TNULL)
			{
				y = x;
				if (_comp_val(z->data, x->data)) // data < x->data
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			z->parent = y;
			if (y == NULL)
			{
				_root = z;
			}
			else if (_comp_val(z->data, y->data))
			{
				y->left = z;
			}
			else
			{
				y->right = z;
			}

			if (z->parent == NULL)
			{
				z->color = BLACK;
				return;
			}

			if (z->parent->parent == NULL)
			{
				return;
			}

			_insertFix(z);
		}

		// deleteNode
		bool deleteNode(const value_type &data)
		{
			node_pointer z = _searchKey(data);
			node_pointer x, y;
			// if key is not found
			if (z == _TNULL)
			{
				return false;
			}
			// if key is exist
			y = z;
			int y_original_color = y->color;
			if (z->left == _TNULL)
			{
				x = z->right;
				_rbTransplant(z, z->right);
			}
			else if (z->right == _TNULL)
			{
				x = z->left;
				_rbTransplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					_rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			_node_alloc.deallocate(z);
			if (y_original_color == BLACK)
			{
				_deleteFix(x);
			}
			return true;
		}

	private:
		// Private member functions
		node_pointer _getnode(node_pointer parent, const value_type &data, const int &color)
		{
			node_pointer ptr = _node_alloc.allocate(1);
			node_type tmp(data, color);

			tmp.parent = _TNULL;
			tmp.left = _TNULL;
			tmp.right = _TNULL;
			_node_alloc.construct(ptr, tmp);

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
			if (x->parent == NULL)
			{
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
			// if parent is left child of grandparent, side is true else side is false
			bool side = (k->parent == k->parent->parent->left);
			// set uncle node
			node_pointer u = side ? k->parent->parent->right : k->parent->parent->left;

			while (k != _root && k->parent->color == RED)
			{
				if (u->color == RED)
				{
					// if uncle's color is RED -> recoloring
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else
				{
					// if uncle is not exist or uncle's color is BLACK -> restructuring
					if (k == (side ? k->parent->right : k->parent->left))
					{
						k = k->parent;
						side ? _leftRotate(k) : _rightRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					side ? _rightRotate(k->parent->parent) : _leftRotate(k->parent->parent);
				}
			}
			_root->color = BLACK;
		}

		bool _equal(const value_type &a, const value_type &b)
		{
			return !_comp_val(a, b) && !_comp_val(b, a);
		}

		node_pointer _searchKey(value_type data)
		{
			node_pointer t = _root;
			
			while (t != _TNULL && !_equal(data, t->data))
			{
				if (_comp_val(data, t->data))
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
			}
			return t;
		}

		void _rbTransplant(node_pointer u, node_pointer v)
		{
			if (u->parent == NULL)
			{
				_root = v;
			}
			else if (u == u->parent->left)
			{
				u->parent->left = v;
			}
			else
			{
				u->parent->right = v;
			}
			v->parent = u->parent;
		}

		void _deleteFix(node_pointer x)
		{
			// if x is left child, side is true else side is false
			bool side = (x == x->parent->left);
			// set sibling node
			node_pointer s = side ? x->parent->right : x->parent->left;

			while (x != _root && x->color == BLACK)
			{
				// case 1
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					side ? _leftRotate(x->parent) : _rightRotate(x->parent);
					s = side ? x->parent->right : x->parent->left;
				}
				// case 2
				if (s->left->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					// case 3
					if ((side ? s->right->color : s->left->color) == BLACK)
					{
						(side ? s->left->color : s->right->color) = BLACK;
						s->color = RED;
						side ? _rightRotate(s) : _leftRotate(s);
						s = side ? x->parent->right : x->parent->left;
					}
					// case 4
					s->color = x->parent->color;
					x->parent->color = BLACK;
					(side ? s->right->color : s->left->color) = BLACK;
					side ? _leftRotate(x->parent) : _rightRotate(x->parent);
					x = _root;
				}
			}
			x->color = BLACK;
			_root->color = BLACK;
		}

		// Member variables
		node_pointer _root;
		node_pointer _TNULL;
		value_compare _comp_val;
		node_allocator_type _node_alloc;
	};
} // namespace ft

#endif
