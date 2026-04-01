#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "core/mesh_instance.h"
#include "core/scene.h"

#include "maths/bounding_sphere.h"

#include "common/status.h"

#include <cecs/ecs.h>

#include <chds/vec.h>

#include <stdint.h>

// Transient buffers used during the render pipeline per frame.

typedef struct
{
    float physics_alpha; // Time through the physics step, used for smooth interpolation.

	// Transform Stage
	CHDS_Vec(V3) view_space_positions;
    CHDS_Vec(V3) view_space_normals;

    CHDS_Vec(V3) point_lights_view_space_positions;

	// Broad Phase Frustum Culling
    CHDS_Vec(MeshInstance) visible_mis;
	int num_visible_mis;
	CHDS_Vec(uint8_t) intersected_planes;

	// Backface Culling Output
	CHDS_Vec(int) front_face_indices;

	// Lighting
	// TODO: Where should the vertex light output be written to?
	/*
	outputs:
	- total contribution from ambient and non shadow casting point lights - note,
	  this shouldnt be clamped because then we might subtract from it 
	- contribution (albedo * diffuse) from each shadow casting point light.
	 - then just subtract from the total?

	 just forget about shadows for now mayber.
	*/


    // TODO: Refactoring this so it's not just float arrays.
	
    CHDS_Vec(V3) vertex_lighting;

	// Clipping
    CHDS_Vec(float) faces_to_clip;  // Input to clip.
	CHDS_Vec(float) clipped_faces;  // Clipping output.
	int num_clipped_faces; // Number of faces in the output buffer.

    // Intermediate buffers for clipping, alternate between per plane.
    CHDS_Vec(float) temp_clipped_faces0; 
    CHDS_Vec(float) temp_clipped_faces1;

} FrameData;

Status frame_data_init(
    CECS* ecs, 
    CECS_ViewId render_view, 
    CECS_ViewId lighting_view, 
    FrameData* frame_data, 
    Scene* scene);


void frame_data_destroy(FrameData* frame_data);


#endif