#ifndef HSL_COLOR_H
#define HSL_COLOR_H

#include "RGB_prototype.h"

typedef struct HSL_color
{
    float hue;
    float sturation;
    float ligthness;
}HSL_color;

static float hue_to_rgb (float p, float q, float t);

RGB888 gen_pixel_HSL_RGB (HSL_color pixel);

#endif