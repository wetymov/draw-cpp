// sector.h
#pragma once
#include "figure.h"
#include "line.h"
#include "arc.h"

class Sector : public Figure {
protected:
    LineFigure l1,  l2;
    ArcFigure arc;

public:
    Sector(int x, int y, int radius, int startAngle, int endAngle, unsigned char r, unsigned char g, unsigned char b)
        : Figure(x, y),
        arc(x, y, radius, startAngle, endAngle, r, g, b)
    {
        double rad1 = startAngle * M_PI / 180.0;
        double rad2 = endAngle * M_PI / 180.0;

        int x1 = x + radius * cos(rad1);
        int y1 = y + radius * sin(rad1);

        int x2 = x + radius * cos(rad2);
        int y2 = y + radius * sin(rad2);

        l1 = LineFigure(x, y, x1 - x, y1 - y, r, g, b);
        l2 = LineFigure(x, y, x2 - x, y2 - y, r, g, b);
    }


    void draw(bool show) override {
        l1.draw(show);
        l2.draw(show);
        arc.draw(show);
    }

    void move(int dx, int dy) override {
        l1.move(dx, dy);
        l2.move(dx, dy);
        arc.move(dx, dy);
        //Figure::move(dx, dy);
    }

    const char* get_type() override { return "Sector"; }
    const char* get_name() override { return "Я сектор"; }
};