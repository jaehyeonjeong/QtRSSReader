#ifndef RECTMANAGER_H
#define RECTMANAGER_H

#include "qtmetamacros.h"
#include "rectclass.h"

class QGraphicsRectItem;

class RectManager : public RectClass
{
public:
    RectManager();

public slots:
    //위치와 크기를 지정할 함수
    void createRect();

private:
    QGraphicsRectItem* Rect;
};

#endif // RECTMANAGER_H
