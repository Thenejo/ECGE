# ECGE

An easy header only graphics engine based on SDL2 and made with C

# Dependencies

 SDL2 
 SDL_image

# Tutorials

 -The Game Loop
 ```c
  #include "Engine.h"

  int main()
  {
   Init(); //Initializing SDL and ECGE engine
   while(!closed()) //closed() is a ECGE function that says if the app should be closed or not
   {
     ClearRender(); //Clears the renderer put it on the start of the game loop
     //Do your logic stuff here
     UpdateRenderer(); // You should put it at the end of your game loop
   }
  }
 ```
 
 
 
 
