#include <stdint.h>
typedef struct RGB888 RGB888;


typedef struct Render_FBO_State 
{
    uint8_t FBO_x_size;
    RGB888* fbo;
}Render_FBO_State;
                                
void init_Render_FBO(Render_FBO_State* FBO);
void free_Render_FBO(Render_FBO_State* FBO);
