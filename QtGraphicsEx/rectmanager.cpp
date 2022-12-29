#include "rectmanager.h"
#include <QGraphicsRectItem>

void RectManager::createRect()
{
    Rect->setRect(getx1(), gety1(), getx2(), gety2());
    Rect->setFlag(QGraphicsItem::ItemIsMovable);    //고정해제
    Rect->setFlag(QGraphicsItem::ItemIsSelectable); //선택 레이어 표출
}
