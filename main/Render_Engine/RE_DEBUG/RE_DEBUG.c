#include "Render_Engine/Render_init.h"
#include "Render_Engine/Render_State.h"
#include "main/LED_RTM.h"
#include "main/Devices_store.h"
#include "RE_DEBUG.h"
#include "esp_mac.h"
#include "esp_log.h"

void debug_devices_state_LED_RMT(Devices_store *Devices_store){
    ESP_LOGI("DEBUG_LED_RMT ", "(fbo_size: %d)/ (pin_out_rmt) %d / (rmt_channel) %d / (state_FBO_link: %d)/ (state_FBO_RMT_link) %d)", 
        Devices_store->led_rmt->fbo_size, 
        Devices_store->led_rmt->pin_rmt_out,
        Devices_store->led_rmt->rmt_channel,
        (int)Devices_store->led_rmt->frame_buffer,
        (int)Devices_store->led_rmt->fbo_rmt
    );
}

void debug_State_FBO_UART(Render_State* Render_State){
        ESP_LOGI("RENDER_STATE_FBO ", "(FBO_size: %d), (FBO_link: %d)",
            *Render_State->fbo_state->FBO_x_size,
            (int)Render_State->fbo_state->fbo
    );
}

void debug_Render_State_FBO_RGB_UART(Render_State *Render_State)
{
    for (uint8_t i = 0; i < *Render_State->fbo_state->FBO_x_size; i++){
        printf("\033[38;2;%d;%d;%dm█", Render_State->fbo_state->fbo[i].red, Render_State->fbo_state->fbo[i].green, Render_State->fbo_state->fbo[i].blue);
    }
    printf("\n");
}
