#ifndef STATES_H
#define STATES_H

#include "TxtProc/CodeExtractor/codeextractor.h"
#include <QString>
#include <QVector>

struct ST_L2Element
{
    int                     Pos;
    QByteArray              Condition;
    QByteArray              Statement;
    QByteArray              NextState;
};

class States
{
public:
    States();

    void                    SetL1Pos(int pos);
    void                    SetL1Cntnt(QByteArray cntnt);
    void                    SetStateSuffix(QByteArray sfx);

    int                     L1Pos() const;
    QByteArray              L1Cntnt() const;

    QVector<ST_L2Element>   L2Elements() const;
    void                    ExtractL2Cntnts();
    bool                    hasL2Cntnt();

    QByteArray              StateNumber() const;


private:
    CodeExtractor           myHuntMaster;

    QByteArray              myStateNumber;

    int                     myL1Pos;
    QByteArray              myL1Cntnt;

    QByteArray              myStateSuffix;

    QVector<ST_L2Element>   myL2Lmts;
};

#endif // STATES_H
