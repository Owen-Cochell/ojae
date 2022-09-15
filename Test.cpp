#include <map>
#include <iostream>

int main()
{
    std::map<std::pair<int,int>, int> test_map;

    test_map.emplace(std::pair<int,int>{1, 1}, 1);

    if(test_map.count(std::pair<int,int>{1, 1,}) != 0)
    {
        std::cout << "Key exists in map\n";
    }

    return 0;
}
