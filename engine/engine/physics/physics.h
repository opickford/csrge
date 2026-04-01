#ifndef PHYSICS_H
#define PHYSICS_H

#include "physics_frame.h"

#include "core/scene.h"

#include "maths/vector3.h"
#include "maths/bounding_sphere.h"
#include "maths/plane.h"

#include "common/status.h"

#include <cecs/ecs.h>

#include <chds/vec.h>

#include <stdint.h>

typedef struct physics
{
    // TODO: Should this contain a scene also?

    CECS* ecs;

    PhysicsFrame frame;

    // Views
    CECS_ViewId physics_view; // TODO: Rename physicsdata view?
    CECS_ViewId moving_colliders_view;
    CECS_ViewId static_colliders_view;
    CECS_ViewId colliders_view;

    uint8_t max_collision_iters;

} Physics;

// TODO: Move to separate file?
typedef struct physics_data
{
    V3 impulses; // Forces applied instantaneously.
    V3 velocity;

    float mass;

    // TODO: TEMP
    uint8_t floating;
} PhysicsData;

void physics_data_init(PhysicsData* data);

Status physics_init(Physics* physics, CECS* ecs);

void physics_tick(Physics* physics, Scene* scene, float dt);


#endif