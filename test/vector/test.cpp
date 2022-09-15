#include <iostream>
#include <vector>
#include "../../containers/vector.hpp"

int main()
{
    std::vector<int> v;

    v.resize(10, 2);
    v.erase(v.begin() + 20);
}
