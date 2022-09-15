#include <iostream>
#include <vector>
#include "../../containers/vector.hpp"

int main()
{
    std::vector<int> v;
    std::vector<int> v2;

    v.resize(10, 2);
    v2.resize(5, 1);
    std::cout << &v << std::endl;
    std::cout << v.size() << " " << v.capacity() << std::endl;
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    v.swap(v2);
    std::cout << &v << std::endl;
    std::cout << v.size() << " " << v.capacity() << std::endl;
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;

}
