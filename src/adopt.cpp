
#pragma comment( lib, "x64/SDL3.lib" )
//#pragma comment( lib, "arm64/SDL3.lib" )

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
//#include "adopt.h"

#define M_PI 3.14159

typedef unsigned char byte;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define NLINES 1000
struct Line{
  int state; // 0 - no, 1 - pass, 2 - active
  byte r,g,b;
  int x0,y0,x1,y1;
}; 
Line ALines[NLINES];

void draw_line(int _x0,int _y0,int _x1,int _y1,byte _r,byte _g,byte _b){
  int i=0;
  Line *pl=&ALines[0];
  for(i=0;i<NLINES;i++){
    pl=&ALines[i];
    if(pl->state == 0) break;
    if(pl->state == 1) continue;
    if(pl->x0 != _x0) continue;
    if(pl->y0 != _y0) continue;
    if(pl->x1 != _x1) continue;
    if(pl->y1 != _y1) continue;
    if(_r == 0 && _g == 0 && _b == 0){ pl->state=1; return; }
    pl->r=_r; pl->g=_g; pl->b=_b;
    return;
  }
  pl->x0=_x0; pl->y0=_y0; pl->x1=_x1; pl->y1=_y1; pl->r=_r; pl->g=_g; pl->b=_b;
  pl->state=2;
}

#define NARCS 1000

struct Arc{
  int state; // 0 - no, 1 - pass, 2 - active
  byte r,g,b;
  int x,y,rad,s,e;
}; 
Arc AArcs[NARCS];

 void draw_arc(int _x, int _y, int _rad, int _start, int _end, byte _r, byte _g, byte _b)
 {
   int i=0;
   Arc *pl=&AArcs[0];
   for(i=0;i<NARCS;i++){
     pl=&AArcs[i];
     if(pl->state == 0) break;
     if(pl->state == 1) continue;
     if(pl->x != _x) continue;
     if(pl->y != _y) continue;
     if(pl->rad != _rad) continue;
     if(pl->s != _start) continue;
     if(pl->e != _end) continue;
     if(_r == 0 && _g == 0 && _b == 0){ pl->state=1; return; }
     pl->r=_r; pl->g=_g; pl->b=_b;
     return;
   }
   pl->x=_x; pl->y=_y; pl->rad=_rad; pl->s=_start; pl->e=_end; pl->r=_r; pl->g=_g; pl->b=_b;
   pl->state=2;
 }

 void draw_arc_internal(int ind){
   Arc *pl=&AArcs[ind];
   int x=pl->x, y=pl->y, rad=pl->rad, start=pl->s, end=pl->e;
   int cx = 0,cy = rad, df = 1 - rad, d_e = 3, d_se = -2 * rad + 5;
   int xpcx, xmcx, xpcy, xmcy, ypcy, ymcy, ypcx, ymcx;
   byte drawoct;
   int startoct, endoct, oct, stopval_start = 0, stopval_end = 0;
   double dstart, dend, temp = 0.0;
   if(rad < 0) return;
   if(rad == 0) {
     SDL_SetRenderDrawColor(renderer, pl->r, pl->g, pl->b, SDL_ALPHA_OPAQUE);
     SDL_RenderPoint(renderer, x, y);
     return;   
   }
   // Octant labelling
   //      
   //  \ 5 | 6 /
   //   \  |  /
   //  4 \ | / 7
   //     \|/
   //------+------ +x
   //     /|\
   //  3 / | \ 0
   //   /  |  \
   //  / 2 | 1 \
   //      +y
   drawoct = 0; 
   start %= 360; end %= 360;
   while (start < 0) start += 360; while (end < 0) end += 360;
   start %= 360; end %= 360;
   // now, we find which octants we're drawing in.
   startoct = start / 45; endoct = end / 45;
   oct = startoct - 1; // we increment as first step in loop
   // stopval_start, stopval_end; 
   // what values of cx to stop at.
   do{
     oct = (oct + 1) % 8;
     if(oct == startoct){
       // need to compute stopval_start for this octant.  Look at picture above if this is unclear
       dstart = (double)start;
       switch(oct){
         case 0:
         case 3:
           temp = sin(dstart * M_PI / 180.);
           break;
         case 1:
         case 6:
           temp = cos(dstart * M_PI / 180.);
           break;
         case 2:
         case 5:
           temp = -cos(dstart * M_PI / 180.);
           break;
         case 4:
         case 7:
           temp = -sin(dstart * M_PI / 180.);
           break;
       }
       temp *= rad;
       stopval_start = (int)temp; // always round down
       if(oct % 2) drawoct |= (1 << oct); // this is basically like saying drawoct[oct] = true, if drawoct were a bool array
       else        drawoct &= 255 - (1 << oct); // this is basically like saying drawoct[oct] = false
     }
     if(oct == endoct){
       dend = (double)end;
       switch(oct){
         case 0:
         case 3:
           temp = sin(dend * M_PI / 180);
           break;
         case 1:
         case 6:
           temp = cos(dend * M_PI / 180);
           break;
         case 2:
         case 5:
           temp = -cos(dend * M_PI / 180);
           break;
         case 4:
         case 7:
           temp = -sin(dend * M_PI / 180);
           break;
       }
       temp *= rad;
       stopval_end = (int)temp;
       if(startoct == endoct){
         if(start > end){ drawoct = 255; }else{ drawoct &= 255 - (1 << oct); }
       }else{ 
         if(oct % 2){ drawoct &= 255 - (1 << oct); }else{ drawoct |= (1 << oct); }
       }
     }else{ 
       if(oct != startoct){ drawoct |= (1 << oct); }
     }
   }while(oct != endoct);
   SDL_SetRenderDrawColor(renderer, pl->r, pl->g, pl->b, SDL_ALPHA_OPAQUE);
   do{
     ypcy = y + cy; ymcy = y - cy;
     if(cx > 0){
       xpcx = x + cx; xmcx = x - cx;
       if(drawoct & 4)  SDL_RenderPoint(renderer, xmcx, ypcy);
       if(drawoct & 2)  SDL_RenderPoint(renderer, xpcx, ypcy);
       if(drawoct & 32) SDL_RenderPoint(renderer, xmcx, ymcy);
       if(drawoct & 64) SDL_RenderPoint(renderer, xpcx, ymcy);
     }else{
       if(drawoct & 96) SDL_RenderPoint(renderer, x, ymcy);
       if(drawoct & 6)  SDL_RenderPoint(renderer, x, ypcy);
     }
     xpcy = x + cy; xmcy = x - cy;
     if(cx > 0 && cx != cy){
       ypcx = y + cx; ymcx = y - cx;
       if(drawoct & 8)   SDL_RenderPoint(renderer, xmcy, ypcx);
       if(drawoct & 1)   SDL_RenderPoint(renderer, xpcy, ypcx);
       if(drawoct & 16)  SDL_RenderPoint(renderer, xmcy, ymcx);
       if(drawoct & 128) SDL_RenderPoint(renderer, xpcy, ymcx);
     }else if(cx == 0){
       if(drawoct & 24)  SDL_RenderPoint(renderer, xmcy, y);
       if(drawoct & 129) SDL_RenderPoint(renderer, xpcy, y);
     }
     if(stopval_start == cx){
       if(drawoct & (1 << startoct)){ drawoct &= 255 - (1 << startoct); }               
       else{ drawoct |= (1 << startoct); }
     }
     if(stopval_end == cx){
       if(drawoct & (1 << endoct)){ drawoct &= 255 - (1 << endoct); }
       else{ drawoct |= (1 << endoct); }
     }
     if(df < 0){
       df += d_e; d_e += 2; d_se += 2;
     }else{
       df += d_se; d_e += 2; d_se += 4; cy--;
     }
     cx++;
   }while(cx <= cy);
 }

void render_all(void){
  SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
  SDL_RenderClear(renderer);  /* start with a blank canvas. */
  
  for(int i=0;i<NLINES;i++){
    Line *pl=&ALines[i];
    if(pl->state == 0) break;
    if(pl->state == 1) continue;
    SDL_SetRenderDrawColor(renderer, pl->r, pl->g, pl->b, SDL_ALPHA_OPAQUE);  
    SDL_RenderLine(renderer, pl->x0, pl->y0, pl->x1, pl->y1);
  }
  for(int i=0;i<NARCS;i++){
    Arc *pl=&AArcs[i];
    if(pl->state == 0) break;
    if(pl->state == 1) continue;
    draw_arc_internal(i);
  }

  SDL_RenderPresent(renderer);  /* put it all on the screen! */
}

bool init(void){
  if(!SDL_Init(SDL_INIT_VIDEO)){
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return false;
  }
  if(!SDL_CreateWindowAndRenderer("examples/renderer/primitives", 640, 480, 0, &window, &renderer)){
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return false;
  }
  return true;
}

void leave(void){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void wait4mouse(void){
  SDL_Event e;
    
  render_all();
  while (1) {
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT || e.type ==  SDL_EVENT_MOUSE_BUTTON_UP){
        return;
      }
    }
    SDL_Delay(10);
  }
}

//int main(int argc, char *argv[]){
//  main();
//  return 0;
//}
