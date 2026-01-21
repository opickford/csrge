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
	CHDS_VEC(V3) view_space_positions;
    CHDS_VEC(V3) view_space_normals;

    CHDS_VEC(V3) point_lights_view_space_positions;

	// Broad Phase Frustum Culling
    CHDS_VEC(MeshInstance) visible_mis;
	int num_visible_mis;
	CHDS_VEC(uint8_t) intersected_planes;

	// Backface Culling Output
	CHDS_VEC(int) front_face_indices;

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
	
    CHDS_VEC(V3) vertex_lighting;

	// Clipping
    CHDS_VEC(float) faces_to_clip;  // Input to clip.
	CHDS_VEC(float) clipped_faces;  // Clipping output.
	int num_clipped_faces; // Number of faces in the output buffer.

    // Intermediate buffers for clipping, alternate between per plane.
    CHDS_VEC(float) temp_clipped_faces0; 
    CHDS_VEC(float) temp_clipped_faces1;

} FrameData;

Status frame_data_init(
    cecs* ecs, 
    cecs_view_id render_view, 
    cecs_view_id lighting_view, 
    FrameData* frame_data, 
    Scene* scene);


void frame_data_destroy(FrameData* frame_data);


#endif