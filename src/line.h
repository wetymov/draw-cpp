// line.h
#pragma once
#include "figure.h"
#include "adopt.h"

class LineFigure : public virtual Figure {
protected:
    int dx, dy;
    unsigned char r, g, b;
public:
    LineFigure(int x0 = 0, int y0 = 0, int dx0 = 0, int dy0 = 0, unsigned char r0 = 0, unsigned char g0 = 0, unsigned char b0 = 0)
        : Figure(x0, y0), dx(dx0), dy(dy0), r(r0), g(g0), b(b0) {}

    void draw(bool show) override {
        if (show) draw_line(x,y,x+dx,y+dy,r,g,b);
        else draw_line(x, y, x + dx, y + dy, 0, 0, 0);
    };

    void move(int dx, int dy) override {
        draw(false);
        Figure::move(dx, dy);
        draw(true);
    }
    const char* get_type() override { return "LineFigure"; }
    const char* get_name() override { return "Я линия"; }

};
