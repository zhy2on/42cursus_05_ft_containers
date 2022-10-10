/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 05:05:37 by jihoh             #+#    #+#             */
/*   Updated: 2022/10/10 16:20:30 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <cstddef>	 // std::size_t

namespace ft
{
	template<typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		// Member types
		typedef T value_type;
		typedef Container container_type;
		typedef typename std::size_t size_type;

		// Member functions
		explicit stack(const container_type &ctnr = container_type())
			: _cont(ctnr)
		{
		}

		bool empty() const
		{
			return _cont.empty();
		}

		size_type size() const
		{
			return _cont.size();
		}

		value_type& top()
		{
			return _cont.back();
		}
		
		const value_type& top() const
		{
			return _cont.back();
		}

		void push(const value_type &val)
		{
			_cont.push_back(val);
		}

		void pop()
		{
			_cont.pop_back();
		}

		template <typename T1, typename C1>
		friend bool operator==(const stack<T1, C1> &x, const stack<T1, C1> &y);
		template <typename T1, typename C1>
		friend bool operator<(const stack<T1, C1> &x, const stack<T1, C1> &y);

	protected:
		container_type _cont;
	};

	// Non-member function overloads
	template <typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._cont == rhs._cont);
	}

	template <typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}

	template <typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
