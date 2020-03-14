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

    Symbols*                AddStatement(qreal x, qreal y, QString condition="Condition", QString statements="Statements");
    void                    ShowStatement(Symbols* state);

    Symbols*                AddStage(qreal x, qreal y, QString stateNumber="02.03.04.05");
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
