#pragma once

// https://www.youtube.com/watch?v=3Dw5d7PlcTM

#include <vector>

template<typename T>
struct HeapItem
{
    T* targ_item;
    int heap_index;

    HeapItem(T& item)
    {
        targ_item = &item;
    }
};

template<typename T>
class Heap
{

private:

    std::vector<HeapItem<T>*> items;
    int current_item_count;

    int compare(int first_num, int second_num)
    {

    }

    void sort_up(HeapItem<T>& item)
    {
        int parent_index = (item.heap_index - 1) / 2;

        while(true)
        {
            HeapItem<T>* parent_item = items[parent_index];
            
            while(true)
            {
                if(item.compare(parent_item) > 0)
                {
                    swap(item, *parent_item);
                }

                else
                {
                    break;
                }
            }
        }
    }

    void sort_down(HeapItem<T>& item)
    {
        while(true)
        {
            int child_index_left = (item.heap_index * 2) + 1;
            int child_index_right = (item.heap_index * 2) - 1;
            int swap_index = 0;

            if(child_index_left < current_item_count)
            {
                swap_index = child_index_left;

                if(child_index_right < current_item_count)
                {
                    if(items.at(compare(items.at(child_index_left)->heap_index,
                        items.at(child_index_right)->heap_index
                    ) < 0))
                    {
                        swap_index = child_index_right;
                    }
                }

                if(compare(item.heap_index, 
                    items.at(swap_index)->heap_index7) < 0)
                {
                    swap(item, items.at(swap_index));
                }
                
                else
                {
                    break;
                }
            }

            else
            {
                return;
            }
        }
    }

    void swap(HeapItem<T>& first_item, HeapItem<T>& second_item)
    {
        items.at(first_item.heap_index) = &second_item;
        items.at(second_item.heap_index) = &first_item;

        int first_item_index = first_item.heap_index;
        first_item.heap_index = second_item.heap_index;
        second_item.heap_index = first_item_index;
    }

    T* remove_first()
    {
        T* first_item = items.at(0);
        current_item_count--;

        items.at(0) = items.at(current_item_count);
        items.at(0)->heap_index = 0;
        sort_down(*items.at(0));
        return first_item;
    }

public:

    ~Heap()
    {
        for(int i = 0; i < items.size(); i++)
        {
            delete items .at(i);
        }
        delete items;
    }

    void add(T& item)
    {
        HeapItem<T>* new_item = new HeapItem<T>;

        new_item->heap_index = current_item_count;
        items.at(current_item_count) = new_item;
        sort_up(*new_item);
        current_item_count++;
    }

    update_item(T& item)
    {
        for(int i = 0; i < current_item_count; i++)
        {
            if(item == *items.at(i)->targ_item)
            {
                sort_up(*items.at(i)->targ_item);
            }
        }
    }

    bool contains(T& item)
    {
        if(item.heap_index < current_item_count && 
            item == *items.at(item.heap_index)->targ_item)
        {
            return true;
        }

        return false;
    }

    int count() { return current_item_count; }

};

