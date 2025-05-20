#include "Devices_store.h"
#include "LED_RTM.h"


void init_Main_State(Devices_store *main_state_store){
    main_state_store->led_rmt = malloc(sizeof(LED_RMT));
}

void clear_Main_State(Devices_store *main_state_store){
    free(main_state_store);
}