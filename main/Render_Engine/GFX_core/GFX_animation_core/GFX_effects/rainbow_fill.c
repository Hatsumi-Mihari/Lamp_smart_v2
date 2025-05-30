#include "rainbow_fill.h"
#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"

void ranibow_one_color_fill(void *arg_fuction)
{
    Rainbow_effect_obj *obj = (Rainbow_effect_obj*)arg_fuction;
    
    obj->Color_Fill_Start.red += obj->step_change;
    obj->Color_Fill_Start.green += obj->step_change;
    obj->Color_Fill_Start.blue += obj->step_change;

    GFX_Fill_Color(obj->Color_Fill_Start, obj->Render_FBO_State);
}
