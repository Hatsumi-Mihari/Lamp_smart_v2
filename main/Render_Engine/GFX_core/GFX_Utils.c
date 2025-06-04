#include "GFX_Utils.h"
#include "Render_Engine/Render_State.h"
#include "Render_Engine/Render_init.h"
#include "Render_Engine/lib/RGB_prototype.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <string.h>

void GFX_Clear_FBO(RGB888 *Color_Clear, Render_FBO_State *Render_FBO_State)
{
    uint8_t temp_cash = Render_FBO_State->FBO_divide_size_cash;
    for (uint8_t i = 0; i < (temp_cash); i++)
    {
        Render_FBO_State->fbo[i] = *Color_Clear;
        Render_FBO_State->fbo[i + temp_cash] = *Color_Clear;
        Render_FBO_State->fbo[i + (temp_cash + temp_cash)] = *Color_Clear;
        Render_FBO_State->fbo[i + (temp_cash + temp_cash + temp_cash)] = *Color_Clear;
    }
}

void GFX_Fill_Color(RGB888 Color, Render_FBO_State *Render_FBO_State)
{
    GFX_Clear_FBO(&Color, Render_FBO_State);
}

void GFX_Fill_Color_range(uint16_t pos_x1, uint16_t pos_x2, RGB888 Color, Render_FBO_State *Render_FBO_State)
{
    uint16_t start_point = pos_x1 < pos_x2 ? pos_x1 : pos_x2;

    if (pos_x1 < 0 || pos_x2 > Render_FBO_State->FBO_x_size)
        return;

    for (int i = start_point; i < pos_x2; i++)
    {
        Render_FBO_State->fbo[i] = Color;
    }
}

void GFX_gen_hsl_gradient(uint16_t pos_x1, uint16_t pos_x2, HSL_color color_1, HSL_color color_2, Render_FBO_State *Render_FBO_State, HSL_color *color_cash_buffer, float *t_cash_buffer)
{
    HSL_color color_interpolate;

    if (pos_x1 < 0 || pos_x2 > Render_FBO_State->FBO_x_size)
        return;
    float delta = color_2.hue - color_1.hue;
    if (delta > 180.0f)
        delta -= 360.0f;
    if (delta < -180.0f)
        delta += 360.0f;

    

    for (int i = pos_x1; i < pos_x2; i++)
    {
        t_cash_buffer[0] = (float)i / (pos_x2 - 1);
        t_cash_buffer[1] = (float)i + 1 / (pos_x2 - 1);
        t_cash_buffer[2] = (float)i + 2 / (pos_x2 - 1);
        t_cash_buffer[3] = (float)i + 3/ (pos_x2 - 1);

        color_interpolate.hue = color_1.hue + delta * t_cash_buffer[0];
        if (color_interpolate.hue < 0.0f)
            color_interpolate.hue += 360.0f;
        if (color_interpolate.hue >= 360.0f)
            color_interpolate.hue -= 360.0f;

        color_interpolate.ligthness = color_1.ligthness + (color_2.ligthness - color_1.ligthness) * t_cash_buffer[0];
        color_interpolate.sturation = color_1.sturation + (color_2.sturation - color_1.sturation) * t_cash_buffer[0];
        Render_FBO_State->fbo[i] = gen_pixel_HSL_RGB(color_interpolate);
    }
}

void GFX_brightness_full_FBO(Render_FBO_State *Render_FBO_State, uint8_t value){
    for (int i = 0; i < Render_FBO_State->FBO_x_size; i++){
            Render_FBO_State->fbo[i].red = (uint8_t)((Render_FBO_State->fbo[i].red * value + 50) / 100);
            Render_FBO_State->fbo[i].green = (uint8_t)((Render_FBO_State->fbo[i].green * value + 50) / 100);
            Render_FBO_State->fbo[i].blue = (uint8_t)((Render_FBO_State->fbo[i].blue * value + 50) / 100);
        
    }
}
