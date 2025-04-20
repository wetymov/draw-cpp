#pragma once
#include "item.h"

class Figure : public virtual Item {
protected:
    int x, y = 0;
public:
    Figure(int x0, int y0) : x(x0), y(y0) {}
    virtual void move(int dx, int dy) override {
        x += dx;
        y += dy;
    }
};
