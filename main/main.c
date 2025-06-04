#include <stdio.h>
#include <stdint.h>
#include "main/LED_RTM.h"
#include "main/Devices_store.h"
#include "Render_Engine/Render_init.h"
#include "Render_Engine/Render_State.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"
#include "Render_Engine/GFX_core/GFX_animation_core/GFX_maneger_animation.h"
#include "Render_Engine/GFX_core/GFX_animation_core/GFX_effects/rainbow_fill.h"
#include "Render_Engine/lib/STL_Lib/List.h"
#include "Render_Engine/RE_DEBUG/RE_Time_Layer_proto.h"
#include "Render_Engine/RE_DEBUG/RE_DEBUG.h"
#include <esp_log.h>
#include "esp_heap_caps.h"


void app_main(void)
{
    Devices_store devices_store = {
        .x_size = 72
    };
    init_Main_State(&devices_store);

    devices_store.led_rmt->fbo_size = 72;
    devices_store.led_rmt->pin_rmt_out = 12;
    devices_store.led_rmt->rmt_channel = RMT_CHANNEL_3;
    led_init(devices_store.led_rmt);

    Render_FBO_State Render_FBO = {
        .FBO_x_size = &devices_store.led_rmt->fbo_size};

    init_Render_FBO(&Render_FBO);

    GFX_Utils_Config GFX_Utils_Config = {
        .GFX_Color_Clear = (RGB888){0, 0, 0}};

    Render_Timer_Config timer_debug = {
        .ms_loop_update = 166666
    };

    Render_State render_state = {
        .fbo_state = &Render_FBO,
        .GFX_Utils_Config = &GFX_Utils_Config,
        .List_GFX_PipeLine = Redner_Loop_init_debug_list_time(),
        .Queue_GFT_Animation = init_animation_queue(),
    };

    bind_FBO_device(&devices_store.led_rmt->frame_buffer, render_state.fbo_state->fbo);

    Render_init_debug_loop(&timer_debug, &render_state);


    add_animation_pipeline(render_state.Queue_GFT_Animation, (GFX_state_animation){
        .name = "Rainbow Range Animation 1",
        .callback_function = &ranibow_linery_gradient,
        .duration_ms = 5000,
        .tick_interval_ms = 1000,
        .time_start = esp_timer_get_time(),
        .flag_loop_infinity = true,
        .arg_fuction = &(Rainbow_effect_gradient){
            .color_1 = {
                .hue = 0.0f,
                .ligthness = 0.5f,
                .sturation = 1.0f
            },
            .color_2 = {
                .hue = 45.0f,
                .ligthness = 0.5f,
                .sturation = 1.0f
            },
            .speed = 0.8f,
            .pos_range_x1 = 0,
            .pos_range_x2 = *render_state.fbo_state->FBO_x_size,
            .Render_FBO_State = render_state.fbo_state
        }
    });
    /**/

    debug_State_FBO_UART(&render_state);
    debug_devices_state_LED_RMT(&devices_store);

    while (1) {
        render_loop(&render_state);
        //ws2812_redner(devices_store.led_rmt);
        vTaskDelay(pdMS_TO_TICKS(17));
    }
    printf("Hello ESP32-S2");
}