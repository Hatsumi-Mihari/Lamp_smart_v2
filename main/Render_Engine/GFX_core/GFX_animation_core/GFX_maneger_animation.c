#include "GFX_maneger_animation.h"
#include "Render_Engine/lib/STL_Lib/List.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "Render_Engine/Render_State.h"
#include "Render_Engine/lib/RGB_prototype.h"


List* init_animation_queue()
{
    List* Queue_animation = (List*)heap_caps_malloc(sizeof(List), MALLOC_CAP_SPIRAM);
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

void tick_update_animations(void *arg)
{
    List *Queue_animation = (List*)arg;
    GFX_state_animation animation_t; 
    for (int i = 0; i < Queue_animation->size; i++){
        animation_t = *(GFX_state_animation*)list_get(Queue_animation, i);
        if (animation_t.passed_time_qs <= animation_t.delay_qs) animation_t.passed_time_qs += animation_t.tickrat_qs;
        else if (animation_t.flag_loop_infinity) animation_t.passed_time_qs = 0;
        else { 
            remove_animation_pipeline(Queue_animation, i); 
            if (i != 0) i--;
            continue;
        }

        if (animation_t.callback_function) {
            if (!animation_t.arg_fuction) animation_t.callback_function(NULL);
            else animation_t.callback_function(animation_t.arg_fuction);
        }
    }
}

void run_animation_timer_loop(Render_Timer_Config *timer_config, List* Queue_animation)
{
    timer_config->loop_config.arg = Queue_animation;
    timer_config->loop_config.callback = &tick_update_animations;
    timer_config->loop_config.name = "Queue_animation";
    timer_config->timer_err = esp_timer_create(&timer_config->loop_config, &timer_config->loop_handle);

    if(timer_config->timer_err != ESP_OK){
        ESP_LOGE("Timer_Animation_Loop", "Error Init, Animation Loop %s", esp_err_to_name(timer_config->timer_err));
        return;
    }

    esp_timer_start_periodic(timer_config->loop_handle, timer_config->ms_loop_update);
}