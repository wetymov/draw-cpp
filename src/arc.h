// arc.h
#pragma once
#include "figure.h"
#include "adopt.h"

class ArcFigure : public virtual Figure {
protected:
    int radius, startAngle, endAngle;
    unsigned char r, g, b;
public:
    ArcFigure(int x0 = 0, int y0 = 0, int rad = 0, int sa = 0, int ea = 0, unsigned char r0 = 0, unsigned char g0 = 0, unsigned char b0 = 0)
        : Figure(x0, y0), radius(rad), startAngle(sa), endAngle(ea), r(r0), g(g0), b(b0) {}

    void draw(bool show) override {
            if (show) draw_arc(x, y, radius, startAngle, endAngle, r, g, b);
            else draw_arc(x, y, radius, startAngle, endAngle, 0, 0, 0);
    }

    void move(int dx, int dy) override {
        draw(false);
        Figure::move(dx, dy);
        draw(true);
    }
    const char* get_type() override { return "ArcFigure"; }
    const char* get_name() override { return "п Фѓур"; }
};
