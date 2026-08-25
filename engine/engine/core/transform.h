#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "maths/vector3.h"

// TODO: Should this just go into components?

typedef struct Transform
{
    V3 position;
    V3 scale;
    V3 rotation;

    // Store previous state for lerp between state updated by physics.
    V3 previous_position;
    V3 previous_rotation;
    //V3 previous_scale;

} Transform;


inline void transform_init(Transform* t)
{
    t->position = (V3){ 0.f, 0.f, 0.f };
    t->scale = (V3){ 1.f, 1.f, 1.f };
    t->rotation = (V3){ 0.f, 0.f, 0.f };

    t->previous_position = t->position;
    t->previous_rotation = t->rotation;
    
    /*

TODO: Do we want to lerp scale????

      The issue is that if we do not set the previous_scale to equal scale,
      and we lerp scale (maybe from 1,1,1 to 10,10,10 for example),
      then we do not calculate a new bounding sphere as scale_has_changed
      hasn't been updated, this can cause clipping issues which causes
      out of buffer writes!!!!!!

      To fix this we could just not lerp scale as it doesn't seem necessary.


*/
    //t->previous_scale = t->scale;
}



#endif