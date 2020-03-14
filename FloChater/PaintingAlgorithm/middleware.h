#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include "Painter/Scene/scene.h"
#include "TxtProc/TxtOperation/txtreader.h"
#include "TxtProc/CodeBlocks/stateextractor.h"

struct Node
{
    int Sequence;
    int MaxBranch;
    int CurrentBranch;
};

class Middleware
{
public:
    Middleware(Scene* scene, TxtReader* codeBlocks);
    ~Middleware();

    void                    InitORUpdate();

private:
    Scene*                  myScene;
    StateExtractor*         myStates;
    QVector<States>         myStatements;

    int                     myNodeNbr;
    QVector<Node*>          myNodes;
    QVector<int>            myBranchNbr;
    QVector<int>            myBranchSequence;
    int                     myLastCarctPos;
    int                     myInitStateNbr;
    QVector<Symbols*>       myStageSymbols;
    void                    myGetNodeNumber();
    void                    myInitNodeInfo();
    void                    myInitStageSymbols();
    int                     myGetNodeSequence(int i);
    int                     myGetMaxBranchNumber(int i);
    int                     myChar2Int(char ch);

    QVector<Node*>          myCurrentLoop;
    Node*                   myNextNode;
    void                    myCode2FlowChart();
    void                    myLoopBuilding();
};

#endif // MIDDLEWARE_H
