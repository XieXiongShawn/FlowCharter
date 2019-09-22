#ifndef CGRAPHICSVIEW_H
#define CGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class CGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CGraphicsView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);


private:
    bool myZooming;

signals:

public slots:

};

#endif // CGRAPHICSVIEW_H
