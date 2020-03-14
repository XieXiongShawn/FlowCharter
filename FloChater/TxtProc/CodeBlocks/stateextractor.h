#ifndef STATEEXTRACTOR_H
#define STATEEXTRACTOR_H

#include "states.h"
#include "TxtProc/CodeExtractor/codeextractor.h"
#include <QByteArray>

class StateExtractor
{
public:
    StateExtractor();

    void            SetTxtContent(QByteArray &txtCntnt);

    QVector<States> Cases;
    QVector<States> Statements;
    int             CaseCount();
    int             StatementCount();

    bool            ProcessFinished();

private:
    CodeExtractor   myHuntMaster;

    QByteArray      myTxtCntnt;
    bool            myProcessFinished;

    void            myTxtProxer();

    void            myCaseHunter();
    void            myStateHunter(States &src);
    void            myFCallHunter();
};

#endif // STATEEXTRACTOR_H
