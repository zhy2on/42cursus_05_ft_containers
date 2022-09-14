#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;

    std::cout << v.capacity() << std::endl;
    v.resize(11);
    std::cout << v.capacity() << std::endl;
    v.resize(12);
    std::cout << v.capacity() << std::endl;
    v.resize(23);
    std::cout << v.capacity() << std::endl;
}
