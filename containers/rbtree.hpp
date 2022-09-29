/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:39 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/29 14:30:46 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>  // std::less
#include <iostream>
#include "type_traits.hpp"

namespace ft
{
	enum
	{
		RED,
		BLACK
	};

	template <typename Val>
	struct rbtree_node
	{
		typedef Val value_type;
		typedef rbtree_node<value_type> node_type;
		typedef std::allocator<node_type> node_allocator_type;
		typedef node_type *node_ptr;
		typedef const node_type *const_node_ptr;

		node_ptr parent;
		node_ptr left;
		node_ptr right;
		value_type data;
		int color;

		rbtree_node(node_ptr parent, node_ptr left, node_ptr right, value_type data, int color)
			: parent(parent), left(left), right(right), data(data), color(color)
		{
		}

		static bool isTNULL(node_ptr x)
		{
			if (x && x->left == NULL)
				return true;
			else
				return false;
		}

		static node_ptr minimum(node_ptr x)
		{
			while (x && !isTNULL(x->left))
				x = x->left;
			return x;
		}

		static const_node_ptr minimum(const_node_ptr x)
		{
			while (x && !isTNULL(x->left))
				x = x->left;
			return x;
		}

		static node_ptr maximum(node_ptr x)
		{
			while (x && !isTNULL(x->right))
				x = x->right;
			return x;
		}

		static const_node_ptr maximum(const_node_ptr x)
		{
			while (x && !isTNULL(x->right))
				x = x->right;
			return x;
		}
	};

	template <typename Key,
			  typename T,
			  typename Compare = std::less<Key>,
			  typename Alloc = std::allocator<ft::pair<const Key, T> >
			  >
	class rbtree
	{
	public:
		// Member types
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef rbtree_node<value_type> node_type;
		typedef typename node_type::node_allocator_type node_allocator_type;
		typedef typename node_type::node_ptr node_ptr;
		typedef typename node_type::const_node_ptr const_node_ptr;

		// Member functions
		rbtree()
		{
			_TNULL = _getnode(node_type(NULL, NULL, NULL, value_type(), BLACK));
			_root = _getnode(node_type(NULL, _TNULL, _TNULL, value_type(), RED));
			_TNULL->parent = _root;
		}

		const node_ptr &getRoot() const
		{
			return _root;
		}

		const node_ptr &getTNULL() const
		{
			return _TNULL;
		}

		node_ptr searchKey(key_type key)
		{
			node_ptr t = _root;

			while (t != NULL && !_equal(key, t->data.first))
			{
				if (_comp(key, t->data.first))
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

		void rbInsert(const value_type &data)
		{
			_insertNode(data);
			_TNULL->parent = _root;
		}

		void rbDelete(node_ptr &z)
		{
			_deleteNode(z);
			if (_root == _TNULL)
			{
				_root = _getnode(node_type(NULL, _TNULL, _TNULL, value_type(), RED));
			}
			_TNULL->parent = _root;
		}

	private:
		// Private member functions
		node_ptr _getnode(node_type tmp)
		{
			node_ptr ptr = _node_alloc.allocate(1);
			_node_alloc.construct(ptr, tmp);
			return ptr;
		}

		void _leftRotate(node_ptr x)
		{
			node_ptr y = x->right;
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

		void _rightRotate(node_ptr x)
		{
			node_ptr y = x->left;
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

		void _insertNode(const value_type &data)
		{
			node_ptr z = _getnode(node_type(NULL, _TNULL, _TNULL, data, RED));
			node_ptr y = NULL;
			node_ptr x = _root;

			if (_root->color == RED)
			{
				_node_alloc.deallocate(_root, 1);
				_root = z;
				_root->color = BLACK;
				return;
			}

			while (x != _TNULL)
			{
				y = x;
				if (_comp(z->data.first, x->data.first)) // data < x->data
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
			else if (_comp(z->data.first, y->data.first))
			{
				y->left = z;
			}
			else
			{
				y->right = z;
			}

			// if Z is root node
			if (z->parent == NULL)
			{
				z->color = BLACK;
				return;
			}

			// if Z's parent is root node. No need fix up.
			if (z->parent->parent == NULL)
			{
				return;
			}

			_insertFix(z);
		}

		void _insertFix(node_ptr k)
		{
			while (k != _root && k->parent->color == RED)
			{
				// if parent is left child of grandparent, side is true else side is false
				bool side = (k->parent == k->parent->parent->left);
				// set uncle node
				node_ptr u = side ? k->parent->parent->right : k->parent->parent->left;

				if (u->color == RED)
				{
					// if uncle's color is RED -> recoloring
					k->parent->color = BLACK;
					u->color = BLACK;
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

		bool _equal(const key_type &a, const key_type &b)
		{
			return !_comp(a, b) && !_comp(b, a);
		}

		void _rbTransplant(node_ptr u, node_ptr v)
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
			if (v != _TNULL)
			{
				v->parent = u->parent;
			}
		}

		bool _deleteNode(node_ptr &z)
		{
			node_ptr x, y;
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
				y = node_type::minimum(z->right);
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
			_node_alloc.deallocate(z, 1);
			z = _TNULL;
			if (y_original_color == BLACK)
			{
				_deleteFix(x);
			}
			return true;
		}

		void _deleteFix(node_ptr x)
		{
			while (x != _root && x->color == BLACK)
			{
				// if x is left child, side is true else side is false
				bool side = (x == x->parent->left);

				// set sibling node
				node_ptr s = side ? x->parent->right : x->parent->left;

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
		node_ptr _root;
		node_ptr _TNULL;
		key_compare _comp;
		node_allocator_type _node_alloc;
	};
} // namespace ft

#endif
