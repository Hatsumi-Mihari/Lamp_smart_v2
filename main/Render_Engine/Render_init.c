#include <stdint.h>
#include <stdlib.h>
#include "Render_init.h"
#include "esp_heap_caps.h"

void init_Render_FBO(Render_FBO_State* FBO){
    FBO->fbo = heap_caps_malloc(*FBO->FBO_x_size * sizeof(RGB888), MALLOC_CAP_INTERNAL);
    
    if (FBO->FBO_divider_size_fill == NULL) FBO->FBO_divider_size_fill = 4;
    FBO->FBO_divide_size_cash = *FBO->FBO_x_size / FBO->FBO_divider_size_fill;

    FBO->fbo_cash = heap_caps_malloc(FBO->FBO_divider_size_fill * sizeof(RGB888), MALLOC_CAP_INTERNAL);
}

void bind_FBO_device(RGB888 **devices_store_FBO, RGB888 *render_FBO)
{
    *devices_store_FBO = render_FBO;
}

void free_Render_FBO(Render_FBO_State *FBO)
{
    free(FBO->fbo);
}