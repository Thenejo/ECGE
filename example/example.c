#include <stdio.h>
#include "Engine.h"

int main()
{
    Init(); 
    Rect r;
    r.w=32;
    r.h=32;
    r.x=20-r.w/2;
    r.y=20-r.h/2;
    Rect r1;
    r1.w=32;
    r1.h=32;
    r1.x=40-r1.w/2;
    r1.y=40-r1.h/2;
    CreateWindow(640,640,"My Game Window"); 
    Color a={209, 84, 178,255};
    Color c={122,0, 18,255};
    int x=0,y=0;
    float rot;
    struct Texture cubeToDraw=LoadTexture("res/plyr.png");
    while (!closed())    //closed() returns if the app shouldbe closed or not
    {
       
        ClearRender(); //clears the renderer 
        rot+=1;
        if(1==isKeyPressed(KEYS_RIGHT))
        {
              x+=1;
        }

        if(1==isKeyPressed(KEYS_LEFT))
        {
              x-=1;
        }

        if(1==isKeyPressed(KEYS_UP))
        {
              y-=1;
        }

        if(1==isKeyPressed(KEYS_DOWN))
        {
              y+=1;
        }
        if(isMouseKeyPressed(0)==false)
        {
            DrawTextureEx(cubeToDraw,x,y,rot,FLIP_NONE);
        }
        r1.x=x;
        r1.y=y;
        DrawRect(&r,a,isRectColliding(r,r1)); //Draws a rect "r "if it is colliding with r1 filled else not filled
        DrawRect(&r1,a,false);
        DrawLine(c,x,y,x+r.w,y);
        DrawCircle(c,10,320,320);
        UpdateRenderer();
        printf("FPS: %i \n", FPS);
    }
    
}


