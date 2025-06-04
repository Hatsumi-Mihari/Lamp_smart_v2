#include "rainbow_fill.h"
#include <stddef.h>
#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/GFX_core/GFX_Utils.h"
#include "Render_Engine/lib/HSL_color.h"
#include <math.h>

void ranibow_one_color_fill(void *arg_fuction, float *progress)
{
    Rainbow_effect_obj *obj = (Rainbow_effect_obj *)arg_fuction;
    HSL_color hsl_color = {
        .hue = *progress * 360.0f,
        .ligthness = 0.5f,
        .sturation = 1.0f
    };
    obj->Color_Fill_Start = gen_pixel_HSL_RGB(hsl_color);

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

void ranibow_linery_gradient(void *arg_fuction, float *progress)
{
    Rainbow_effect_gradient *obj = (Rainbow_effect_gradient *)arg_fuction;
    float nolmal_speed = fmodf((*progress + obj->speed), 360.0f);
    obj->color_1.hue += nolmal_speed;
    obj->color_2.hue += nolmal_speed;

    GFX_gen_hsl_gradient(obj->pos_range_x1, obj->pos_range_x2, obj->color_1, obj->color_2, obj->Render_FBO_State, obj->color_cash_buffer, obj->t_cash_buffer);
}
