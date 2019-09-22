#include "stepnbr.h"
#include "Painter/MacroForElements.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QTextCursor>

/* Construct an object */
StepNbr::StepNbr(QString txt, QGraphicsItem* parent)
{
    this->setHtml(txt);
    this->setParentItem(parent);

    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable | ItemSendsScenePositionChanges);
    setTextInteractionFlags(Qt::NoTextInteraction);
}

/* Paint the object */
void StepNbr::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    bool txtEditable = false;

    /* Set the style of selected item */
    QPen pen(Qt::black);
    if (option->state & QStyle::State_Selected)
    {
        txtEditable = true;

        pen.setWidth(MC_SelectedLineWidth);
        pen.setColor(MC_SelectedLineColor);
    }
    else
    {
        txtEditable = false;

        pen.setColor(MC_StepBGColour);
    }

    painter->setPen(pen);
    painter->setBrush(MC_StepBGColour);
    painter->drawRect(boundingRect());

    /* Determine if txt of the item is editable
        Only when the item is selected, the txt will be editable,
        If the text interaction flag set was done, an new mouse clicking is needed.
            The operation would be same as an QGraphicsTextItem */
    if (txtEditable)
    {
        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
    }
    else
    {
        setTextInteractionFlags(Qt::NoTextInteraction);
    }

    QGraphicsTextItem::paint(painter, option, widget);

    return;
}

/* Clear the text selection and text cursor */
void StepNbr::focusOutEvent(QFocusEvent *event)
{
    /* If the item is focused out, clear the text selection */
    this->textCursor().insertText(this->textCursor().selectedText());

    QGraphicsTextItem::focusOutEvent(event);

    return;
}
