#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
#include <unordered_map>

void simulate_map(int size_map)
{
    Uint64 sim_start = SDL_GetTicks64();

    int ordered_time = 0;
    int unordered_time = 0;

    std::map<int, int> ordered_map;
    std::unordered_map<int, int> unordered_map;

    for(int i = 0; i < size_map; i++)
    {
        ordered_map[i] = 1;
        unordered_map[i] = 1;
    }

    std::cout << "Adding to map: " << SDL_GetTicks64() << '\n';

    Uint64 start_time = SDL_GetTicks64();
    int sum = 0;

    for(std::map<int, int>::iterator it = ordered_map.begin(); 
        it != ordered_map.end(); it++)
    {
        sum += it->second;
    }

    ordered_time = SDL_GetTicks64() - start_time;

    sum = 0;

    start_time = SDL_GetTicks64();

    for(std::unordered_map<int, int>::iterator it = unordered_map.begin(); 
        it != unordered_map.end(); it++)
    {
        sum += it->second;
    }

    unordered_time = SDL_GetTicks64() - start_time;

    std::cout << "Ordered: " << ordered_time << '\n';
    std::cout << "Unordered: " << unordered_time << '\n';
}

void simulate_loop(unsigned long long num)
{

    Uint64 start_time = SDL_GetTicks64();

    unsigned long long sum = 0;

    std::map<int, int> map_thing;

    for(int i = 0; i < num; i++)
    {
        map_thing[i] = i;
    }

    std::cout << "For loop: " <<  num << "-> " << SDL_GetTicks64() - start_time << '\n';
}

int main()
{
    int num = 1000000;

    std::cout << (sizeof(int) * num) / (1000 * 1000);

    // simulate_map(10000000);
    //simulate_loop(100000);

    // int seconds = 3753;
    
    // int minutes = 3753 / 60;
    // seconds %= 60;

    // int hours = minutes / 60;
    // minutes %= 60;

    // std::cout << "Hours: " << hours << '\n';
    // std::cout << "Minutes: " << minutes << '\n';
    // std::cout << "Seconds: " << seconds << '\n';

    return 0;
}
