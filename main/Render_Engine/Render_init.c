#include <stdint.h>
#include <stdlib.h>
#include "Render_init.h"

void init_Render_FBO(Render_FBO_State* FBO){
    FBO->fbo = (RGB888*)malloc((*FBO->FBO_x_size) * sizeof(RGB888));
}

void bind_FBO_device(RGB888 **devices_store_FBO, RGB888 *render_FBO)
{
    *devices_store_FBO = render_FBO;
}

void free_Render_FBO(Render_FBO_State *FBO)
{
    free(FBO->fbo);
}