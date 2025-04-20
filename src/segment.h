
// segment.h
#pragma once
#include "line.h"
#include "arc.h"

class Segment : public LineFigure, public ArcFigure {
protected:
    LineFigure l1;
    ArcFigure arc;

public:
    Segment(int x, int y, int rad, double startAngleDeg, double endAngleDeg, unsigned char r, unsigned char g, unsigned char b)
        : Figure(x, y),
        arc(x, y, rad, startAngleDeg, endAngleDeg, r, g, b)
    {
        double a1 = startAngleDeg * M_PI / 180.0;
        double a2 = endAngleDeg * M_PI / 180.0;

        int x1 = x + rad * cos(a1);
        int y1 = y + rad * sin(a1);

        int x2 = x + rad * cos(a2);
        int y2 = y + rad * sin(a2);

        l1 = LineFigure(x1, y1, x2 - x1, y2 - y1, r, g, b); // хорда
    }



    void draw(bool show) override {
        l1.draw(show);
        arc.draw(show);
    }

    void move(int dx, int dy) override {
        l1.move(dx, dy);
        arc.move(dx, dy);
        //Figure::move(dx, dy);
    }

    const char* get_type() override { return "Segment"; }
    const char* get_name() override { return "Я сегмент"; }
};
