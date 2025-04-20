#pragma once

typedef unsigned char byte;

void draw_line(int _x0,int _y0,int _x1,int _y1,byte _r,byte _g,byte _b);
void draw_arc(int _x, int _y, int _rad, int _start, int _end, byte _r, byte _g, byte _b);
void wait4mouse(void);


