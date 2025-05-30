#include "Render_Engine/Render_init.h"
#include "Render_Engine/Render_State.h"
#include "main/LED_RTM.h"
#include "main/Devices_store.h"
#include "RE_DEBUG.h"
#include "esp_mac.h"
#include "esp_log.h"
#include "RE_Time_Layer_proto.h"
#include "Render_Engine/lib/STL_Lib/List.h"
#include "Render_Engine/GFX_core/GFX_animation_core/GFX_maneger_animation.h"


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

void DB_UART_out_log_time_redner_part_pipeLine(const char *name, int64_t time_start, int64_t time_end)
{
    ESP_LOGI(name, "%lld µs", time_end - time_start);
}

void DB_UART_out_log_pipeline_animations(GFX_state_animation* obj){
    ESP_LOGI("Animation gueue", "name: %s, loop_infinity: %d, delay_ms: %d", obj->name, obj->flag_loop_infinity, obj->delay_qs);
}

void DB_UART_get_all_info_about_render_pipeline(List* RE_DB_List_time_PipeLine){
    RE_DB_Time_Layer *temp_unit_debug;
    for (int i = 0; i < RE_DB_List_time_PipeLine->size; i++){
        temp_unit_debug = (RE_DB_Time_Layer*)list_get(RE_DB_List_time_PipeLine, i);
        DB_UART_out_log_time_redner_part_pipeLine(temp_unit_debug->key_name_Layer,
        temp_unit_debug->time_start, temp_unit_debug->time_end);
    }
}

void DB_UART_get_all_info_about_pipeline_animations(List* Queue_animation){
    for (int i = 0; i < Queue_animation->size; i++){
        DB_UART_out_log_pipeline_animations((GFX_state_animation*)list_get(Queue_animation, i));
    }
}

void DB_UART_update_watchdog_time_render_pipeline(List *RE_DB_List_time_PipeLine, uint8_t index, int64_t time_start, int64_t time_end)
{
    RE_DB_Time_Layer* temp_obj_edit = list_get(RE_DB_List_time_PipeLine, index);
    if (time_start != -1) temp_obj_edit->time_start = time_start;
    if (time_end != -1) temp_obj_edit->time_end = time_end;
    list_update(RE_DB_List_time_PipeLine, index, temp_obj_edit);
}

void DB_UART_redner_debug_loop_callback(void *arg){
    Render_State *Render_State_t = (Render_State*)arg;
    debug_Render_State_FBO_RGB_UART(Render_State_t);    
    ESP_LOGI("DRAM total", "%d bytes", (int)(heap_caps_get_total_size(MALLOC_CAP_INTERNAL)));
    ESP_LOGI("PSRAM total", "%d bytes\n", (int)(heap_caps_get_total_size(MALLOC_CAP_SPIRAM)));

    ESP_LOGI("DRAM busy", "%d bytes", (int)(heap_caps_get_total_size(MALLOC_CAP_INTERNAL) - heap_caps_get_free_size(MALLOC_CAP_INTERNAL)));
    ESP_LOGI("PSRAM busy", "%d bytes\n", (int)(heap_caps_get_total_size(MALLOC_CAP_SPIRAM) - heap_caps_get_free_size(MALLOC_CAP_SPIRAM)));


    DB_UART_get_all_info_about_render_pipeline(Render_State_t->List_GFX_PipeLine);
    ESP_LOGI("Frame", "%lld", Render_State_t->drawn_frames);

    DB_UART_get_all_info_about_pipeline_animations(Render_State_t->Queue_GFT_Animation);

    printf("\033[2J\033[H"); 
}

void DB_UART_LOG(){

}
