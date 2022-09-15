/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 01:55:04 by jihoh             #+#    #+#             */
/*   Updated: 2022/09/15 18:54:19 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include <cstddef>	 // std::ptrdiff_t
#include <memory>	 // std::allocator
#include <stdexcept> // std::out_of_range

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef ft::vector_iterator<value_type> iterator;
		typedef ft::vector_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		// constructor
		explicit vector(const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _capacity(0), _size(0), _data(NULL)
		{
		} // default

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _allocator(alloc), _capacity(n), _size(n)
		{
			_data = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.construct(_data + i, val);
			}
		} // fill

		template <class InputIterator>
		vector(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last,
			const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
		{
			_capacity = 0;
			for (InputIterator it = first; it != last; it++)
			{
				_capacity++;
			}
			_data = _allocator.allocate(_capacity);
			for (_size = 0; _size < _capacity; _size++)
			{
				_allocator.construct(_data + _size, *first++);
			}
		} // range

		vector(const vector &x)
			: _allocator(x._allocator), _capacity(x._capacity), _size(x._size)
		{
			_data = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.construct(_data + i, x[i]);
			}
		} // copy

		// destructor
		~vector()
		{
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.destroy(_data + i);
			}
			_allocator.deallocate(_data, _capacity);
		}

		// operator=
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.deallocate(_data, _capacity);
				_capacity = x._capacity;
				_data = _allocator.allocate(_capacity);
				for (_size = 0; _size < x._size; _size++)
				{
					_allocator.construct(_data + _size, x[_size]);
				}
			}
			return (*this);
		}

		// Iterators
		iterator begin()
		{
			return (iterator(_data));
		}

		const_iterator begin() const
		{
			return (const_iterator(_data));
		}

		iterator end()
		{
			return (iterator(_data + _size));
		}

		const_iterator end() const
		{
			return (const_iterator(_data + _size));
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
		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return ((_allocator.max_size() < PTRDIFF_MAX) ? _allocator.max_size() : PTRDIFF_MAX);
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n <= _size)
			{
				for (size_type i = _size - n; i < _size; i++)
				{
					_allocator.destroy(_data + i);
				}
			}
			else
			{
				this->reserve(n);
				for (size_type i = _size; i < n; i++)
				{
					_allocator.construct(_data + i, val);
				}
			}
			_size = n;
		}

		size_type capacity() const
		{
			return (_capacity);
		}

		bool empty() const
		{
			return (_size == 0);
		}

		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				pointer tmp = _data;

				if (n < _capacity * 2)
					n = _capacity * 2;
				_data = _allocator.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(_data + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, _capacity);
				_capacity = n;
			}
		}

		// Element access
		reference operator[](size_type n)
		{
			return (_data[n]);
		}

		const_reference operator[](size_type n) const
		{
			return (_data[n]);
		}

		reference at(size_type n)
		{
			if (n < _size)
				return (_data[n]);
			throw std::out_of_range("vector");
		}

		const_reference at(size_type n) const
		{
			if (n < _size)
				return (_data[n]);
			throw std::out_of_range("vector");
		}

		reference front()
		{
			return (_data[0]);
		}

		const_reference front() const
		{
			return (_data[0]);
		}

		reference back()
		{
			return (_data[_size - 1]);
		}

		const_reference back() const
		{
			return (_data[_size - 1]);
		}

		// Modifiers
		template <class InputIterator>
		void assign(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			size_type n = 0;

			for (InputIterator it = first; it != last; it++)
			{
				n++;
			}
			this->reserve(n);
			for (size_type i = 0; i < n; i++)
			{
				if (i < _size)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.construct(_data + i, *first++);
			}
			_size = n;
		}

		void assign(size_type n, const value_type &val)
		{
			this->reserve(n);
			for (size_type i = 0; i < n; i++)
			{
				if (i < _size)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.construct(_data + i, val);
			}
			_size = n;
		}

		void push_back(const value_type &val)
		{
			if (_size + 1 > _capacity)
			{
				this->resize(_size + 1, val);
			}
			else
			{
				_allocator.construct(_data + _size, val);
				_size++;
			}
		}

		void pop_back()
		{
			_allocator.destroy(_data + _size);
			_size--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type i = position - this->begin();

			insert(position, 1, val);

			return (iterator(this->begin() + i));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type i = position - this->begin();

			if (_size + n > _capacity)
			{
				this->reserve(_size + n);
			}
			for (iterator it = this->end(); it != position; it--)
			{
				*(it - 1 + n) = *(it - 1);
			}
			for (size_type j = 0; j < n; j++)
			{
				_allocator.construct(_data + i + j, val);
			}
			_size += n;
		}

		template <class InputIterator>
		void insert(
			iterator position,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			size_type i = position - this->begin();
			size_type n = 0;

			for (InputIterator it = first; it != last; it++)
			{
				n++;
			}
			if (_size + n > _capacity)
			{
				this->reserve(_size + n);
			}
			for (iterator it = this->end(); it != position; it--)
			{
				*(it - 1 + n) = *(it - 1);
			}
			for (size_type j = 0; j < n; j++)
			{
				_allocator.construct(_data + i + j, *first++);
			}
			_size += n;
		}

		iterator erase(iterator position)
		{
			return (erase(position, position + 1));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type i = 0;

			for (iterator it = first; it != last; it++)
			{
				_allocator.destroy(&(*it));
			}
			for (iterator it = last + 1; it != this->end(); it++)
			{
				*(first + i) = *it;
				i++;
			}
			_size -= last - first;

			return (first);
		}

		void swap(vector &x)
		{
			vector<T> tmp;

			if (this != &x)
			{
				tmp = x;
				x = *this;
				*this = tmp;
			}
		}

	private:
		size_type _size;	 // current size
		size_type _capacity; // allocated size
		allocator_type _allocator;
		pointer _data;
	};
} // namespace ft

#endif
