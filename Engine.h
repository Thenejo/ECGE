
#include "SDL.h"
#include "SDL_image.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define RENDER_FLIP_HORIZONTAL
#define Event SDL_Event
#define Rect SDL_Rect
#define fRect SDL_FRect
#define Color SDL_Color

const int MAXFPS=60;
const int MAXTPF=1000/MAXFPS;//ticks per frame
int TICKTIMER;
int FPS;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;
struct Texture
{
    SDL_Texture* baseTexture;
    int w;
    int h;
};


bool closed()
{
    TICKTIMER=SDL_GetTicks();
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        if(evnt.type==SDL_QUIT)
        {
            return true;
        }
    }
    return false;
    
}

void Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
}       

/*Render START */

void CreateWindow(int ScreenSizeX, int ScreenSizeY,const char* name)
{
    WINDOW=SDL_CreateWindow(name,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,ScreenSizeX,ScreenSizeY,SDL_WINDOW_SHOWN);
    RENDERER=SDL_CreateRenderer(WINDOW,-1,SDL_RENDERER_ACCELERATED);
}

void DrawTexture(struct Texture texToDraw,int x,int y)
{
    SDL_Rect dst;
    dst.x=x;
    dst.y=y;
    dst.h=texToDraw.h;
    dst.w=texToDraw.w;
    SDL_RenderCopy(RENDERER,texToDraw.baseTexture,NULL,&dst);
}

void DrawTextureEx(struct Texture texToDraw,double x,double y,float rot,SDL_RendererFlip renderFlip)
{
    SDL_FRect dst;
    dst.x=x;
    dst.y=y;
    dst.h=texToDraw.h;
    dst.w=texToDraw.w;
    SDL_RenderCopyExF(RENDERER,texToDraw.baseTexture,NULL,&dst,rot,NULL,renderFlip);
}

struct Texture LoadTexture(char* res)
{
    struct Texture r;
    r.baseTexture=IMG_LoadTexture(RENDERER,res);
    SDL_QueryTexture(r.baseTexture,NULL,NULL,&r.w,&r.h);
    return r;
}

void UpdateRenderer()
{
    SDL_RenderPresent(RENDERER);
    while(SDL_GetTicks()-TICKTIMER<MAXTPF)
    {
        SDL_Delay(1);
    }
    FPS=1000/(SDL_GetTicks()-TICKTIMER);
}


void ClearRender()
{
    SDL_RenderClear(RENDERER);
}

//Filling it may create performance problems
void DrawRect(Rect* r,Color c,bool isFilled)
{   
    int cr,cg,cb,ca;
    SDL_GetRenderDrawColor(RENDERER,&cr,&cg,&cb,&ca);
    SDL_SetRenderDrawColor(RENDERER,c.r,c.g,c.b,c.a);
    if(isFilled==false)
        SDL_RenderDrawRect(RENDERER,r);
    else
    {
        for(int x=0;x<r->w+1;x++)
        {
            for(int y=0;y<r->h+1;y++)
            {
                SDL_RenderDrawLine(RENDERER,r->x,r->y,r->x+x,r->y+y);
            }
        }
        
    }
    SDL_SetRenderDrawColor(RENDERER,cr,cg,cb,ca);
    
}
void DrawLine(Color c,int x1,int y1,int x2,int y2)
{
    
    int cr,cg,cb,ca;
    SDL_GetRenderDrawColor(RENDERER,&cr,&cg,&cb,&ca);
    SDL_SetRenderDrawColor(RENDERER,c.r,c.g,c.b,c.a);
    SDL_RenderDrawLine(RENDERER,x1,y1,x2,y2);
    SDL_SetRenderDrawColor(RENDERER,cr,cg,cb,ca);
}
void DrawCircle(Color c,int radius,int x,int y)
{

    int cr,cg,cb,ca;
    SDL_GetRenderDrawColor(RENDERER,&cr,&cg,&cb,&ca);
    SDL_SetRenderDrawColor(RENDERER,c.r,c.g,c.b,c.a);
    int i=radius;
    while (i > 0)
    {
        for (int t = 0; t < 360; t++)
        {
            SDL_RenderDrawPoint(RENDERER,x + radius * cos(t), y + radius * sin(t));
        }

        i--;
    }
    SDL_SetRenderDrawColor(RENDERER,cr,cg,cb,ca);
}


/*Render END */






/*Input START */
#define KEY SDL_Keycode
#define KEYS_SPACE SDL_SCANCODE_SPACE
#define KEYS_A SDL_SCANCODE_A

#define KEYS_B SDL_SCANCODE_B
#define KEYS_C SDL_SCANCODE_C

#define KEYS_D SDL_SCANCODE_D
#define KEYS_E SDL_SCANCODE_E

#define KEYS_F SDL_SCANCODE_F
#define KEYS_G SDL_SCANCODE_G

#define KEYS_H SDL_SCANCODE_H
#define KEYS_I SDL_SCANCODE_I

#define KEYS_J SDL_SCANCODE_J
#define KEYS_K SDL_SCANCODE_K

#define KEYS_L SDL_SCANCODE_L
#define KEYS_M SDL_SCANCODE_M

#define KEYS_N SDL_SCANCODE_N
#define KEYS_O SDL_SCANCODE_O

#define KEYS_P SDL_SCANCODE_P
#define KEYS_Q SDL_SCANCODE_Q

#define KEYS_R SDL_SCANCODE_R
#define KEYS_S SDL_SCANCODE_S

#define KEYS_T SDL_SCANCODE_T
#define KEYS_U SDL_SCANCODE_U

#define KEYS_V SDL_SCANCODE_V
#define KEYS_W SDL_SCANCODE_W

#define KEYS_X SDL_SCANCODE_X
#define KEYS_Y SDL_SCANCODE_Y

#define KEYS_Z SDL_SCANCODE_Z
#define KEYS_RIGHT SDL_SCANCODE_RIGHT

#define KEYS_LEFT SDL_SCANCODE_LEFT
#define KEYS_UP SDL_SCANCODE_UP

#define KEYS_DOWN SDL_SCANCODE_DOWN


bool isKeyPressed(SDL_Scancode sdlScanCode)
{
    SDL_PumpEvents();
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    return state[sdlScanCode];
}

void getMousePos(int* p_x,int* p_y)
{
    SDL_PumpEvents();
    SDL_GetMouseState(p_x,p_y);
}

bool isMouseKeyPressed(int keyNum)
{
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();

    buttons = SDL_GetMouseState(&x, &y);

    
    if(keyNum==0)
    {
        if ((buttons & SDL_BUTTON_LMASK) != 0) 
        {
            return true;
        }else
        {
            return false;
        }
    }
    else if(keyNum==1)
    {
        if ((buttons & SDL_BUTTON_RMASK) != 0) 
        {
            return true;
        }else
        {
            return false;
        }
    }
}
/*Input END*/



bool isRectColliding(Rect a,Rect b)
{
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.h + a.y > b.y);
}