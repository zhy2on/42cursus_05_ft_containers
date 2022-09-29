#include "../../containers/map.hpp"
#include <iostream>
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};
int main()
{
	ft::map<char, int> m;

	m.insert(ft::make_pair('a', 1));
	m.insert(ft::make_pair('b', 1));
	m.insert(ft::make_pair('c', 1));


	// ft::map<char, foo<float> >::const_iterator cit;
	// ft::map<char, foo<float> >::const_iterator it;

	ft::map<char, int >::const_iterator cit;
	ft::map<char, int >::iterator it;

	ft::map<char, foo<float> > m2;
	ft::map<char, foo<float> >::const_iterator cit2;
	ft::map<char, foo<float> >::iterator it2;

	it2 = m2.begin();
	cit2 = it2;

	std::cout << cit2->first << std::endl;
	// std::cout << m.begin()->first << std::endl;
	// m.erase(m.begin());
	// std::cout << m.begin()->first << std::endl;
	// m.erase(m.begin());
	// std::cout << m.begin()->first << std::endl;
	// m.erase(m.begin());
	// std::cout << m.begin()->first << std::endl;
	// m.erase(m.begin());

	// ft::map<char, int>::iterator it;
	// ft::map<char, int>::const_iterator cit;

	// it = m.begin();
	// cit = it;

	// std::cout << cit->first << std::endl;
	// std::cout <<(it != cit) << std::endl;
	// std::cout <<(cit != it) << std::endl;

	return (0);
}
