#pragma once

#include <vector>
#include <map>
#include <algorithm>

template<typename T>
/**
 * @brief A vector and a map combined to quickly find elements within
 * the vector, while also storing the elements in contiguous memory
 * 
 * @tparam T Type of Element
 */
class SmartVector
{

private:

    std::vector<T> items;

    std::map<T, std::vector<int>> item_indexes;

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

    typename std::vector<T>::iterator begin() { return items.begin(); }

    int find(const T& item)
    {

        if(item_indexes.count(item) == 0)
        {
            return -1;
        }

        return item_indexes[item].at(0);
    }

    int size() { return items.size(); }

    void push_back(const T& item)
    {   
        // Add the vector index to the item indexes map
        item_indexes[item].push_back(items.size() - 1);
        
        // Sort the item indexes for this item,
        std::sort(item_indexes[item].begin(), item_indexes[item].begin());

        // Add the item to the vector
        items.push_back(item);
    }

    bool erase(const T& item)
    {
        // If the item doesn't exist in the item indexes map
        if(item_indexes.count(item) == -1)
        {
            return false;
        }

        bool successfuly_erased = erase_at(item_indexes[item].first);        
    }

    bool erase_at(int index)
    {
        // If the index is out of range
        if(index < 0 || index >= items.size())
        {
            return false;
        }

        // The target item
        T targ_item = items.at(index);

        // Erase the item from the vector at the position
        items.erase(items.begin() + index);

        // Iterate through the indexes inside the item indexes at the target 
        // item 
        for(int i = 0; i < item_indexes[targ_item].size(); i++)
        {
            // If the current index matches the index to erase
            if(item_indexes[targ_item].at(i) == index)
            {
                item_indexes[targ_item].erase(item_indexes[targ_item].begin() + i);
            }
        }

        // If there are no more indexes of this item
        if(item_indexes[targ_item].size() == 0)
        {
            item_indexes.erase(targ_item);
        }

        // Iterate through 
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
