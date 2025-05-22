
typedef struct Devices_store Devices_store;
typedef struct Render_State Render_State;

void debug_devices_state(Devices_store *Devices_store);

void debug_devices_state_LED_RMT(Devices_store *Devices_store);

void debug_State_FBO_UART(Render_State* Render_State);
void debug_Render_State_FBO_RGB_UART(Render_State* Render_State);