#pragma once

#include <hadron/hadron.h>
#include <alligator/alligator.h>

#include <allegro5/allegro_primitives.h>

#include "entity.h"

class BodyDebugRenderer : public hadron::collision::IBodyVisitor
{
public:
    void visit(hadron::collision::Body::Ptr body)
    {
        const hadron::collision::AABB& r = body->aabb();
        /*
        al_draw_filled_rectangle(
                    r.x, r.y,
                    r.x + r.width,
                    r.y + r.height,
                    al_map_rgb(255, 0, 0));
        */
        auto e = static_cast<Entity*>(body->userData());

        ALLEGRO_COLOR c = e->colliding ? al_map_rgb(255,0,0) : al_map_rgb(0,0,255);
        if( e->queried > 0 )
        {
            c = al_map_rgb(0,255,0);
        }

        al_draw_rectangle(
                    r.x, r.y,
                    r.x + r.width,
                    r.y + r.height,
                    c, 4.0f);
    }
};
