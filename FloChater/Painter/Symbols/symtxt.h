#ifndef SYMTXT_H
#define SYMTXT_H

#include <QGraphicsTextItem>

class SymTxt : public QGraphicsTextItem
{
public:
    SymTxt(QString& str, QGraphicsItem* parent);

    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void    SetBold(bool bold);
    void    mousePressEvent(QGraphicsSceneMouseEvent *event);
    void    mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void    focusInEvent(QFocusEvent *event);
    void    focusOutEvent(QFocusEvent *event);
    void    keyPressEvent(QKeyEvent * event);
    void    keyReleaseEvent(QKeyEvent * event);
    bool    isActive() const;

private:
    bool    myBoldFont;
};

#endif // SYMTXT_H
