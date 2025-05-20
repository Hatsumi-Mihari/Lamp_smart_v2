#include <stdint.h>
#include "driver/rmt.h"
#define PIN_LED 12
#define RMT_CHANNEL RMT_CHANNEL_3

typedef struct RGB888 RGB888;

typedef struct LED_RMT
{
    uint8_t fbo_size; // Size Frame Buffer Out, from Redner_Engine State 
    RGB888 *frame_buffer; // Link for seving Frame Buffer Out, from Redner_Engine State 
    rmt_item32_t *fbo_rmt; // Local dynamic buffer for send data on led strit
}LED_RMT;

#define RMT_CLK_DIV 2
#define T0H 14 // ~0.35 µs
#define T0L 32 // ~0.80 µs
#define T1H 32 // ~0.80 µs
#define T1L 14 // ~0.35 µs

void led_init(LED_RMT *fbo_config);
void ws2812_redner(LED_RMT *fbo_config);