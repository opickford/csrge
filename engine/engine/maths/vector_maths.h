#ifndef VECTOR_MATHS_H
#define VECTOR_MATHS_H

#include "vector3.h"
#include "vector4.h"

#include "utils/common.h"

// TODO: Per function comments.
// Avoid circular dependencies by having shared functions here.

inline V3 v4_xyz(V4 v)
{
	return (V3) { .x = v.x, v.y, v.z };
}

inline V4 v3_to_v4(V3 in, float w)
{
	return (V4) { in.x, in.y, in.z, w };
}

// Combine these to potentially minimise function calls.
inline V4 v3_read_to_v4(const float* in, float w)
{
	return (V4) { in[0], in[1], in[2], w };
}

inline uint8_t point_in_triangle(V3 p, V3 a, V3 b, V3 c)
{
    // FROM: https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/point_in_triangle.html

    // Translate ABC so P is at the origin, then check if world 
    // origin is contained in ABC.
    v3_sub_eq_v3(&a, p);
    v3_sub_eq_v3(&b, p);
    v3_sub_eq_v3(&c, p);

    // Calculate normals of triangles using two vertices and the 
    // origin (P).
    V3 u = cross(b, c); // PBC
    V3 v = cross(c, a); // PCA
    V3 w = cross(a, b); // PAB

    // If all normals face the same direction, then ABC contains P.
    if (dot(u, v) < 0.f) return 0;
    if (dot(u, w) < 0.f) return 0;

    return 1;
}

#endif