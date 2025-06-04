#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/lib/HSL_color.h"

typedef struct Render_FBO_State Render_FBO_State;

typedef struct GFX_Utils_Config
{
    RGB888 GFX_Color_Clear;
    RGB888 GFX_Color_Fill_State;
}GFX_Utils_Config;

void GFX_Clear_FBO(RGB888 *Color_Clear, Render_FBO_State *Render_FBO_State);
void GFX_Fill_Color(RGB888 Color, Render_FBO_State *Render_FBO_State);

void GFX_Fill_Color_range(uint16_t pos_x1, uint16_t pos_x2, RGB888 Color, Render_FBO_State *Render_FBO_State);

void GFX_gen_hsl_gradient(uint16_t pos_x1, uint16_t pos_x2, HSL_color color_1, HSL_color color_2, Render_FBO_State *Render_FBO_State, HSL_color *color_cash_buffer, float *t_cash_buffer);

void GFX_brightness_full_FBO(Render_FBO_State *Render_FBO_State, uint8_t value);