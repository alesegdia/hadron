#pragma once

#include <hadron/hadron.h>
#include <alligator/alligator.h>

#include <allegro5/allegro_primitives.h>

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
        al_draw_rectangle(
                    r.x, r.y,
                    r.x + r.width,
                    r.y + r.height,
                    al_map_rgb(255, 0, 0), 4.0f);
    }
};
