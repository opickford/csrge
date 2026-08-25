#ifndef SCENE_H
#define SCENE_H

#include "mesh_instance.h"
#include "lights.h"

#include "maths/vector3.h"

#include "common/status.h"

// TODO: This should more be storing metadata of the scene, the ecs contains lights and instances etc.
typedef struct Scene
{
	MeshBases mesh_bases; // TODO: Should these simply be global? 
                          // TODO: Make chds_vec

    // TODO: A scene could have a base ambient light, but mesh instances should also be able to!
    //       This will let them glow. This could potentially be per vertex but probably not worth.
	V3 ambient_light;
    int bg_colour;

} Scene;

// TODO: refactor to remove the 

Status scene_init(Scene* scene);
Status scene_destroy(Scene* scene);

// MeshBase API Wrappers
MeshBaseId scene_add_mesh_base(Scene* scene);

#endif