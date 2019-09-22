#include "clineitem.h"
#include "Painter/MacroForElements.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QPen>
#include <QDebug>

/* Construc an object */
CLineItem::CLineItem()
{
}

/* Construct an object with two given proints */
CLineItem::CLineItem(QPointF p1, QPointF p2)
{
    myPoint1 = p1;
    myPoint2 = p2;

    setLine(myPoint1.x(),myPoint1.y(),
            myPoint2.x(),myPoint2.y());

    setFlags(ItemIsSelectable | ItemIsFocusable | ItemSendsScenePositionChanges);
}

/* Deconstruct the object */
CLineItem::~CLineItem()
{
}

/* Set the size of bounding rect. */
QRectF CLineItem::boundingRect() const
{
    QRectF rect(myPoint1, myPoint2);
    rect.adjust(-MC_BoundingRectOfSleLine, -MC_BoundingRectOfSleLine,
                       MC_BoundingRectOfSleLine, MC_BoundingRectOfSleLine);
    return rect;
}

/* Paint the object */
void CLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (option->state & QStyle::State_Selected)
    {
        QPen pen(Qt::black);

        SetLineSiblingsSelection();

        pen.setWidth(MC_SelectedLineWidth);
        pen.setColor(MC_SelectedLineColor);
        painter->setPen(pen);

        painter->drawLine(myPoint1, myPoint2);
    }
    else
        QGraphicsLineItem::paint(painter, option, widget);

    return;
}

/* Update the item according to given starting point and end point */
void CLineItem::Update(QPointF src, QPointF dst)
{
    myPoint1 = src;
    myPoint2 = dst;
    this->setLine(src.x(),src.y(), dst.x(),dst.y());

    return;
}

/* Add the sibling CLineItem-s */
void CLineItem::SetLineSiblings(CLineItem* siblings)
{
    mySiblings.append(siblings);

    return;
}

/* Set the selection status of the CLineItem group,
    if one of the siblings is selected, all the siblings should be set as selected */
void CLineItem::SetLineSiblingsSelection()
{
    for (int i = 0; i < mySiblings.size(); i++)
    {
        mySiblings.at(i)->setSelected(true);
    }
}
