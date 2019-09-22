#ifndef CLINEITEM_H
#define CLINEITEM_H

#include <QGraphicsLineItem>

class CLineItem : public QGraphicsLineItem
{
public:
    CLineItem();
    CLineItem(QPointF p1, QPointF p2);
    ~CLineItem();

    QRectF              boundingRect() const;
    void                paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void                Update(QPointF src, QPointF dst);

    void                SetLineSiblings(CLineItem* sibling);
    void                SetLineSiblingsSelection();

private:
    QPointF             myPoint1;
    QPointF             myPoint2;
    QVector<CLineItem*> mySiblings;
};

#endif // CLINEITEM_H
