#include <stdint.h>
#include <stdlib.h>
#include "Render_init.h"
#include "Render_Engine/lib/Color_Spaces.h"

void init_Render_FBO(Render_FBO_State* FBO){
    FBO->fbo = (RGB888*)malloc(FBO->FBO_x_size * sizeof(RGB888));
}

void free_Render_FBO(Render_FBO_State *FBO)
{
    free(FBO->fbo);
}