#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "array.h"
#include "texture.h"

typedef struct AnimationCycle AnimationCycle;
struct AnimationCycle
{
    Array frames;
    float time_per_frame;
};

typedef struct AnimationManager AnimationManager;
struct AnimationManager
{
    Array queue;
    float time_elapsed;
    uint current_frame_id;
};

AnimationCycle animationcycle_create(float time_per_frame);
void animationcycle_add_frame(AnimationCycle*, Texture*);

AnimationManager animationmanager_create();
void animationmanager_update(AnimationManager*, float);
Texture* animationmanager_get_current_texture(AnimationManager*);
void animationmanager_enqueue(AnimationManager*, AnimationCycle*);

#endif

