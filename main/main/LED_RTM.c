#include "LED_RTM.h"
#include "Render_Engine/lib/RGB_prototype.h"
#include "driver/rmt.h"
#include "driver/gpio.h"
#include "soc/rmt_reg.h"

void led_init(LED_RMT *config_t){
    rmt_config_t config = {
        .rmt_mode = RMT_MODE_TX,
        .channel = config_t->rmt_channel,
        .gpio_num = config_t->pin_rmt_out,
        .clk_div = RMT_CLK_DIV,
        .mem_block_num = 1,
        .tx_config = {
            .loop_en = false,
            .carrier_en = false,
            .idle_output_en = true,
            .idle_level = RMT_IDLE_LEVEL_LOW,
        }};

    rmt_config(&config);
    rmt_driver_install(config.channel, 0, 0);
    config_t->fbo_rmt = (rmt_item32_t *)calloc((config_t->fbo_size) * 24, sizeof(rmt_item32_t));
}

void ws2812_redner(LED_RMT *config_t){
       uint32_t color;

    for (int j = 0; j < (config_t->fbo_size); j++)
        {
            color = ((uint32_t)(config_t->frame_buffer[j].green) << 16) | ((uint32_t)config_t->frame_buffer[j].red << 8) | (uint32_t)config_t->frame_buffer[j].blue; 
            for (int i = 0; i < 24; i++) { 
                int bit_index = j * 24 + i;
                if (color & (1 << (23 - i))) {
                    config_t->fbo_rmt[bit_index].duration0 = T1H;
                    config_t->fbo_rmt[bit_index].level0 = 1;
                    config_t->fbo_rmt[bit_index].duration1 = T1L;
                    config_t->fbo_rmt[bit_index].level1 = 0;
                } else {
                    config_t->fbo_rmt[bit_index].duration0 = T0H;
                    config_t->fbo_rmt[bit_index].level0 = 1;
                    config_t->fbo_rmt[bit_index].duration1 = T0L;
                    config_t->fbo_rmt[bit_index].level1 = 0;
                }
            }

            
        }
        rmt_write_items(RMT_CHANNEL, config_t->fbo_rmt, (config_t->fbo_size) * 24, true); 
}