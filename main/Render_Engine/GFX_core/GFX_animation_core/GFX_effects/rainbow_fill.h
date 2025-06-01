#ifndef RAINBOW_FILL_H
#define RAINBOW_FILL_H
#include "Render_Engine/lib/RGB_prototype.h"
#include "Render_Engine/lib/HSL_color.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct Render_FBO_State Render_FBO_State;

typedef struct Rainbow_effect_obj
{
    RGB888 Color_Fill_Start;
    bool revers_flag;
    uint8_t mode;
    uint16_t pos_range_x1;
    uint16_t pos_range_x2;
    Render_FBO_State *Render_FBO_State;
}Rainbow_effect_obj;

typedef struct Rainbow_effect_gradient
{
    HSL_color color_1;
    HSL_color color_2;
    float speed;
    uint16_t pos_range_x1;
    uint16_t pos_range_x2;
    Render_FBO_State *Render_FBO_State;
}Rainbow_effect_gradient;


void ranibow_one_color_fill(void* arg_fuction, float *progress);
void ranibow_linery_gradient(void* arg_fuction, float *progress);
#endif
