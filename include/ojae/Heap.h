#pragma once

// https://www.youtube.com/watch?v=3Dw5d7PlcTM

#include <vector>
#include <unordered_map>

// template<typename T>
// struct HeapItem
// {
//     T* item;
//     int weight;
//     int heap_index;

//     HeapItem(T* _item, int _weight)
//     {
//         item = _item;
//         weight = _weight;
//     }
// };

// template<typename T>
// class Heap
// {

// private:

//     std::vector<HeapItem*> items;
//     int current_item_count;

//     int compare(HeapItem* a, HeapItem* b)
//     {
//         if(a->weight == b->weight)
//         {
//             return 0;
//         }

//         if(a->weight > b->weight)
//         {
//             return 1;
//         }

//         return -1;
//     }

//     void swap(HeapItem* a, HeapItem* b)
//     {
//         items.at(a->heap_index) = b;
//         items.at(b->heap_index) = a;

//         int temp_a_index = a->heap_index;

//         a->heap_index = b->heap_index;
//         b->heap_index = temp_a_index;
//     }

//     void sort_up(HeapItem* heap_item)
//     {
//         int parent_index = (heap_item->heap_index - 1) / 2;

//         while(true)
//         {
//             HeapItem* parent_heap_item = items.at(parent_index);
//             if(compare(heap_item, parent_heap_item) > 0)
//             {
//                 swap(heap_item, parent_heap_item)
//                 continue;
//             }

//             else
//             {
//                 break;
//             }

//             parent_index = (heap_item->heap_index - 1) / 2;

//         }
//     }

//     void sort_down(HeapItem* heap_item)
//     {
//         while(true)
//         {
//             int child_index_left = heap_item->heap_index * 2 + 1;
//             int child_index_right = heap_item->heap_index * 2 + 2;
//             int swap_index = 0;

//             if(child_index_left < current_item_count)
//             {
//                 swap_index = child_index_left;

//                 if(child_index_right < current_item_count)
//                 {
//                     if(compare(items.at(child_index_left), 
//                         items.at(child_index_right)) < 0)
//                     {
//                         swap_index = child_index_right;
//                     }
//                 }

//                 if(compare(heap_item, items.at(swap_index)) < 0)
//                 {
//                     swap(heap_item, items.at(swap_index));
//                 }

//                 else
//                 {
//                     return;
//                 }
//             }

//             else 
//             {
//                 return;
//             }


//         }
//     }

//     T* remove_first()
//     {
//         HeapItem* first_item = items.at(0);
//         current_item_count--;
//         items.at(0) = items.at(current_item_count);
//         items.at(0)->heap_index = 0;
//         sort_down(items.at(0));
//         return first_item->item;
//     }

//     public int contains(T* item)
//     {
        
//     }

// public:

//     Heap() 
//     {
//         current_item_count = 0;
//     }

//     void add(T& item, int weight)
//     {
//         HeapItem* new_item = new HeapItem(&item, weight);
//         new_item->heap_index = current_item_count;
//         sort_up(new_item);
//         current_item_count++;
//     }

// };

template<typename T>
class Heap
{

private:

    std::vector<std::pair<T*, int>> items;
    std::unordered_map<std::pair<T*, int>, int> item_indexes;
    int current_item_count;

    int compare(HeapItem* a, HeapItem* b)
    {
        if(a->weight == b->weight)
        {
            return 0;
        }

        if(a->weight > b->weight)
        {
            return 1;
        }

        return -1;
    }

    void swap(HeapItem* a, HeapItem* b)
    {
        items.at(a->heap_index) = b;
        items.at(b->heap_index) = a;

        int temp_a_index = a->heap_index;

        a->heap_index = b->heap_index;
        b->heap_index = temp_a_index;
    }

    void sort_up(T* item)
    {
        int parent_index = (items[item] - 1) / 2;

        while(true)
        {
            HeapItem* parent_heap_item = items.at(parent_index);
            if(compare(heap_item, parent_heap_item) > 0)
            {
                swap(heap_item, parent_heap_item)
                continue;
            }

            else
            {
                break;
            }

            parent_index = (heap_item->heap_index - 1) / 2;

        }
    }

    void sort_down(HeapItem* heap_item)
    {
        while(true)
        {
            int child_index_left = heap_item->heap_index * 2 + 1;
            int child_index_right = heap_item->heap_index * 2 + 2;
            int swap_index = 0;

            if(child_index_left < current_item_count)
            {
                swap_index = child_index_left;

                if(child_index_right < current_item_count)
                {
                    if(compare(items.at(child_index_left), 
                        items.at(child_index_right)) < 0)
                    {
                        swap_index = child_index_right;
                    }
                }

                if(compare(heap_item, items.at(swap_index)) < 0)
                {
                    swap(heap_item, items.at(swap_index));
                }

                else
                {
                    return;
                }
            }

            else 
            {
                return;
            }


        }
    }

    T* remove_first()
    {
        HeapItem* first_item = items.at(0);
        current_item_count--;
        items.at(0) = items.at(current_item_count);
        items.at(0)->heap_index = 0;
        sort_down(items.at(0));
        return first_item->item;
    }

    public int contains(const T& item)
    {

    }

public:

    Heap() 
    {
        current_item_count = 0;
    }

    // Done
    void add(T& item, int weight)
    {
        
        // HeapItem* new_item = new HeapItem(&item, weight);
        std::pair<T*, int> item_pair = std::pair<T*, int>{&item, weight};

        items.push_back(item_pair);
        items[item_pair] = current_item_count;
        
        sort_up(&item);
        current_item_count++;
    }

};
