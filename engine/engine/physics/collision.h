#ifndef COLLISION_H
#define COLLISION_H

#include "physics_frame.h"

#include "maths/bounding_sphere.h"


#include <cecs/ecs.h>

#include <chds/vec.h>


typedef struct V3 V3;
typedef struct MeshBase MeshBase;
typedef struct Physics Physics;
typedef struct Scene Scene;

typedef enum
{
    COLLISION_SHAPE_ELLIPSOID,
    COLLISION_SHAPE_MESH
} CollisionShapeType;

typedef struct
{
    const MeshBase* mb;
    CHDS_Vec(V3) wsps;
} CollisionMesh;

typedef struct
{
    // Tagged union for the type narrow phase shape.
    CollisionShapeType type;
    union
    {
        CollisionMesh mesh;
        V3 ellipsoid;
        float radius;
    };

    // TODO: How do we ensure that these are set???? Just down to user???
    uint8_t dirty; // Recalculate world space positions
    uint8_t scale_dirty; // Recalculate bounding sphere radius

    // Broad phase shape.
    BoundingSphere bs;

} CollisionShape;

typedef struct
{
    CECS* ecs;

    CECS_EntityId self;
    CECS_EntityId other;

    // Only really makes sense to use this in the stay event, e.g. 
    // for damage over time. Also could be useful down the line.
    // TODO: the callback could add a component for managing effects over time
    //       instead. 
    float dt;

    // TODO: for now there is no point including the normal/depth as we're 
    // talking about a collision between two entities here. We resolve
    // potentially multiple different collisions between colliders but
    // we're losing the number of contacts here.

} CollisionEvent;

// TODO: include normal?
// TODO: do we need dt here? for stay?
typedef void (*CollisionCallback)(
    const CollisionEvent* event
);

// TODO: Collider stuff could be separated into a new file but not necessary for now.
// TODO: In the future this could contain some callback etc.
typedef struct Collider
{
    CollisionShape shape;

    // Ratio of relative velocity of separation to relative velocity of approach.
    // Determines collisions elasticity (how much energy loss)
    // 0 = completely inelastic, 1 = perfectly elastic (no energy loss)
    float restiution_coeff;

    // Ratio of frictional force to normal force pushing objects together.
    // 0 = no friction, 1 is as much friction as the normal force.
    float friction_coeff;

    // TODO: this potentially could be refactored into a separate 
    //       ColliderCallbacks component.
    CollisionCallback on_collision_enter;
    CollisionCallback on_collision_stay;
    CollisionCallback on_collision_exit;

} Collider;

void collider_init(Collider* c);
void collider_destroy(Collider* c);

void reset_contacts(Physics* physics);
uint8_t handle_collisions(Physics* physics, Scene* scene);
void dispatch_contacts(Physics* physics, Scene* scene, float dt);

#endif