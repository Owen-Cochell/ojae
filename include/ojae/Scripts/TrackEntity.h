#pragma once 

// https://www.youtube.com/watch?v=-L-WgKMFuhE&t=586s

#include <vector>
#include <unordered_set>
#include <map>
#include <SDL2/SDL.h>

#include "../ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/AIMovementComponent.h"
#include "../CollisionHandler.h"
#include "../Debug.h"

// https://www.techiedelight.com/use-pair-key-std-unordered_set-cpp/
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const
    {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
 
        return h1 ^ h2;
    }
};

struct TrackEntity : public Script
{

private:

    int start_x;
    int start_y;
    int targ_x;
    int targ_y;

    Uint64 update_start;

    bool path_blocked = false;

    std::pair<int,int> closest_position;

    std::map<std::pair<int,int>,std::pair<int,int>> parent_pos;

    std::vector<std::pair<int,int>> get_surrounding_positions(int _x, int _y)
    {
        std::vector<std::pair<int,int>> surrounding_positions;

        for(std::pair<int,int> element : 
            CollisionHandler::get_available_surrounding_positions
            (entity, _x, _y))
        {
            surrounding_positions.push_back({element.first, element.second});
        }

        return surrounding_positions;
    }

    int get_f_cost(int x, int y)
    {
        return get_g_cost(x, y) + get_h_cost(x, y);
    }

    int get_h_cost(int x, int y)
    {
        return get_distance(x, y, targ_x, targ_y);
    }

    int get_g_cost(int x, int y)
    {
        return get_distance(x, y, start_x, start_y);
    }

    int get_g_cost(std::pair<int,int> element)
    {
        return get_g_cost(element.first, element.second);
    }

    int get_distance(int first_x, int first_y, int second_x, int second_y)
    {
        int dist_x = abs(first_x - second_x);
        int dist_y = abs(first_y - second_y);

        if(dist_x > dist_y)
        {
            return (14 * dist_y) + (10 * (dist_x - dist_y));
        }

        return (14 * dist_x) + (10 * (dist_y - dist_x));
    }

    int get_distance(std::pair<int,int> first_element, std::pair<int,int> second_element)
    {
        return get_distance(first_element.first, first_element.second, second_element.first, 
            second_element.second);
    }

    void retrace_path()
    {
    
        std::pair<int,int> targ_pos {targ_x, targ_y};

        while(parent_pos.at(targ_pos) != std::pair<int,int>{start_x, start_y})
        {
            targ_pos = parent_pos.at(targ_pos);
        }

        AIMovementComponent* c = 
            entity->get_component<AIMovementComponent>();

        c->move(targ_pos.first, targ_pos.second);
        // std::cout << entity->name << " moving to target\n";
        // std::cout << "Took " << (SDL_GetTicks64() - update_start) << " miliseconds\n\n";
        c->reset_frames();
    }

public:

    Entity* targ_entity;

    TrackEntity(Entity* _targ_entity)
    {
        targ_entity = _targ_entity;
    }

    Script* clone() override
    {
        return new TrackEntity(targ_entity);
    }

    void set_positions()
    {
        // Tracked Entity's Transform Component
        TransformComponent* targ_t = 
            targ_entity->get_component<TransformComponent>();
        // This Script's Entity's TransformComponent
        TransformComponent* this_t = 
            entity->get_component<TransformComponent>();

        // Set starting and ending Nodes
        start_x = this_t->x_pos;
        start_y = this_t->y_pos;
        targ_x = targ_t->x_pos;
        targ_y = targ_t->y_pos;

        closest_position = std::pair<int,int>{start_x, start_y};
    }

    void update() override
    {

        AIMovementComponent* c = entity->get_component<AIMovementComponent>();

        // If this entity is not allowed to move yet, don't calculate a path
        if(!c->can_move()) return;

        // std::cout << entity->name << " can move\n";

        if(!path_blocked)
        {
            set_positions();

            // If this entity is already next to the player, there is no sense in 
            // moving
            if(get_distance(start_x, start_y, targ_x, targ_y) <= 14)
            {
                // std::cout << entity->name << " closest to target\n";
                // std::cout << "Took " << (SDL_GetTicks64() - update_start) << " miliseconds\n\n";
                c->reset_frames();
                return;
            }
        }

        else
        {
            path_blocked = false;

            // The entity is the closest they can get to the player while 
            // being blocked
            if(start_x == targ_x && start_y == targ_y)
            {
                // std::cout << entity->name << " closest to target while being blocked\n";
                // std::cout << "Took " << (SDL_GetTicks64() - update_start) << " miliseconds\n\n";
                c->reset_frames();
                return;
            }
        }

        parent_pos.clear();

        // Create open and closed position containers, and a map containing positions
        // to their 'parents', or where the positiosn were created frome

        std::vector<std::pair<int,int>> open_pos;
        std::unordered_set<std::pair<int,int>, pair_hash> closed_pos;

        // Add starting node
        open_pos.push_back({start_x, start_y});

        while(open_pos.size() > 0)
        {
            // Position we are currently looking at
            std::pair<int,int> current_pos = open_pos.at(0);

            // Iterate through all open positions and find the most efficient one
            for(int i = 1; i < open_pos.size(); i++)
            {
                if(get_f_cost(open_pos.at(i).first, open_pos.at(i).second) <=
                    get_f_cost(current_pos.first, current_pos.second))
                {
                    if(get_h_cost(open_pos.at(i).first, open_pos.at(i).second) <
                        get_h_cost(current_pos.first, current_pos.second))
                    {
                        current_pos = open_pos.at(i);
                    }
                }
            }

            // Search and remove the current position from open positions
            for(int i = 0; i < open_pos.size(); i++)
            {
                if(current_pos == open_pos.at(i))
                {
                    open_pos.erase(open_pos.begin() + i);
                    break;
                }
            }

            // Add the current Node to closed Nodes
            closed_pos.emplace(current_pos);

            // If we have found the target
            // if(current_pos == std::pair<int,int>{targ_x, targ_y})
            // {
            //     retrace_path();
            //     return;
            // }

            if(get_distance(current_pos, std::pair<int,int>{targ_x, targ_y}) <= 14)
            {
                parent_pos.emplace(std::pair<int,int>{targ_x, targ_y}, current_pos);
                retrace_path();
                return;
            }

            // Iterate through the neighbors of the current node
            for(std::pair<int,int> neighbor_pos : 
                get_surrounding_positions(current_pos.first, current_pos.second))
            {
                if(get_distance(neighbor_pos, std::pair<int,int>{targ_x, targ_y}) < 
                    get_distance(closest_position, std::pair<int,int>{targ_x, targ_y}))
                {
                    closest_position = neighbor_pos;
                }

                if(closed_pos.count(neighbor_pos) != 0) continue;

                int new_cost_to_neighbor = get_g_cost(current_pos) + 
                    get_distance(current_pos, neighbor_pos);
                
                if(new_cost_to_neighbor < get_g_cost(neighbor_pos) || 
                    closed_pos.count(neighbor_pos) == 0)
                {
                    parent_pos.emplace(neighbor_pos, current_pos);

                    for(std::pair<int,int> element : open_pos)
                    {
                        if(neighbor_pos == element) goto FOUND_PAIR;
                    }

                    open_pos.push_back(neighbor_pos);

                    FOUND_PAIR:
                    ;

                }
            }
        } 

        path_blocked = true;

        targ_x = closest_position.first;
        targ_y = closest_position.second;

        update();
    }  
};
