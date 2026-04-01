#ifndef COLLISION_H
#define COLLISION_H

#include "maths/bounding_sphere.h"

#include <chds/vec.h>

typedef struct v3 V3;
typedef struct mesh_base MeshBase;
typedef struct physics Physics;
typedef struct scene Scene;

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

// TODO: Collider stuff could be separated into a new file but not necessary for now.
// TODO: In the future this could contain some callback etc.
typedef struct collider
{
    CollisionShape shape;

    // Ratio of relative velocity of separation to relative velocity of approach.
    // Determines collisions elasticity (how much energy loss)
    // 0 = completely inelastic, 1 = perfectly elastic (no energy loss)
    float restiution_coeff;

    // Ratio of frictional force to normal force pushing objects together.
    // 0 = no friction, 1 is as much friction as the normal force.
    float friction_coeff;

} Collider;

void collider_init(Collider* c);
void collider_destroy(Collider* c);

uint8_t handle_collisions(Physics* physics, Scene* scene);

#endif