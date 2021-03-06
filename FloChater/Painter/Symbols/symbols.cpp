#include "symbols.h"
#include "Painter/Scene/cgraphicsscene.h"
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTextCursor>
#include <QKeyEvent>
#include <QDebug>

/* Construct an object */
Symbols::Symbols()
{
    mySymbolIsEffective = false;
}

/* Construct an object with given info */
Symbols::Symbols(QString str, QPointF pos, SymShape shape)
{
    myShape = shape;
    myCtrlIsPressed = false;

    myConditionItem = new SymTxt(str, this);
    myConditionItem->setTextInteractionFlags(Qt::NoTextInteraction);
    myConditionItem->setFlags(ItemIsMovable | ItemIsFocusable | ItemSendsScenePositionChanges);

    myStatementItem = NULL;

    mySymbolIsEffective = true;

    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable | ItemSendsScenePositionChanges);
    this->setPos(pos);
}

/* Construct an code-block object with given info */
Symbols::Symbols(QString condition, QString statement, QPointF pos, SymShape shape)
{
    myShape = shape;
    myCtrlIsPressed = false;

    myConditionItem = new SymTxt(condition, this);
    myConditionItem->setTextInteractionFlags(Qt::NoTextInteraction);
    myConditionItem->setFlags(ItemIsMovable | ItemIsFocusable | ItemSendsScenePositionChanges);
    myConditionItem->SetBold(false);

    myStatementItem = new SymTxt(statement, this);
    myStatementItem->setTextInteractionFlags(Qt::NoTextInteraction);
    myStatementItem->setFlags(ItemIsMovable | ItemIsFocusable | ItemSendsScenePositionChanges);
    myStatementItem->SetBold(true);

    mySymbolIsEffective = true;

    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable | ItemSendsScenePositionChanges);
    this->setPos(pos);
}

/* Deconstruct the object */
Symbols::~Symbols()
{
    if (mySymbolIsEffective)
    {
        delete myConditionItem;

        if (myStatementItem)
        {
            delete myStatementItem;
        }
    }
}

/* Determine the bounding rect. */
QRectF Symbols::boundingRect() const
{
    QRectF rect;
    if (myShape == Circle)
    {
        rect.setRect(0,0,
                     MC_StageTxtRect,
                     MC_StageTxtRect);
    }
    else
    {
        rect.setRect(0,0,
                     (MC_TxtWidth + 10),
                     (myConditionItem->boundingRect().height() + myStatementItem->boundingRect().height()));
    }

    return rect;
}

/* Paint the object */
void Symbols::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* )
{
    QPen pen(Qt::black);
    if (option->state & QStyle::State_Selected)
    {
        pen.setWidth(3);
        pen.setColor(Qt::blue);

        CGraphicsScene* scene = (static_cast<CGraphicsScene*> (this->scene()));
        scene->SelectionOrder();
    }
    painter->setPen(pen);
    painter->setBrush(Qt::transparent);

    /* Draw the shape of the object */
    if (myShape == Circle)
        painter->drawEllipse(this->boundingRect());
    else
        painter->drawRect(this->boundingRect());

    /* Keep the alignment of the text item */
    if (myStatementItem)
    {
        qreal rectWidth = this->boundingRect().width();
        myConditionItem->setPos(((rectWidth / 2) - (myConditionItem->boundingRect().width() / 2)),
                                (0));

        myStatementItem->setPos(((rectWidth / 2) - (myStatementItem->boundingRect().width() / 2)),
                                (myConditionItem->boundingRect().height()));

        QPointF separator(0, myConditionItem->boundingRect().height());
        painter->drawLine(separator.x(), separator.y(),
                          (separator.x() + rectWidth), separator.y());
    }
    else
    {
        myConditionItem->setPos(((this->boundingRect().width() / 2) - (myConditionItem->boundingRect().width() / 2)),
                                ((this->boundingRect().height() / 2) - (myConditionItem->boundingRect().height() / 2)));
    }

    //qDebug() << LinkedInS.size() << LinkedToS.size();
    UpdateLinkers();

    return;
}

/* Update the relevant links */
void Symbols::UpdateLinkers()
{
    for (int i = 0; i < LinkedInS.size(); i++)
    {
        LinkedInS.at(i)->UpdateDstItem(this);
    }

    for (int i = 0; i < LinkedToS.size(); i++)
    {
        LinkedToS.at(i)->UpdateSrcItem(this);
    }

    return;
}

/* Process the mousePressEvent */
void Symbols::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    /* If the Ctrl is pressed, text cannot be changed. For a better selection experience */
    if (!myCtrlIsPressed)
    {
        myConditionItem->mousePressEvent(event);
        myConditionItem->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
        myConditionItem->setSelected(true);

        if (myStatementItem)
        {
            myStatementItem->mousePressEvent(event);
            myStatementItem->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
            myStatementItem->setSelected(true);
        }
    }
}

/* Process the mouseDoubleClickEvent */
void Symbols::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);

    myConditionItem->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
    myConditionItem->setSelected(true);
    myConditionItem->mouseDoubleClickEvent(event);

    if (myStatementItem)
    {
        myStatementItem->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard | Qt::TextEditable);
        myStatementItem->setSelected(true);
        myStatementItem->mouseDoubleClickEvent(event);
    }
}

/* Process the focusInEvent */
void Symbols::focusInEvent(QFocusEvent *event)
{
    QGraphicsItem::focusInEvent(event);
}

/* Process the focusOutEvent */
void Symbols::focusOutEvent(QFocusEvent *event)
{
    QGraphicsItem::focusOutEvent(event);

    if (myStatementItem)
    {
        myConditionItem->textCursor().insertText(myConditionItem->textCursor().selectedText());
        myStatementItem->textCursor().insertText(myStatementItem->textCursor().selectedText());
    }
    else
    {
        myConditionItem->textCursor().insertText(myConditionItem->textCursor().selectedText());
    }
}

/* Process the keyPressEvent */
void Symbols::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        myCtrlIsPressed = true;
    }
    QGraphicsItem::keyPressEvent(event);

    if (myStatementItem)
    {
        myConditionItem->keyPressEvent(event);
        myStatementItem->keyPressEvent(event);
    }
    else
    {
        myConditionItem->keyPressEvent(event);
    }
}

/* Process the keyReleaseEvent */
void Symbols::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsItem::keyReleaseEvent(event);

    if (myStatementItem)
    {
        myConditionItem->keyReleaseEvent(event);
        myStatementItem->keyReleaseEvent(event);
    }
    else
    {
        myConditionItem->keyReleaseEvent(event);
    }
}

/* Return the effectiveness */
bool Symbols::IsEffective()
{
    return mySymbolIsEffective;
}
