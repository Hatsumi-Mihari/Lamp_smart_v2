#include "Render_init.h"
#include "Render_State.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"
#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/lib/STL_Lib/List.h"
#include "Render_Engine/RE_DEBUG/RE_Time_Layer_proto.h"
#include "Render_Engine/GFX_core/GFX_animation_core/GFX_maneger_animation.h"
#include "Render_Engine/RE_DEBUG/RE_DEBUG.h"
#include "esp_heap_caps.h"
#include "esp_timer.h"
#include "esp_log.h"

List *Redner_Loop_init_debug_list_time(){
    List* ptr_struct_debug_time = (List*)heap_caps_malloc(sizeof(List), MALLOC_CAP_SPIRAM);
    list_init(ptr_struct_debug_time, sizeof(RE_DB_Time_Layer), 0);

    list_push(ptr_struct_debug_time, 
        &(RE_DB_Time_Layer){
        .key_name_Layer = "RE_DB_Time_Full",
        .time_start = 0,
        .time_end = 0});

    return ptr_struct_debug_time;
}

void render_loop(Render_State *Render_State)
{
    DB_UART_update_watchdog_time_render_pipeline(Render_State->List_GFX_PipeLine, 0, esp_timer_get_time(), 0);

    //GFX_Fill_Color((RGB888){255, 0 , 0}, Render_State->fbo_state);
    tick_update_animations(Render_State->Queue_GFT_Animation, &Render_State->flag_clear_fbo);
    if (Render_State->flag_clear_fbo){
        GFX_Clear_FBO(&Render_State->GFX_Utils_Config->GFX_Color_Clear, Render_State->fbo_state);
    }

    DB_UART_update_watchdog_time_render_pipeline(Render_State->List_GFX_PipeLine, 0, -1, esp_timer_get_time());
    Render_State->drawn_frames++;
    
}

void redner_debug_loop_callback(void *arg){
    DB_UART_redner_debug_loop_callback(arg);
}

void Render_init_debug_loop(Render_Timer_Config *Render_Timer_Config, Render_State *Render_State)
{
    Render_Timer_Config->loop_config.arg = Render_State;
    Render_Timer_Config->loop_config.callback = &redner_debug_loop_callback;
    Render_Timer_Config->loop_config.name = "Debug_Render_Loop";
    Render_Timer_Config->timer_err = esp_timer_create(&Render_Timer_Config->loop_config, &Render_Timer_Config->loop_handle);

    if (Render_Timer_Config->timer_err != ESP_OK) {
        ESP_LOGE("Timer_Debug_Loop", "Error Init, Debug Loop");
        return;
    }

   esp_timer_start_periodic(Render_Timer_Config->loop_handle, Render_Timer_Config->ms_loop_update);
    
}
