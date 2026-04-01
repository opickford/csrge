#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "transform.h"
#include "mesh_instance.h"
#include "lights.h"

#include "physics/collision.h"
#include "physics/physics.h"

#include <cecs/ecs.h>

#define CORE_COMPONENTS_LIST          \
    X(MESH_INSTANCE, MeshInstance) \
    X(POINT_LIGHT, PointLight)     \
    X(TRANSFORM, Transform)         \
    X(PHYSICS_DATA, PhysicsData)   \
    X(COLLIDER, Collider)

#define X(name, T) CECS_ComponentId COMPONENT_##name;
    CORE_COMPONENTS_LIST
#undef X

inline void core_components_init(CECS* ecs)
{
    // Register all core engine components.
#define X(name, T) \
    COMPONENT_##name = cecs_register_component(ecs, sizeof(T)); \
    printf("Registered Component: " #name " id: %d\n", COMPONENT_##name);

        CORE_COMPONENTS_LIST
#undef X
}


#endif