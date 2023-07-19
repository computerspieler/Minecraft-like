#include <assert.h>

#include "array.h"
#include "texture.h"
#include "animation.h"

AnimationCycle animationcycle_create(float time_per_frame)
{
    AnimationCycle output;

    output.time_per_frame = time_per_frame;
    output.frames = array_create(sizeof(Texture*));

    return output;
}

void animationcycle_add_frame(AnimationCycle* c, Texture* t)
{ array_push(&c->frames, &t); }

AnimationManager animationmanager_create()
{
    AnimationManager output;

    output.time_elapsed = 0;
    output.current_frame_id = 0;
    output.queue = array_create(sizeof(AnimationCycle));

    return output;
}

AnimationCycle* front(AnimationManager *m)
{
    assert(array_size(&m->queue) > 0);
    return (AnimationCycle*) m->queue.array;
}

void animationmanager_update(AnimationManager* m, float delta_time)
{
	m->time_elapsed += delta_time;

	while(m->time_elapsed >= front(m)->time_per_frame) {
		m->time_elapsed -= front(m)->time_per_frame;
		m->current_frame_id ++;
		if(m->current_frame_id >= array_size(&(front(m)->frames))) {
			if(array_size(&m->queue) > 1)
				array_first_pop(&m->queue, NULL);
			
			m->current_frame_id = 0;
		}
	}
}

Texture* animationmanager_get_current_texture(AnimationManager* m)
{ return ((Texture**)front(m)->frames.array)[m->current_frame_id]; }

void animationmanager_enqueue(AnimationManager* m, AnimationCycle* c)
{ array_push(&m->queue, c); }


