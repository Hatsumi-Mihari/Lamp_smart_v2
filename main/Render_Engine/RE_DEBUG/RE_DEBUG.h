
typedef struct Devices_store Devices_store;
typedef struct Render_State Render_State;
typedef struct RE_DB_Time_Layer RE_DB_Time_Layer;
typedef struct GFX_state_animation GFX_state_animation;
typedef struct List List;


void debug_devices_state(Devices_store *Devices_store);

void debug_devices_state_LED_RMT(Devices_store *Devices_store);

void debug_State_FBO_UART(Render_State* Render_State);
void debug_Render_State_FBO_RGB_UART(Render_State* Render_State);

void DB_UART_out_log_time_redner_part_pipeLine(const char *name, int64_t time_start, int64_t time_end);
void DB_UART_out_log_pipeline_animations(GFX_state_animation* obj);
void DB_UART_get_all_info_about_render_pipeline (List* RE_DB_List_time_PipeLine);
void DB_UART_get_all_info_about_pipeline_animations(List* Queue_animation);

void DB_UART_update_watchdog_time_render_pipeline(List *RE_DB_List_time_PipeLine, uint8_t index, int64_t time_start, int64_t time_end);
void DB_UART_redner_debug_loop_callback(void *arg);

void DB_UART_LOG();