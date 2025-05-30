#include <stdint.h>
#include "Render_Engine/lib/RGB_prototype.h"


typedef struct Render_FBO_State 
{
    uint8_t *FBO_x_size;
    RGB888* fbo;

    uint8_t FBO_divider_size_fill;
    uint8_t FBO_divide_size_cash;
}Render_FBO_State;
                                
void init_Render_FBO(Render_FBO_State* FBO);
void bind_FBO_device(RGB888 **devices_store_FBO, RGB888 *render_FBO);
void free_Render_FBO(Render_FBO_State* FBO);
