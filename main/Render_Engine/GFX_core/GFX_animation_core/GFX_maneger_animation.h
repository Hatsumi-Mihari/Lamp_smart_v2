#ifndef GFX_MANEGER_ANIMATION_H
#define GFX_MANEGER_ANIMATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct List List;
typedef struct Render_Timer_Config Render_Timer_Config;


typedef struct GFX_state_animation
{
    const char* name;
    void (*callback_function)(void*, float*);
    void* arg_fuction;

    uint32_t duration_ms;
    uint32_t tick_interval_ms; 
    float progress;
    bool flag_loop_infinity;

    uint64_t elapsed_time;
    uint64_t time_start;
}GFX_state_animation;

void linery_color_fill(void* arg_fuction);
List* init_animation_queue();
void add_animation_pipeline(List *Queue_animation, GFX_state_animation animation);
void remove_animation_pipeline(List *Queue_animation, uint16_t animation_index);
void tick_update_animations(List* Queue_animation, bool *flag_clear_fbo);
#endif