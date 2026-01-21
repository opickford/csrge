#ifndef mesh_instance_H
#define mesh_instance_H

#include "mesh_base.h"
#include "bounding_sphere.h"

#include "maths/vector3.h"
#include "maths/vector4.h"

#include "common/status.h"

#include <chds/vec.h>

#include <stdint.h>


/*


TODO: Comments about how this is a component now.



*/



// TODO: Do we need this.
typedef int MeshInstanceId; 

typedef struct mesh_instance
{
	MeshBaseId mb_id; // TODO: Rename as base?
	int texture_id;

    // TODO: How do we ensure that this is set????
	uint8_t has_scale_changed; // Determines if the bounding sphere needs updating.

	// Per instance data
	// TODO: Do we actually want per vertex albedos? I reckon per face at least
	//		 makes more sense.
    // TODO: Float or V3???
	CHDS_VEC(V3) vertex_alebdos;

    // TODO: A scene could have a base ambient light, but mesh instances should also be able to!
    //       This will let them glow. This could potentially be per vertex but probably not worth.

	// Offsets into FrameData, these exist here as they are tied
	// to the MeshInstance itself.

    // TODO: When refactored to component would we have these? probs fine.
	int view_space_positions_offset;
	int view_space_normals_offset;

	int num_front_faces;

    BoundingSphere view_space_bounding_sphere; // Broad phase frustum culling.

} MeshInstance;

// MeshInstance API
Status mesh_instance_init(MeshInstance* mi, const MeshBase* mb);
void mesh_instance_destroy(MeshInstance* mi);

Status mesh_instance_set_base(MeshInstance* mi, const MeshBase* mb);
void mesh_instance_set_albedo(MeshInstance* mi, const MeshBase* mb, V3 albedo);

#endif