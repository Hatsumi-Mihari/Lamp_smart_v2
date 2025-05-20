#include "LED_RTM.h"
#include "Render_Engine/lib/Color_Spaces.h"
#include "driver/rmt.h"
#include "driver/gpio.h"
#include "soc/rmt_reg.h"

void led_init(LED_RMT *fbo_config){
    rmt_config_t config = {
        .rmt_mode = RMT_MODE_TX,
        .channel = RMT_CHANNEL,
        .gpio_num = PIN_LED,
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
    fbo_config->fbo_rmt = (rmt_item32_t *)calloc((fbo_config->fbo_size) * 24, sizeof(rmt_item32_t));
}

void ws2812_redner(LED_RMT *fbo_config){
       uint32_t color;

    for (int j = 0; j < (fbo_config->fbo_size); j++)
        {
            color = ((uint32_t)(fbo_config->frame_buffer[j].green) << 16) | ((uint32_t)fbo_config->frame_buffer[j].red << 8) | (uint32_t)fbo_config->frame_buffer[j].blue; 
            for (int i = 0; i < 24; i++) { 
                int bit_index = j * 24 + i;
                if (color & (1 << (23 - i))) {
                    fbo_config->fbo_rmt[bit_index].duration0 = T1H;
                    fbo_config->fbo_rmt[bit_index].level0 = 1;
                    fbo_config->fbo_rmt[bit_index].duration1 = T1L;
                    fbo_config->fbo_rmt[bit_index].level1 = 0;
                } else {
                    fbo_config->fbo_rmt[bit_index].duration0 = T0H;
                    fbo_config->fbo_rmt[bit_index].level0 = 1;
                    fbo_config->fbo_rmt[bit_index].duration1 = T0L;
                    fbo_config->fbo_rmt[bit_index].level1 = 0;
                }
            }

            
        }
        rmt_write_items(RMT_CHANNEL, fbo_config->fbo_rmt, (fbo_config->fbo_size) * 24, true); 
}