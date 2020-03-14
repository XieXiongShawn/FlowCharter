#include "linkers.h"
#include "Painter/MacroForElements.h"
#include <QPointer>
#include <QDebug>

/* Construct an empty object */
Linkers::Linkers()
{
}

/* Construct an object with two given QGraphicsItems with a given step number */
Linkers::Linkers(QGraphicsItem* srcItem, QGraphicsItem* dstItem, QString stepNbr)
{
    mySrcPoint  = srcItem->pos();
    mySrcH      = srcItem->boundingRect().height();
    mySrcW      = srcItem->boundingRect().width();
    myDstPoint  = dstItem->pos();
    myDstH      = dstItem->boundingRect().height();
    myDstW      = dstItem->boundingRect().width();
    myArrow     = new QGraphicsPathItem;

    if (stepNbr != "")
        myStepNbr   = SetupStepNumber(stepNbr, myDstPoint);
    else
        myStepNbr   = NULL;

    CreateLinker();
}

/* Deconstruct the object */
Linkers::~Linkers()
{
    myArrow->setParentItem(NULL);
    delete myArrow;

    for (int i = 0; i < this->size(); i++)
    {
        delete this->at(i);
    }
}

/* Determine which kind of the path should be created */
void Linkers::CreateLinker()
{
    if (mySrcPoint.y() < myDstPoint.y())
    {
        PathCreator();
    }
    else
    {
        RPathCreator();
    }

    return;
}

/* Create a path up to down */
void Linkers::PathCreator()
{
    QPointF lineSrc;
    lineSrc.setX(mySrcPoint.x() + (mySrcW / 2));
    lineSrc.setY(mySrcPoint.y() + mySrcH);

    QPointF lineDst;
    lineDst.setX(myDstPoint.x() + (myDstW / 2));
    lineDst.setY(myDstPoint.y());

    myCurrentPoint = lineSrc;
    this->append(Lineto(lineSrc.x(), (lineSrc.y() + MC_HalfHDistance)));
    this->append(Lineto(lineDst.x(), (lineSrc.y() + MC_HalfHDistance)));
    this->append(Lineto(lineDst.x(), lineDst.y()));
    this->append(Lineto());

    ArrowDrawer(lineDst.x(), lineDst.y(), Down);

    SetSiblings();

    return;
}

/* Create a path down to up */
void Linkers::RPathCreator()
{
    QPointF lineSrc;
    lineSrc.setX(mySrcPoint.x() + (mySrcW / 2));
    lineSrc.setY(mySrcPoint.y() + mySrcH);

    QPointF lineDst;
    lineDst.setX(myDstPoint.x());
    lineDst.setY(myDstPoint.y() + (myDstH /2));

    myCurrentPoint = lineSrc;
    this->append(Lineto(lineSrc.x(), (lineSrc.y() + MC_HalfHDistance)));
    this->append(Lineto((lineDst.x() - MC_HalfWDistance), (lineSrc.y() + MC_HalfHDistance)));
    this->append(Lineto((lineDst.x() - MC_HalfWDistance), lineDst.y()));
    this->append(Lineto(lineDst.x(), lineDst.y()));

    ArrowDrawer(lineDst.x(), lineDst.y(), Right);

    SetSiblings();

    return;
}

/* New a empty member of the CLineItem group */
CLineItem* Linkers::Lineto()
{
    CLineItem* lineItem = new CLineItem(myCurrentPoint, myCurrentPoint);

    return lineItem;
}

/* New a member of the CLineItem group with given point */
CLineItem* Linkers::Lineto(qreal x, qreal y)
{
    QPointF newPoint(x, y);
    CLineItem* lineItem = new CLineItem(myCurrentPoint, newPoint);

    myCurrentPoint = newPoint;

    return lineItem;
}

/* Set up the CLineItem group */
void Linkers::SetSiblings()
{
    for (int i = 0; i < this->size(); i++)
    {
        for (int j = 0; j < this->size(); j++)
        {
            if (j != i)
            {
                this->at(i)->SetLineSiblings(this->at(j));
            }
        }
    }

    return;
}

/* Update the starting point of this Linkers object */
void Linkers::UpdateSrcItem(QGraphicsItem *itm)
{
    mySrcPoint  = itm->pos();
    mySrcH      = itm->boundingRect().height();

    UpdateLinkers();

    return;
}

/* Update the end point of this Linkers object */
void Linkers::UpdateDstItem(QGraphicsItem *itm)
{
    myDstPoint  = itm->pos();
    myDstH      = itm->boundingRect().height();

    UpdateLinkers();

    return;
}

/* Update the path with existing srcPoint and dstPoint */
void Linkers::UpdateLinkers()
{
    if ((mySrcPoint.y() + mySrcH + 5) < myDstPoint.y())
    {
        PathUpdate();
    }
    else if ((mySrcPoint.y() + mySrcH + 5) >= myDstPoint.y())
    {
        RPathUpdate();
    }

    return;
}

/* Update the path with given info of srcItem and dstItem */
void Linkers::UpdateLinkers(QPointF src, qreal srcH, QPointF dst, qreal dstH)
{
    mySrcPoint  = src;
    mySrcH      = srcH;
    myDstPoint  = dst;
    myDstH      = dstH;

    UpdateLinkers();

    return;
}

/* Update the path as up-down */
void Linkers::PathUpdate()
{
    qreal srcX = (mySrcPoint.x() + (mySrcW / 2));
    qreal srcY = (mySrcPoint.y() + mySrcH);

    qreal dstX = (myDstPoint.x() + (myDstW / 2));
    qreal dstY = (myDstPoint.y());

    qreal hHDist = ((dstY - srcY) / 2);

    myCurrentPoint.setX(srcX);
    myCurrentPoint.setY(srcY);
    UpdateLine(this->at(0), srcX,(srcY + hHDist));
    UpdateLine(this->at(1), dstX, (srcY + hHDist));
    UpdateLine(this->at(2), dstX, dstY);
    UpdateLine(this->at(3), dstX, dstY);

    ArrowDrawer(dstX, dstY, Down);
    if (myStepNbr != NULL)
        UpdateStepNbrPos(dstX, dstY);

    return;
}

/* Update the path as down-up */
void Linkers::RPathUpdate()
{
    qreal srcX = (mySrcPoint.x() + (mySrcW / 2));
    qreal srcY = (mySrcPoint.y() + mySrcH);

    myCurrentPoint.setX(srcX);
    myCurrentPoint.setY(srcY);

    qreal dstX = (myDstPoint.x());
    qreal dstY = (myDstPoint.y() + (myDstH /2));

    if (myDstPoint.x() > (mySrcPoint.x() + mySrcW + MC_ArrowH))
    {
        if ((dstY - srcY) < (MC_ArrowH + 5))
        {
            qreal hWDist = ((dstX - (mySrcPoint.x() + mySrcW)) / 2);

            UpdateLine(this->at(0), srcX, (srcY + MC_HalfHDistance));
            UpdateLine(this->at(1), (dstX - hWDist), (srcY + MC_HalfHDistance));
            UpdateLine(this->at(2), (dstX - hWDist), dstY);
            UpdateLine(this->at(3), dstX, dstY);
        }
        else
        {
            qreal hWDist = ((dstX - srcX) / 2);
            qreal hHDist = ((dstY - srcY) / 2);

            UpdateLine(this->at(0), srcX, (srcY + hHDist));
            UpdateLine(this->at(1), (dstX - hWDist), (srcY + hHDist));
            UpdateLine(this->at(2), (dstX - hWDist), dstY);
            UpdateLine(this->at(3), dstX, dstY);
        }
    }
    else
    {
        if (myDstPoint.y() <= mySrcPoint.y())
        {
            UpdateLine(this->at(0), srcX, (srcY + MC_HalfHDistance));
            UpdateLine(this->at(1), (dstX - myDstW), (srcY + MC_HalfHDistance));
            UpdateLine(this->at(2), (dstX - myDstW), dstY);
            UpdateLine(this->at(3), dstX, dstY);
        }
        else
        {
            UpdateLine(this->at(0), srcX, (dstY + MC_HDistance));
            UpdateLine(this->at(1), (dstX - myDstW), (dstY + MC_HDistance));
            UpdateLine(this->at(2), (dstX - myDstW), dstY);
            UpdateLine(this->at(3), dstX, dstY);
        }
    }

    ArrowDrawer(dstX, dstY, Right);
    if (myStepNbr != NULL)
        UpdateStepNbrPos(dstX, dstY);

    return;
}

/* Update a line of Linkers object */
void Linkers::UpdateLine(CLineItem* line, qreal x, qreal y)
{
    QPointF newP(x, y);
    line->Update(myCurrentPoint, newP);

    myCurrentPoint.setX(newP.x());
    myCurrentPoint.setY(newP.y());

    return;
}

/* Draw the arrow to inidicate the direction of the link */
void Linkers::ArrowDrawer(qreal x, qreal y, ArrowDir dir)
{
    QPointF pos(x, y);
    QPainterPath shape(pos);

    if (dir == Right)
    {
        shape.lineTo((pos.x() - MC_ArrowH), (pos.y() - MC_ArrowW));
        shape.lineTo((pos.x()  - 4), pos.y());
        shape.lineTo((pos.x() - MC_ArrowH), (pos.y() + MC_ArrowW));
        shape.lineTo(pos);
    }
    else
    {
        shape.lineTo((pos.x() - MC_ArrowW), (pos.y() - MC_ArrowH));
        shape.lineTo(pos.x(), (pos.y() - 4));
        shape.lineTo((pos.x() + MC_ArrowW), (pos.y() - MC_ArrowH));
        shape.lineTo(pos);
    }

    myArrow->setPath(shape);
    myArrow->setParentItem(this->at(this->size() - 1));

    return;
}

/* Set up a step number */
StepNbr* Linkers::SetupStepNumber(QString nbr, QPointF pos)
{
    StepNbr* stepNbr = new StepNbr(nbr, this->at(3));
    stepNbr->setPos(pos);

    return stepNbr;
}

/* Update the position of step number item */
void Linkers::UpdateStepNbrPos(qreal x, qreal y)
{
    myStepNbr->setPos((x - 25), (y - 40 ));

    return;
}

/* Set the CLineItems selection */
void Linkers::SetSelected(bool selected)
{
    if (selected)
    {
        for (int i = 0; i < this->size(); i++)
        {
            this->at(i)->setSelected(true);
        }

        if (myStepNbr)
        {
            myStepNbr->setSelected(true);
        }
    }

    return;
}
