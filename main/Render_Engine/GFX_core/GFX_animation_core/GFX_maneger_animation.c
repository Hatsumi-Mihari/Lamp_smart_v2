#include "GFX_maneger_animation.h"
#include "Render_Engine/lib/STL_Lib/List.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "Render_Engine/Render_State.h"
#include "esp_timer.h"
#include "Render_Engine/lib/RGB_prototype.h"

List *init_animation_queue()
{
    List *Queue_animation = (List *)heap_caps_malloc(sizeof(List), MALLOC_CAP_SPIRAM);
    list_init(Queue_animation, sizeof(GFX_state_animation), 0);
    return Queue_animation;
}

void add_animation_pipeline(List *Queue_animation, GFX_state_animation animation)
{
    
    list_push(Queue_animation, &animation);
}

void remove_animation_pipeline(List *Queue_animation, uint16_t animation_index)
{
    list_remove(Queue_animation, animation_index);
}

void tick_update_animations(List *Queue_animation, bool *flag_clear_fbo)
{
    GFX_state_animation *animation_t;
    bool obj_removed = false;
    for (int i = 0; i < Queue_animation->size; i++)
    {
        animation_t = (GFX_state_animation *)list_get(Queue_animation, i);

        if (animation_t->elapsed_time >= animation_t->duration_ms)
        {
            if (animation_t->flag_loop_infinity)
                animation_t->elapsed_time = 0;
            else
            {
                obj_removed = true;
                list_remove(Queue_animation, i);
                *flag_clear_fbo = obj_removed;
                i--;
                continue;
            }
        }

        if (animation_t->callback_function)
        {
            animation_t->progress = (float)animation_t->elapsed_time / animation_t->duration_ms;
            animation_t->callback_function(animation_t->arg_fuction, &animation_t->progress);
            obj_removed = false;
            *flag_clear_fbo = obj_removed;
        }

        animation_t->elapsed_time += animation_t->tick_interval;
    }
}