#include "symtxt.h"
#include "../MacroForElements.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QTextCursor>
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>

/* Construct an object */
SymTxt::SymTxt(QString &str, QGraphicsItem *parent)
{
    this->setPlainText(str);
    this->setParentItem(parent);
    this->setTextWidth(MC_TxtWidth);

    myBoldFont = false;
}

/* Paint the object */
void SymTxt::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);

    if (this->isSelected() && !(this->parentItem()->isSelected()))
    {
        this->parentItem()->setSelected(true);
    }

    this->setTextWidth(-1);
    if (this->boundingRect().width() >= MC_TxtWidth)
        this->setTextWidth(MC_TxtWidth);

    if (myBoldFont)
    {
        QFont font = this->font();
        font.setBold(true);
        this->setFont(font);
    }
}

/* Set the font as bold */
void SymTxt::SetBold(bool bold)
{
    myBoldFont = bold;

    return;
}

/* Process the mousePressEvent */
void SymTxt::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->parentItem()->setSelected(true);

    QGraphicsTextItem::mousePressEvent(event);
}

/* Process the mouseDoubleClickEvent */
void SymTxt::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
    this->setSelected(true);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

/* Process the focusInEvent */
void SymTxt::focusInEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusInEvent(event);
}

/* Process the focusOutEvent */
void SymTxt::focusOutEvent(QFocusEvent *event)
{
    this->textCursor().insertText(this->textCursor().selectedText());
    QGraphicsTextItem::focusOutEvent(event);
    this->setTextInteractionFlags(Qt::NoTextInteraction);
}

/* Process the keyPressEvent */
void SymTxt::keyPressEvent(QKeyEvent * event)
{
    QGraphicsTextItem::keyPressEvent(event);
}

/* Process the keyReleaseEvent */
void SymTxt::keyReleaseEvent(QKeyEvent * event)
{
    QGraphicsTextItem::keyReleaseEvent(event);
}
