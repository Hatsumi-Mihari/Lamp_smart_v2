#include <stdio.h>
#include <stdint.h>
#include "main/LED_RTM.h"
#include "main/Devices_store.h"
#include "Render_Engine/Render_init.h"
#include "Render_Engine/Render_State.h"

void app_main(void)
{
    Devices_store devices_store;
    init_Main_State(&devices_store);

    devices_store.led_rmt->fbo_size = 72;
    led_init(devices_store.led_rmt);

    Render_FBO_State Render_FBO = {
        .FBO_x_size = devices_store.led_rmt->fbo_size
    };

    init_Render_FBO(&Render_FBO);

    Render_State render_state = {
        .FBO_state = &Render_FBO
    };
    printf("Test ESP-IDF");
}