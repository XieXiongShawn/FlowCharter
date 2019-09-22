#ifndef LINKERS_H
#define LINKERS_H

#include "clineitem.h"
#include "Painter/Linker/stepnbr.h"
#include <QVector>

#define MyVector QVector<CLineItem*>

enum ArrowDir {Down, Right};

class Linkers : public QVector<CLineItem*>
{
public:
    Linkers();
    Linkers(QGraphicsItem* srcItem, QGraphicsItem* dstItem);
    Linkers(QGraphicsItem* srcItem, QGraphicsItem* dstItem, QString stepNbr);
    ~Linkers();


    void                UpdateSrcItem(QGraphicsItem* itm);
    void                UpdateDstItem(QGraphicsItem* itm);
    void                UpdateLinkers();
    void                UpdateLinkers(QPointF src, qreal srcH, QPointF dst, qreal dstH);

    StepNbr*            SetupStepNumber(QString nbr, QPointF pos);
    void                UpdateStepNbrPos(qreal x, qreal y);

    void                SetSelected(bool selected);

private:
    void                CreateLinker();
    void                PathCreator();
    void                RPathCreator();
    CLineItem*          Lineto();
    CLineItem*          Lineto(qreal x, qreal y);
    void                ArrowDrawer(qreal x, qreal y, ArrowDir dir);

    void                PathUpdate();
    void                RPathUpdate();
    void                UpdateLine(CLineItem* line, qreal x, qreal y);

    void                SetSiblings();

    QPointF             mySrcPoint;
    qreal               mySrcH;
    qreal               mySrcW;
    QPointF             myDstPoint;
    qreal               myDstH;
    qreal               myDstW;
    QPointF             myCurrentPoint;
    QGraphicsPathItem*  myArrow;

    StepNbr*            myStepNbr;
};

#endif // LINKERS_H
