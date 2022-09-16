#include <map>
#include <iostream>
#include <iterator>

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main()
{
	std::map<char, int> m;
	std::map<char, int>::iterator it;

	m['a'] = 10;
	m['b'] = 30;
	m['c'] = 50;
	m['d'] = 70;
	std::cout << std::endl
			  << "#====== constructor =====#" << std::endl;
	std::map<char, int> m2(m.begin(), m.end());
	std::map<char, int> m3(m2);
	std::map<char, int, classcomp> m4;

	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	// system("leaks std-map");
}
