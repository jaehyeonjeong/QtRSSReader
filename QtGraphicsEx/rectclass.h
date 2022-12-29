#ifndef RECTCLASS_H
#define RECTCLASS_H

class RectClass
{
public:
    RectClass(int, int, int, int);

    int getx1()const;
    void setx1(int&);
    int gety1()const;
    void sety1(int&);
    int getx2()const;
    void setx2(int&);
    int gety2()const;
    void sety2(int&);

private:
    int x1, y1, x2, y2;
};

#endif // RECTCLASS_H
