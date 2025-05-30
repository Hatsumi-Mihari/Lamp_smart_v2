#ifndef GFX_MANEGER_ANIMATION_H
#define GFX_MANEGER_ANIMATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct List List;
typedef struct Render_Timer_Config Render_Timer_Config;


typedef struct GFX_state_animation
{
    const char* name;
    void (*callback_function)(void*);
    void* arg_fuction;

    uint16_t delay_qs;
    uint16_t tickrat_qs; 
    uint16_t passed_time_qs;
    bool flag_loop_infinity;
}GFX_state_animation;

void linery_color_fill(void* arg_fuction);
List* init_animation_queue();
void add_animation_pipeline(List *Queue_animation, GFX_state_animation animation);
void remove_animation_pipeline(List *Queue_animation, uint16_t animation_index);
void tick_update_animations(void *arg);
void run_animation_timer_loop(Render_Timer_Config *timer_config, List* Queue_animation);
#endif