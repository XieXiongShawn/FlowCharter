#include "cgraphicsview.h"
#include <QGraphicsScene>
#include <QDebug>

/* Construct an object */
CGraphicsView::CGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setParent(parent);
    myZooming = false;
}

/* Reimplement keyPressEvent() */
void CGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        myZooming = true;
    }
    else
    {
        myZooming = false;
    }

    QGraphicsView::keyPressEvent(event);

    return;
}

/* Reimplement keyReleaseEvent() */
void CGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    myZooming = false;

    QGraphicsView::keyReleaseEvent(event);

    return;
}

/* Reimplement wheelEvent() */
void CGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (myZooming)
    {
        float t = ((event->angleDelta()).y());
        if (t < 0)
        {
            t = (-(60 / t));
        }
        else if (t > 0)
        {
            t = (t / 60);
        }
        else
        {
            t = 1;
        }

        this->scale(t, t);
    }

    QGraphicsView::wheelEvent(event);

    return;
}
