#pragma once

#ifndef PHYSICS_FRAME_H
#define PHYSICS_FRAME_H

#include <maths/vector3.h>

#include <cecs/archetype.h>

#include <chds/vec.h>


#include <string.h>

typedef struct collider Collider;
typedef struct physics_data PhysicsData;
typedef struct mesh_instance MeshInstance;
typedef struct transform Transform;

// TODO: Should this just store the necessary for each entity, i think so? Would make it easier to unpack right and less computations....
// TODO: An issue with pointers would be if a collision called a 
//       callback that created a new entity which could invalidate 
//       the pointers maybe? But not an issue for now. I believe 
//       we would want to wait for all collisions to be resolved
//       before firing callbacks anyways.

// TODO: Should this be elsewhere?
typedef struct
{
    const MeshInstance* mi0;
    Collider* c0;
    PhysicsData* pd0;
    Transform* t0;

    const MeshInstance* mi1;
    Collider* c1;
    PhysicsData* pd1;
    Transform* t1;
    



    /*
    // Collider collides with a target.
    cecs_archetype_id collider_aid;
    int collider_offset;

    cecs_archetype_id target_aid;
    int target_offset;
    */

} PotentialCollision;

typedef struct
{
    V3 collision_normal;

    uint8_t hit;

    float penetration_depth;

    PotentialCollision pc; // TODO: TEMP: Just for the entity ptrs?

} CollisionData;

typedef struct
{
    CHDS_Vec(PotentialCollision) potential_collisions;
    CHDS_Vec(CollisionData) collisions;

} PhysicsFrame;

inline void physics_frame_init(PhysicsFrame* pf)
{
    memset(pf, 0, sizeof(PhysicsFrame));
}

inline void physics_frame_destroy(PhysicsFrame* pf)
{
    chds_vec_destroy(pf->potential_collisions);
    chds_vec_destroy(pf->collisions);
}

#endif