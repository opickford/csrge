#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <core/engine.h>

#include <cecs/ecs.h>

// TODO: Refactor this script to really make sense, e.g. we can pass in a camera offset.
uint8_t third_person = 1;

inline void player_controller_physics(Engine* engine, CECS_EntityId eid, float dt)
{
    if (engine->input_mode != INPUT_MODE_GAME) return;

    /*
    TODO: How can this be customisable?
    
    We really want this player controller to be provided by the engine.
    - Where/how can we provide it?

    Note, using this we see the choppy movement due to less physics updates,
    therefore, we need to lerp between positions for all entities.


    TODO:
    - Could accept an entity id.
    - Would this control the mouse as well?? 
    - This shouldn't be based off a camera direction right? more a player direction?
    
    */

    const static V3 up = { 0, 1.f, 0 };
    const V3 forward = v3_normalised((V3) { engine->renderer.camera.direction.x, 0.f, engine->renderer.camera.direction.z });
    const V3 right = v3_normalised(cross(forward, up));

    PhysicsData* pd = cecs_get_component(engine->ecs, eid, COMPONENT_PHYSICS_DATA);
    Transform* t = cecs_get_component(engine->ecs, eid, COMPONENT_TRANSFORM);

    // By multiplying by dt we're essentially converting the force into an impulse.
    const float speed = 20.f * dt * pd->mass;

    if (CSRGE_KEYDOWN(engine->window.keys['W']))
    {    
        v3_add_eq_v3(&pd->impulses, v3_mul_f(forward, speed));
    }
    if (CSRGE_KEYDOWN(engine->window.keys['S']))
    {
        v3_sub_eq_v3(&pd->impulses, v3_mul_f(forward, speed));
    }
    if (CSRGE_KEYDOWN(engine->window.keys['A']))
    {
        v3_sub_eq_v3(&pd->impulses, v3_mul_f(right, speed));
    }
    if (CSRGE_KEYDOWN(engine->window.keys['D']))
    {   
        v3_add_eq_v3(&pd->impulses, v3_mul_f(right, speed));
    }
    if (CSRGE_KEYDOWN(engine->window.keys[' ']))
    {
        // TODO: Only if colliding with something???
        const float jump_height = pd->mass;
        v3_add_eq_v3(&pd->impulses, v3_mul_f(up, jump_height));   
    }    
}

inline void player_controller_camera(Engine* engine, CECS_EntityId eid)
{
    if (engine->input_mode != INPUT_MODE_GAME) return;

    Transform* t = cecs_get_component(engine->ecs, eid, COMPONENT_TRANSFORM);

    const static V3 up = { 0, 1.f, 0 };
    const V3 forward = v3_normalised((V3) { engine->renderer.camera.direction.x, 0.f, engine->renderer.camera.direction.z });
    const V3 right = v3_normalised(cross(forward, up));

    V3 player_pos = v3_lerp(t->previous_position, t->position, engine->renderer.frame_data.physics_alpha);
    if (third_person)
    {
        const static float cam_dist = 4.f;
        const static float lateral_offset = 2.f;
        const static float vertical_offset = 2.f;

        V3 pos = v3_sub_v3(player_pos, v3_mul_f(engine->renderer.camera.direction, cam_dist));
        v3_add_eq_v3(&pos, v3_mul_f(right, lateral_offset));
        v3_add_eq_v3(&pos, v3_mul_f(up, vertical_offset));
        engine->renderer.camera.position = pos;
    }
    else
    {
        engine->renderer.camera.position = player_pos;
    }
}



#endif