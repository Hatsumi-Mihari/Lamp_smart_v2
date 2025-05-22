#include <stdio.h>
#include <stdint.h>
#include "main/LED_RTM.h"
#include "main/Devices_store.h"
#include "Render_Engine/Render_init.h"
#include "Render_Engine/Render_State.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"
#include "Render_Engine/RE_DEBUG/RE_DEBUG.h"

void app_main(void)
{
    Devices_store devices_store;
    init_Main_State(&devices_store);

    devices_store.led_rmt->fbo_size = 72;
    devices_store.led_rmt->pin_rmt_out = 12;
    devices_store.led_rmt->rmt_channel = RMT_CHANNEL_3;
    led_init(devices_store.led_rmt);

    Render_FBO_State Render_FBO = {
        .FBO_x_size = &devices_store.led_rmt->fbo_size
    };

    init_Render_FBO(&Render_FBO);

    GFX_Utils_Config GFX_Utils_Config = {
        .GFX_Color_Clear = (RGB888){0,0,0}
    };

    Render_State render_state = {
        .fbo_state = &Render_FBO,
        .GFX_Utils_Config = &GFX_Utils_Config
    };

    debug_devices_state_LED_RMT(&devices_store);
    bind_FBO_device(&devices_store.led_rmt->frame_buffer, render_state.fbo_state->fbo);
    debug_State_FBO_UART(&render_state);

    Render_Loop(render_state.GFX_Utils_Config, render_state.fbo_state);
    debug_Render_State_FBO_RGB_UART(&render_state);

    printf("Hello ESP32-S2");
}