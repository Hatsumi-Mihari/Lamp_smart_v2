#include <stdint.h>

typedef struct LED_RMT LED_RMT;

typedef struct Devices_store {
    LED_RMT *led_rmt;
}Devices_store;

void init_Main_State(Devices_store *main_state_store);
void clear_Main_State(Devices_store *main_state_store);