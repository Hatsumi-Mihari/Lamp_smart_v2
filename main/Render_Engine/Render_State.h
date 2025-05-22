typedef struct Render_FBO_State Render_FBO_State;
typedef struct GFX_Utils_Config GFX_Utils_Config;


typedef struct Render_State
{
    Render_FBO_State *fbo_state;
    GFX_Utils_Config *GFX_Utils_Config;
}Render_State;

void Render_Loop(GFX_Utils_Config* GFX_Utils_Config, Render_FBO_State* Render_FBO_State);


