#include "Render_Engine/lib/RGB_prototype.h"

typedef struct Render_FBO_State Render_FBO_State;

typedef struct GFX_Utils_Config
{
    RGB888 GFX_Color_Clear;
    RGB888 GFX_Color_Fill_State;
}GFX_Utils_Config;

void GFX_Clear_FBO(RGB888 *Color_Clear, Render_FBO_State *Render_FBO_State);
void GFX_Fill_Color(RGB888 Color, Render_FBO_State *Render_FBO_State);

