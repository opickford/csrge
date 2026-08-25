#pragma once

#ifndef PHYSICS_FRAME_H
#define PHYSICS_FRAME_H

#include <maths/vector3.h>

#include <cecs/entity.h>
#include <cecs/archetype.h>

#include <chds/vec.h>

#include <string.h>

typedef struct Collider Collider;
typedef struct PhysicsData PhysicsData;
typedef struct MeshInstance MeshInstance;
typedef struct Transform Transform;

// TODO: Should this just store the necessary for each entity, i think so? Would make it easier to unpack right and less computations....
// TODO: An issue with pointers would be if a collision called a 
//       callback that created a new entity which could invalidate 
//       the pointers maybe? But not an issue for now. I believe 
//       we would want to wait for all collisions to be resolved
//       before firing callbacks anyways. Also, this is purely internal,
//       so the pointers aren't an issue because we know the ecs won't be
//       mutated at this step.

// TODO: Should this be elsewhere?
typedef struct
{
    CECS_EntityId eid0;
    CECS_EntityId eid1;

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

    float penetration_depth;

    PotentialCollision pc; // TODO: TEMP: Just for the entity ptrs?

} CollisionData;

// TODO: it's a bit annoying having this in the physics_frame.h
//       as this is persistant over frames, physics_frame
//       implies otherwise, although i suppose we could use
//       it for that too.
typedef struct CollisionPair
{
    // TODO: for now we just store the entity id, this will most likely
    //       change in the future, for example, if we wanted to support 
    //       multiple colliders per entity, but that would require 
    //       changes to the ECS too.
    CECS_EntityId e0;
    CECS_EntityId e1;

} CollisionPair;

typedef struct
{
    CHDS_Vec(PotentialCollision) potential_collisions;
    CHDS_Vec(CollisionData) collisions;

    // TODO: extract these elsewhere. or have a PhysicsContext etc.
    CHDS_Vec(CollisionPair) current_contacts;
    CHDS_Vec(CollisionPair) previous_contacts;

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