// item.h
#pragma once

class Item {
public:
    virtual void draw(bool show) = 0;
    virtual void move(int dx, int dy) = 0;
    virtual const char* get_type() = 0;
    virtual const char* get_name() = 0;

    virtual ~Item() = default;
};