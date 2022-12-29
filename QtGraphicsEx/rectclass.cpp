#include "rectclass.h"

RectClass::RectClass(int _x1, int _y1, int _x2, int _y2)
{
    x1 = _x1;
    y1 = _y1;
    x2 = _y2;
    y2 = _y2;
}

int RectClass::getx1() const
{
    return x1;
}

void RectClass::setx1(int& _x1)
{
    x1 = _x1;
}

int RectClass::gety1() const
{
    return y1;
}

void RectClass::sety1(int& _y1)
{
    y1 = _y1;
}


int RectClass::getx2() const
{
    return x2;
}

void RectClass::setx2(int& _x2)
{
    x2 = _x2;
}

int RectClass::gety2() const
{
    return y2;
}

void RectClass::sety2(int& _y2)
{
    y2 = _y2;
}
