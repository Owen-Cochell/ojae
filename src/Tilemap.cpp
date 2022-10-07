#include "Tilemap.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ColliderComponent.h"


Tilemap::Tilemap() 
{
    entity_handler = nullptr;
    width = 0;
    height = 0;
}

Tilemap::Tilemap(int _width, int _height)
{
    entity_handler = new EntityHandler(_width, _height);
    width = _width; 
    height = _height;

    // Tilemap is too small, no entity can be present without exceeding the 
    // tilemap's bounds
    if(width < 3 || height < 3)
    {
        Debug::log("[FAIL] Tilemap.Constructor() -> Tilemap too small");
        exit(0);
    }

    // Add non traversable entities along the edges of the tilemap so no
    // entity can move out of bounds
    Entity* edge_map_collider = new Entity("EDGE MAP COLLIDER");
    edge_map_collider->add_component<ColliderComponent>();
    edge_map_collider->add_component<SpriteComponent>('C', "Red", 11);
    edge_map_collider->add_tag("NON_TRAVERSABLE");

    for(int x = 0; x < width; x++)
    {
        add_entity(edge_map_collider, x, 0);
        add_entity(edge_map_collider, x, height - 1);
    }

    for(int y = 0; y < height; y++)
    {
        add_entity(edge_map_collider, 0, y);
        add_entity(edge_map_collider, width - 1, y);
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

    // std::map<std::pair<int, int>, std::vector<Entity*>> entity_positions = 
    //     entity_handler->get_entity_positions();

    for(int y = 0; y <  15; y++)
    {
        for(int x = 0; x < 15; x++)
        {

            std::vector<Entity*> targ_positions = 
                entity_handler->get_entities_at_position(x, y);

            if(targ_positions.size() == 0)
            {

                NO_SPRITE_PRESENT:

                display.push_back(new Character('%', "White", 0, 0));
                continue;
            }

            SpriteComponent* highest_sprite_component = nullptr;

            for(Entity* e : targ_positions)
            {

                if(e->has_component<SpriteComponent>())
                {
                    SpriteComponent* sprite_component = 
                        e->get_component<SpriteComponent>();

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
    if(!e->has_component<TransformComponent>())
    {
        e->add_component<TransformComponent>(x, y);
    }

    e->get_component<TransformComponent>()->set_position(x, y);;
    entity_handler->add_entity(e, x, y);
}

void Tilemap::add_copy_entity(const Entity& e, int x, int y)
{
    Entity* new_e = new Entity(e);
    add_entity(new_e, x, y);
}

void Tilemap::remove_entity(Entity* e)
{
    if(!e->has_component<TransformComponent>())
    {
        Debug::log("[FAIL] Tilemap.remove_entity -> Entity does not have"
            "required Transform Component");
        exit(0);
    }

    TransformComponent* transform_component =
         e->get_component<TransformComponent>();

    if(!entity_handler->remove_entity(e, transform_component->x_pos, 
        transform_component->y_pos))
    {
        Debug::log("[FAIL] Tilemap.remove_entity -> Could not remove" 
            "entity");
        exit(0);
    }
}

void Tilemap::fill_tilemap(Entity* e)
{

    int x = 0;
    int y = 0;

    // Add the first entity to the first position
    add_entity(e, x, y);
    x++;

    while(y < height)
    {
        while(x < width)
        {
            add_copy_entity(*e, x, y);
            x++;
        }

        x = 0;
        y++;
    }
}
