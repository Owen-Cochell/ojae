#pragma once

#include <vector>
#include <map>
#include <iostream>

/**
 * @brief A vector and a map combined to quickly find elements within
 * the vector, while also storing the elements in contiguous memory
 * 
 * @tparam T Type of Element
 */
template<typename T>
class SmartVector
{

private:

    std::vector<T> items;

    std::map<T, int> item_indexes;

public:
    
    SmartVector() {}
    
    T& at(int index)
    {
        return items.at(index);
    }

    T& pop_back()
    {
        T targ_item = items.at(items.size() - 1);

        item_indexes.erase(targ_item);
        items.erase(items.begin() + items.size() - 1);
        return targ_item;
    }

    int find(const T& item)
    {
        if(item_indexes.count(item) == 0)
        {
            return -1;
        }

        return item_indexes[item];
    }

    int size() { return items.size(); }

    void push_back(const T& item)
    {
        items.push_back(item);
        item_indexes[item] = items.size() - 1;
    }

    bool erase(const T& item)
    {
        if(item_indexes.count(item) == -1)
        {
            return false;
        }

        return erase_at(item_indexes[item]);
    }

    bool erase_at(int index)
    {
        if(index < 0 || index >= items.size())
        {
            return false;
        }

        T targ_item = items.at(index);

        items.erase(items.begin() + index);
        item_indexes.erase(targ_item);

        for(int i = index; i < items.size(); i++)
        {
            item_indexes[items.at(i)]--;
        }

        return true;
    }

    void clear()
    {
        items.clear();
        item_indexes.clear();
    }

};
