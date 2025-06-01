#include "HSL_color.h"
#include "RGB_prototype.h"
#include <stdint.h>
#include <math.h>
#define HSL_DEGREE 360.0f

static float hue_to_rgb (float p, float q, float t){
    if (t < 0.0f) t+=1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f/2.0f) return q;
    if (t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
    return p;
}

RGB888 gen_pixel_HSL_RGB(HSL_color pixel)
{
    float r,g,b;

    pixel.hue = fmodf(pixel.hue, HSL_DEGREE) / HSL_DEGREE;

    if (pixel.sturation == 0.0f)
    {
        r = g = b = pixel.ligthness;
    }
    else
    {
        float q = (pixel.ligthness < 0.5f) ? (pixel.ligthness * (1 + pixel.sturation)) : (pixel.ligthness + pixel.sturation - pixel.ligthness * pixel.sturation);
        float p = 2 * pixel.ligthness - q;

        r = hue_to_rgb(p, q, pixel.hue + 1.0f/3.0f);
        g = hue_to_rgb(p, q, pixel.hue);
        b = hue_to_rgb(p, q, pixel.hue - 1.0f/3.0f);
    }

    return (RGB888){
        .red = (uint8_t)(r * 255),
        .green = (uint8_t)(g * 255),
        .blue = (uint8_t)(b * 255)
    };
}