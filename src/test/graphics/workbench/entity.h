#pragma once

struct Entity
{
    // tells if the entity just started a collision in the last frame
    bool just_collided = false;

    // tells if the entity collides in the last frame
    bool colliding = false;
};

