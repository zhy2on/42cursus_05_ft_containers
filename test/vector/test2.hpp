#include "test.hpp"

namespace ft {

	template <typename T>
	struct Child : public ft::Base<T, T>
	{
		typename ft::Base<T, T>::pointer a;

	private:
		typename ft::Base<T, T>::pointer b;
	};
}