#ifndef CGRAPHICSSCENE_H
#define CGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>

class CGraphicsScene : public QGraphicsScene
{
public:
    CGraphicsScene();

    void                    SelectionOrder();

    QGraphicsItem*          TwoSelectedItem[2];
};

#endif // CGRAPHICSSCENE_H
