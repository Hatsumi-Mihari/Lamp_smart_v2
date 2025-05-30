#ifndef RENDER_STATE_H
#define RENDER_STATE_H
#include <stdbool.h>
#include <esp_timer.h>
typedef struct List List;
typedef struct Render_FBO_State Render_FBO_State;
typedef struct GFX_Utils_Config GFX_Utils_Config;

typedef struct Render_Timer_Config{
    esp_timer_create_args_t     loop_config;
    esp_timer_handle_t          loop_handle;
    esp_err_t                   timer_err;
    int64_t                     ms_loop_update;
}Render_Timer_Config;

typedef struct Render_State
{
    Render_FBO_State            *fbo_state;
    GFX_Utils_Config            *GFX_Utils_Config;
    List                        *List_GFX_PipeLine;
    List                        *Queue_GFT_Animation;

    uint64_t                    drawn_frames;
    bool                        flag_clear_fbo;
    
}Render_State;

List *Redner_Loop_init_debug_list_time();

void render_loop(Render_State *Render_State);
void redner_debug_loop_callback(void *arg);
void Render_init_debug_loop(Render_Timer_Config *Render_Timer_Config, Render_State *Render_State);
#endif


