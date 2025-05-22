#include "GFX_Utils.h"
#include "Render_Engine/Render_State.h"
#include "Render_Engine/Render_init.h"
#include "Render_Engine/lib/RGB_prototype.h"
#include <stdlib.h>

void GFX_Clear_FBO(RGB888 *Color_Clear, Render_FBO_State *Render_FBO_State)
{
    for (uint8_t i = 0; i < *Render_FBO_State->FBO_x_size; i++){
        Render_FBO_State->fbo[i] = *Color_Clear;
    } 
}

