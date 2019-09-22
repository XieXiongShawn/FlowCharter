#ifndef STEPNBR_H
#define STEPNBR_H

#include <QGraphicsTextItem>

class StepNbr : public QGraphicsTextItem
{
public:
    StepNbr(QString txt, QGraphicsItem* parent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void focusOutEvent(QFocusEvent *event);
};

#endif // STEPNBR_H
