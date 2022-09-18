/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:39 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/18 16:31:04 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "utility.hpp" // ft::pair
#include <functional> // std::less
#include <iostream>

namespace ft
{
	template <typename Key,
			  typename T,
			  typename Compare = std::less<Key>,
			  typename Alloc = std::allocator<ft::pair<const Key, T> >
	>
	class rbtree
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		enum Color
		{
			BLACK,
			RED
		};

		struct Node
		{
			value_type data;
			Node *parent;
			Node *left;
			Node *right;
			Color color;
		};

		typedef Node<value_type> node_type;
		typedef Node<value_type> *node_pointer;

	private:
		std::allocator<node_type> _nodeAlloc;
		node_pointer _root;
		node_pointer _TNULL;
		key_compare _comp;
		
		// new node
		node_pointer getNode(value_type data)
		{
			node_type node;
			node_pointer ptr;

			node.parent = NULL;
			node.data = data;
			node.left = _TNULL;
			node.right = _TNULL;
			node.color = RED;

			_nodeAlloc(ptr, node);
			return ptr;
		}

		void initializeNULLNode(node_pointer node, node_pointer parent)
		{
			node->data = 0;
			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
			node->color = BLACK;
		}

		// Preorder
		void preOrderHelper(node_pointer node)
		{
			if (node != _TNULL)
			{
				std::cout << node->data << " ";
				preOrderHelper(node->left);
				preOrderHelper(node->right);
			}
		}

		// Inorder
		void inOrderHelper(node_pointer node)
		{
			if (node != _TNULL)
			{
				inOrderHelper(node->left);
				std::cout << node->data << " ";
				inOrderHelper(node->right);
			}
		}

		// Post order
		void postOrderHelper(node_pointer node)
		{
			if (node != _TNULL)
			{
				postOrderHelper(node->left);
				postOrderHelper(node->right);
				std::cout << node->data << " ";
			}
		}

		node_pointer searchTreeHelper(node_pointer node, key_type key)
		{
			if (node == _TNULL || !key_compare()(key, node->data->first))
			{
				return node;
			}

			if (key < node->data)
			{
				return searchTreeHelper(node->left, key);
			}
			return searchTreeHelper(node->right, key);
		}

		// For balancing the tree after deletion
		void deleteFix(node_pointer x)
		{
			node_pointer s;
			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							rightRotate(s);
							s = x->parent->right;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							leftRotate(s);
							s = x->parent->left;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}

		void rbTransplant(node_pointer u, node_pointer v)
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

		void deleteNodeHelper(node_pointer node, int key)
		{
			node_pointer z = _TNULL;
			node_pointer x, y;
			while (node != _TNULL)
			{
				if (node->data == key)
				{
					z = node;
				}

				if (node->data <= key)
				{
					node = node->right;
				}
				else
				{
					node = node->left;
				}
			}

			if (z == _TNULL)
			{
				// std::cout << "Key not found in the tree" << std::endl;
				return;
			}

			y = z;
			int y_original_color = y->color;
			if (z->left == _TNULL)
			{
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (z->right == _TNULL)
			{
				x = z->left;
				rbTransplant(z, z->left);
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
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			delete z;
			if (y_original_color == BLACK)
			{
				deleteFix(x);
			}
		}

		// For balancing the tree after insertion
		void insertFix(node_pointer k)
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
							rightRotate(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
				{
					break;
				}
			}
			_root->color = BLACK;
		}

		void printHelper(node_pointer _root, std::string indent, bool last)
		{
			if (_root != _TNULL)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = _root->color ? "RED" : "BLACK";
				std::cout << _root->data << "(" << sColor << ")" << std::endl;
				printHelper(_root->left, indent, false);
				printHelper(_root->right, indent, true);
			}
		}

	public:
		rbtree()
		{
			_TNULL = new node_type;
			_TNULL->color = BLACK;
			_TNULL->left = NULL;
			_TNULL->right = NULL;
			_root = _TNULL;
		}

		void preorder()
		{
			preOrderHelper(this->_root);
		}

		void inorder()
		{
			inOrderHelper(this->_root);
		}

		void postorder()
		{
			postOrderHelper(this->_root);
		}

		node_pointer searchTree(int k)
		{
			return searchTreeHelper(this->_root, k);
		}

		node_pointer minimum(node_pointer node)
		{
			while (node->left != _TNULL)
			{
				node = node->left;
			}
			return node;
		}

		node_pointer maximum(node_pointer node)
		{
			while (node->right != _TNULL)
			{
				node = node->right;
			}
			return node;
		}

		node_pointer successor(node_pointer x)
		{
			if (x->right != _TNULL)
			{
				return minimum(x->right);
			}

			node_pointer y = x->parent;
			while (y != _TNULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		node_pointer predecessor(node_pointer x)
		{
			if (x->left != _TNULL)
			{
				return maximum(x->left);
			}

			node_pointer y = x->parent;
			while (y != _TNULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}

			return y;
		}

		void leftRotate(node_pointer x)
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
				this->_root = y;
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

		void rightRotate(node_pointer x)
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
				this->_root = y;
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

		// Inserting a node
		void insert(value_type data)
		{
			node_pointer node = getNode(data);
			node_pointer y = NULL;
			node_pointer x = this->_root;

			while (x != _TNULL)
			{
				y = x;
				if (node->data < x->data)
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
				_root = node;
			}
			else if (node->data < y->data)
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

			insertFix(node);
		}

		node_pointer get_root()
		{
			return this->_root;
		}

		void deleteNode(int data)
		{
			deleteNodeHelper(this->_root, data);
		}

		void printTree()
		{
			if (_root)
			{
				printHelper(this->_root, "", true);
			}
		}
	};

} // namespace ft

#endif
