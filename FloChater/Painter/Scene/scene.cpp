#include "scene.h"
#include "Painter/MacroForElements.h"
#include <QDebug>

/* Construct an object */
Scene::Scene()
{
    GScene  = new CGraphicsScene;

    mySymbolCount = 0;
    myLinkerCount = 0;
}

/* Deconstruct an object */
Scene::~Scene()
{
    dltItemsFromVectors();

    delete GScene;
}

/* New a statement with given position */
Symbols* Scene::AddStatement(qreal x, qreal y)
{
    return AddStatement("Statements", x, y);
}

/* New a statement with given info */
Symbols* Scene::AddStatement(QString statements, qreal x, qreal y)
{
    QPointF p((x - (MC_TxtWidth / 2) - 5), y);

    Symbols* statement = new Symbols(statements, p, Rect);
    myExistingSymbols.append(statement);
    mySymbolCount++;

    ShowStatement(statement);
    return statement;
}

/* Add the given statement onto the scene */
void Scene::ShowStatement(Symbols *state)
{
    GScene->addItem(state);

    return;
}

/* New a stage with given position */
Symbols* Scene::AddStage(qreal x, qreal y)
{
    return AddStage("02.03.04.05", x, y);
}

/* New a stage with given info */
Symbols* Scene::AddStage(QString stateNumber, qreal x, qreal y)
{
    QPointF p((x - (MC_StageTxtRect / 2)), y);
    Symbols* stage = new Symbols(stateNumber, p, Circle);
    myExistingSymbols.append(stage);

    ShowStage(stage);

    return stage;
}

/* Add the given stage onto the scene */
void Scene::ShowStage(Symbols *stage)
{
    GScene->addItem(stage);

    return;
}

/* Link the two selected item */
void Scene::AddLinkers()
{
    if (GScene->selectedItems().size() == 2)
    {
        QGraphicsItem* item0 = GScene->TwoSelectedItem[0];
        QGraphicsItem* item1 = GScene->TwoSelectedItem[1];

        AddLinkers(item0, item1);
    }

    return;
}

/* New a Linkers to link the two given QGraphicsItem-s */
void Scene::AddLinkers(QGraphicsItem* srcItem, QGraphicsItem* dstItem)
{
    Linkers* linker = new Linkers(srcItem, dstItem);
    myExistingLinkers.append(linker);

    ShowLinker(linker);

    /* Add the link information for source item */
    Symbols* srcSym = (static_cast<Symbols*>(srcItem));
    srcSym->LinkedToS.append(linker);

    /* Add the link information for destinated item */
    Symbols* dstSym = (static_cast<Symbols*>(dstItem));
    dstSym->LinkedInS.append(linker);

    return;
}

/* Add the given Linkers onto the scene */
void Scene::ShowLinker(Linkers* lines)
{
    for (int i = 0; i < lines->size(); i++)
    {
        GScene->addItem(lines->at(i));
    }

    return;
}

/* Delete the selected items */
void Scene::DeleteItems()
{
    if (GScene->selectedItems().size() == (GScene->items().size() - 1))
    {
        dltItemsFromScene();
        dltItemsFromVectors();
    }
    else
    {
        dltItemsFromScene();
    }

    return;
}

/* Remove the selected items from scen */
void Scene::dltItemsFromScene()
{
    while (GScene->selectedItems().size())
    {
        GScene->removeItem(GScene->selectedItems().at(0));
    }

    return;
}

/* Delete all the items and clear the vectors */
void Scene::dltItemsFromVectors()
{
    for (int i = 0; i < myExistingLinkers.size(); i++)
    {
        delete myExistingLinkers.at(i);
    }
    for (int i = 0; i < myExistingSymbols.size(); i++)
    {
        delete myExistingSymbols.at(i);
    }

    myExistingLinkers.clear();
    myExistingSymbols.clear();

    return;
}

/* Scene clearance */
void Scene::ClearScene()
{
    dltItemsFromScene();
    dltItemsFromVectors();

    return;
}

/* Scene update */
void Scene::Update()
{
    GScene->update();
}
