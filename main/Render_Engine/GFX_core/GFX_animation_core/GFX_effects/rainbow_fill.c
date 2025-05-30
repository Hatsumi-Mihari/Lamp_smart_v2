#include "rainbow_fill.h"
#include <stddef.h>
#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"

void ranibow_one_color_fill(void *arg_fuction, float *progress)
{
    Rainbow_effect_obj *obj = (Rainbow_effect_obj *)arg_fuction;
    uint8_t uint_progress = (uint8_t)(*progress * 255);

    obj->Color_Fill_Start.red = uint_progress;
    obj->Color_Fill_Start.green = uint_progress;
    obj->Color_Fill_Start.blue = uint_progress;

    switch (obj->mode)
    {
    case 0:
        GFX_Fill_Color(obj->Color_Fill_Start, obj->Render_FBO_State);
        break;
    case 1:
        GFX_Fill_Color_range(obj->pos_range_x1, obj->pos_range_x2,
                             obj->Color_Fill_Start, obj->Render_FBO_State);
        break;
    default:
        break;
    }
}
