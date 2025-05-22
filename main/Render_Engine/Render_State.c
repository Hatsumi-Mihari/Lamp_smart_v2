#include "Render_init.h"
#include "Render_State.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"
#include "Render_Engine/lib/RGB_prototype.h"

void Render_Loop(GFX_Utils_Config *GFX_Utils_Config, Render_FBO_State *Render_FBO_State)
{
    GFX_Clear_FBO(&GFX_Utils_Config->GFX_Color_Clear, Render_FBO_State);
}
