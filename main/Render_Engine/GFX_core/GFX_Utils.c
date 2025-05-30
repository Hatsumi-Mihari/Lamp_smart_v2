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
    for (uint8_t i = 0; i < (temp_cash); i++){
        Render_FBO_State->fbo[i] = *Color_Clear;
        Render_FBO_State->fbo[i+temp_cash] = *Color_Clear;
        Render_FBO_State->fbo[i+(temp_cash + temp_cash)] = *Color_Clear;
        Render_FBO_State->fbo[i+(temp_cash + temp_cash + temp_cash)] = *Color_Clear;
        
    } 
}

void GFX_Fill_Color(RGB888 Color, Render_FBO_State *Render_FBO_State){
    GFX_Clear_FBO(&Color, Render_FBO_State);
}

void GFX_Fill_Color_range(uint16_t pos_x1, uint16_t pos_x2, RGB888 Color, Render_FBO_State *Render_FBO_State){
    uint16_t start_point = pos_x1 < pos_x2 ? pos_x1 : pos_x2;

    if (pos_x1 < 0 || pos_x2 > Render_FBO_State->FBO_x_size) return;

    for (int i = start_point; i < pos_x2; i++){
        Render_FBO_State->fbo[i] = Color;
    }
}
