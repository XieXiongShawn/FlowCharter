#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "symtxt.h"
#include "Painter/MacroForElements.h"
#include "Painter/Linker/linkers.h"
#include <QGraphicsItem>

enum SymShape {Rect, Circle};

class Symbols : public QGraphicsItem
{
public:
    Symbols();
    //Symbols(QString str, QPointF pos, SymShape shape);
    Symbols(QString statement, QPointF pos, SymShape shape);
    ~Symbols();

    QRectF              boundingRect() const;
    void                paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void                UpdateLinkers();
    void                mousePressEvent(QGraphicsSceneMouseEvent *event);
    void                mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void                focusInEvent(QFocusEvent *event);
    void                focusOutEvent(QFocusEvent *event);
    void                keyPressEvent(QKeyEvent * event);
    void                keyReleaseEvent(QKeyEvent * event);

    bool                IsEffective();

    QVector<Linkers*>   LinkedInS;
    QVector<Linkers*>   LinkedToS;

private:
    SymShape            myShape;

    SymTxt*             myStatementItem;
    bool                myCtrlIsPressed;

    bool                mySymbolIsEffective;
};

#endif // SYMBOLS_H
