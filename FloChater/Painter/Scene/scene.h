#ifndef SCENE_H
#define SCENE_H

#include "cgraphicsscene.h"
#include "Painter/Linker/linkers.h"
#include "Painter/Symbols/symbols.h"

class Scene
{
public:
    Scene();
    ~Scene();

    Symbols*                AddStatement(qreal x, qreal y);
    Symbols*                AddStatement(QString statements, qreal x, qreal y);
    void                    ShowStatement(Symbols* state);

    Symbols*                AddStage(qreal x, qreal y);
    Symbols*                AddStage(QString stateNumber, qreal x, qreal y);
    void                    ShowStage(Symbols* stage);

    void                    AddLinkers();
    void                    AddLinkers(QGraphicsItem* srcItem, QGraphicsItem* dstItem);
    void                    ShowLinker(Linkers* lines);

    void                    DeleteItems();
    void                    ClearScene();

    void                    Update();

    CGraphicsScene*         GScene;

private:
    void                    dltItemsFromScene();
    void                    dltItemsFromVectors();

    QVector<Symbols*>       myExistingSymbols;
    qreal                   mySymbolCount;

    QVector<Linkers*>       myExistingLinkers;
    qreal                   myLinkerCount;
};

#endif // SCENE_H
