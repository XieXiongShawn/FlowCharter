#include "cgraphicsscene.h"
#include <QDebug>

/* Construct a CGraphicsScene object */
CGraphicsScene::CGraphicsScene()
{
    TwoSelectedItem[0] = NULL;
    TwoSelectedItem[1] = NULL;
}

/* Record the selection order of two items for AddLinker() */
void CGraphicsScene::SelectionOrder()
{
    QList<QGraphicsItem *> sceneSelectedItems = this->selectedItems();
    if (sceneSelectedItems.size() == 1)
    {
            TwoSelectedItem[0] = sceneSelectedItems.at(0);
            TwoSelectedItem[1] = NULL;
    }
    else if (sceneSelectedItems.size() == 2)
    {
        if (TwoSelectedItem[0] == sceneSelectedItems.at(0))
            TwoSelectedItem[1] = sceneSelectedItems.at(1);
        else if (TwoSelectedItem[0] == sceneSelectedItems.at(1))
            TwoSelectedItem[1] = sceneSelectedItems.at(0);
    }
    else
    {
        TwoSelectedItem[0] = NULL;
        TwoSelectedItem[1] = NULL;
    }
}
