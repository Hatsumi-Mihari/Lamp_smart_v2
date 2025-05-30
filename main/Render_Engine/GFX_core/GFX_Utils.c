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
