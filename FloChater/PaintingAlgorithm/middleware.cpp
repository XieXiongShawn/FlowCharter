#include "middleware.h"
#include "PaintingAlgorithm/MacroForMiddleware.h"
#include "TxtProc/CodeBlocks/states.h"
#include <QDebug>

/* Construct an object with the given info */
Middleware::Middleware(Scene* scene, TxtReader* codeBlocks)
{
    myScene         = scene;
    myStates        = &(codeBlocks->TxtProxer);

    InitORUpdate();
}

/* Deconstruct the object */
Middleware::~Middleware()
{
    for (int i = 0; i < myNodeNbr; i++)
    {
        if (!(myStageSymbols.at(i)->IsEffective()))
        {
            delete   myStageSymbols.at(i);
        }
    }
}

/* Initialize or Update the object */
void Middleware::InitORUpdate()
{
    myStatements    = myStates->Statements;
    myInitStateNbr  = 0;

    myGetNodeNumber();
    if (myStates->ProcessFinished())
    {
        myInitNodeInfo();
        myInitStageSymbols();
        myCode2FlowChart();
    }
}

/* Store the number of nodes */
void Middleware::myGetNodeNumber()
{
    myNodeNbr = myStatements.size();

    return;
}

/* Store the node info and Initialize the CurrentBanch */
void Middleware::myInitNodeInfo()
{
    QByteArray ba = myStatements.at(0).StateNumber();
    if ((ba.size()))
    {
        myLastCarctPos = ((ba.size()) - 1);
        myInitStateNbr = (myChar2Int(ba.at(myLastCarctPos)));

        for (int i = 0; i < myNodeNbr; i++)
        {
            Node* node = new Node;
            node->Sequence       = myGetNodeSequence(i);
            node->MaxBranch      = myGetMaxBranchNumber(i);
            node->CurrentBranch  = 0;

            myNodes.append(node);
        }
    }

    return;
}

/* Initialize the myStageSymbols */
void Middleware::myInitStageSymbols()
{
    for (int i = 0; i < myNodeNbr; i++)
    {
        Symbols* sym = new Symbols;
        myStageSymbols.append(sym);
    }

    return;
}

/* Extract the node sequence */
int Middleware::myGetNodeSequence(int i)
{
    if (myStatements.at(0).StateNumber().size())
    {
        return myChar2Int((myStatements.at(i).StateNumber().at(myLastCarctPos)) - myInitStateNbr);
    }
    return 0;
}

/* Extract the node's maximium branch number */
int Middleware::myGetMaxBranchNumber(int i)
{
    States state = myStatements.at(i);
    state.ExtractL2Cntnts();

    return (state.L2Elements().size());
}

/* Convert a char into a integer */
int Middleware::myChar2Int(char ch)
{
    return (ch - 48);
}

/* Function for converting the code into flow chart */
void Middleware::myCode2FlowChart()
{
    /* If there is no effective code */
    if (myNodeNbr == 0)
    {
        return;
    }
    /* If there is just a function xxxxx_f_Call() */
    else if (myNodeNbr == 1)
    {
        QString str;
        myScene->AddStatement(0,0, str, (myStatements.at(0).L1Cntnt()));
        return;
    }
    /* If there are more than one state */
    else
    {
        myLoopBuilding();
    }
}

/* Algorithm for converting the code of states into flow chart with an specific mothed */
void Middleware::myLoopBuilding()
{
    bool        circulation = true;

    Node*       node0       = myNodes.at(0);
    Node*       node1       = NULL;

    Symbols*    stage       = new Symbols;
    Symbols*    statement   = new Symbols;

    qreal       stageX, stageY;
    qreal       stmntX, stmntY;

    bool        node0NotChanged = false;

    do
    {
        /* Get the statement and extract the contents */
        States state = myStatements.at(node0->Sequence);
        state.ExtractL2Cntnts();

        /* If the stage is not drawn */
        if (node0->CurrentBranch == 0)
        {
            myCurrentLoop.append(node0);

            if (statement->IsEffective())
            {
                stageX = ((statement->x()) + (MC_TxtWidth / 2) + 5);
                stageY = ((statement->y()) + (statement->boundingRect().height()) + MC_VerticalSpace);
                //qDebug() << (statement->boundingRect().height());
            }
            else
            {
                stageX = 0;
                stageY = 0;
            }

            stage = myScene->AddStage(stageX,stageY, state.StateNumber());

            /* Release the pre-occupied storage
             * and Replace the pointer with the real, effective pointer */
            delete myStageSymbols.at(node0->Sequence);
            myStageSymbols.replace((node0->Sequence), stage);

            if ((statement->IsEffective()))
            {
                myScene->AddLinkers(statement, stage);
            }
        }
        else
        {
            if (!node0NotChanged)
            {
                myScene->AddLinkers(statement, (myStageSymbols.at(node0->Sequence)));
            }
            else
            {
                node0NotChanged = false;
            }
        }
        /* Draw the statement */
        stmntX = ((myStageSymbols.at(node0->Sequence)->x()) + (MC_StageTxtRect / 2)
                  + (((node0->CurrentBranch) * 4) * MC_HorizontalSpace));
        stmntY = ((myStageSymbols.at(node0->Sequence)->y()) + MC_StageTxtRect + MC_VerticalSpace);

        statement = myScene->AddStatement(stmntX,stmntY,
                                          (state.L2Elements().at(node0->CurrentBranch).Condition),
                                          (state.L2Elements().at(node0->CurrentBranch).Statement));
        myScene->AddLinkers((myStageSymbols.at(node0->Sequence)), statement);

        /* Update current branch */
        node0->CurrentBranch++;

        /* If node0 is not the one node which is the latest on the vector */
        if ((((myCurrentLoop.size()) - 1) >=0)
                && node0 != (myCurrentLoop.at((myCurrentLoop.size()) - 1)))
        {
            myCurrentLoop.append(node0);
        }

        /* If all the conditions of node0 are drawn */
        if ((node0->CurrentBranch) >= (node0->MaxBranch))
        {
            circulation = false;
        }

        /* Determine if there is the next state */
        char ch;
        int nextNodePos;
        if ((state.L2Elements().at((node0->CurrentBranch) - 1).NextState) != "")
        {
            ch = (state.L2Elements().at((node0->CurrentBranch) - 1).NextState.at(myLastCarctPos));
            nextNodePos = ((myChar2Int(ch)) - myInitStateNbr);
        }
        else
        {
            nextNodePos = -1;
        }

        /* If there is the next state */
        if (nextNodePos > 0)
        {
            node1 = myNodes.at(nextNodePos);
            // qDebug() << nextNodePos;
            /* If the current branch of the next state is NOT larger than than current state of the current n0de
             * and it is less than the maximum branch,
             * to update node0 */
            if (((node1->CurrentBranch) <= (node0->CurrentBranch)))
            {
                if ((node1->CurrentBranch) < (node1->MaxBranch))
                {
                    node0 = node1;
                }
                else
                {
                    // node0 = node0;
                    myScene->AddLinkers(statement, (myStageSymbols.at(nextNodePos)));
                    node0NotChanged = true;
                }
            }
            else
            {
                // node0 = node0;
                node0NotChanged = true;
            }

            circulation = true;
        }
        /* Else */
        else
        {
            if (nextNodePos == 0)
            {
                myScene->AddLinkers(statement, (myStageSymbols.at(0)));
            }

            Node* nodeTemp = node0;

            /* Remove the latest node from the vector */
            while (((node0->CurrentBranch) >= (node0->MaxBranch)) && (node0->Sequence != 0))
            {
                int endPos = ((myCurrentLoop.size()) - 1);
                node0 = (myCurrentLoop.at(endPos - 1));
                myCurrentLoop.removeAt(endPos);
            }

            if (node0->Sequence != 0)
            {
                circulation = true;

                if (nodeTemp == node0)
                {
                    node0NotChanged = true;
                }
            }
        }
    }
    while (circulation);
}
