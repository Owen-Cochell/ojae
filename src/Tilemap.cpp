#include <iostream>

#include "Tilemap.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

Tilemap::Tilemap() 
{
    debugger = nullptr;
    entity_handler = nullptr;
    width = 0;
    height = 0;
}

Tilemap::Tilemap(Debugger* _debugger, int _width, int _height)
{
    entity_handler = new EntityHandler;
    debugger = _debugger;
    width = _width;
    height = _height;

    // Tilemap is too small, no entity can be present without exceeding the 
    // tilemap's bounds
    if(width < 1 || height < 1)
    {
        debugger->log("[FAIL] Tilemap.Constructor() -> Tilemap too small");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    // Add non traversable entities along the edges of the tilemap so no
    // entity can move out of bounds
    Entity* edge_map_collider = new Entity("EDGE MAP COLLIDER");
    edge_map_collider->add_tag("NON_TRAVERSABLE");

    for(int x = 0; x < width; x++)
    {
        add_entity(edge_map_collider, x, -1);
        add_entity(edge_map_collider, x, height);
    }

    for(int y = 0; y < height; y++)
    {
        add_entity(edge_map_collider, -1, y);
        add_entity(edge_map_collider, width, y);
    }
}

Tilemap::~Tilemap()
{
    delete entity_handler;
}

std::vector<Character*> Tilemap::get_display()
{

    // Delete character objects so we don't have memory leaks
    for(Character* c : display)
    {
        delete c;
    }

    display.clear();

    std::map<std::pair<int, int>, std::vector<Entity*>> entity_positions = 
        entity_handler->get_entity_positions();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {

            if(entity_positions.count({x, y}) == 0)
            {

                NO_SPRITE_PRESENT:

                display.push_back(new Character('%', "White", 0, 0));
                continue;
            }

            SpriteComponent* highest_sprite_component = nullptr;

            for(Entity* e : entity_positions[{x, y}])
            {
                if(e->hasComponent<SpriteComponent>())
                {
                    SpriteComponent* sprite_component = 
                        e->getComponent<SpriteComponent>();

                    // If there is no highest sprite component 
                    if(highest_sprite_component == nullptr)
                    {
                        highest_sprite_component = sprite_component;
                        continue;
                    }

                    if(sprite_component->priority > 
                        highest_sprite_component->priority)
                    {
                        highest_sprite_component = sprite_component;
                    }
                }
            }

            if(highest_sprite_component == nullptr)
            {
                goto NO_SPRITE_PRESENT;
            }

            display.push_back(
                    new Character(highest_sprite_component->symbol,
                    highest_sprite_component->color, 0, 0));
        }

        display.push_back(new Character('\n', "White", 0, 0));
    }

    return display;
}

void Tilemap::update()
{
    entity_handler->update();
}

void Tilemap::add_entity(Entity* e, int x, int y) 
{ 

    if(!e->hasComponent<TransformComponent>())
    {
        e->addComponent<TransformComponent>(x, y);
    }

    e->getComponent<TransformComponent>()->set_position(x, y);

    entity_handler->add_entity(e, x, y);
}

void Tilemap::remove_entity(Entity* e)
{
    if(!e->hasComponent<TransformComponent>())
    {
        debugger->log("[FAIL] Tilemap.remove_entity -> Entity does not have"
            "required Transform Component");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    TransformComponent* transform_component =
         e->getComponent<TransformComponent>();

    if(!entity_handler->remove_entity(e, transform_component->x_pos, 
        transform_component->y_pos))
    {
        debugger->log("[FAIL] Tilemap.remove_entity -> Could not remove" 
            "entity");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }
}

