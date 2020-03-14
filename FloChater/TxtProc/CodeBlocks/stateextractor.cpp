#include "stateextractor.h"
#include <QDebug>

/* Construct an object */
StateExtractor::StateExtractor()
{
    myProcessFinished = false;
}

/* Set txt content with given QByteArray */
void StateExtractor::SetTxtContent(QByteArray &txtCntnt)
{
    myTxtCntnt = txtCntnt;
    myHuntMaster.SetTxt(myTxtCntnt);    // Transmit content to myHuntMaster
    myProcessFinished = false;

    myTxtProxer();

    return;
}

/* Return the case count */
int StateExtractor::CaseCount()
{
    return (Cases.size());
}

/* Return the statement count */
int StateExtractor::StatementCount()
{
    return (Statements.size());
}

/* Return whether the process is finished */
bool StateExtractor::ProcessFinished()
{
    return myProcessFinished;
}

/* The first step to process the txt content */
void StateExtractor::myTxtProxer()
{
    myProcessFinished = false;

    Cases.clear();
    Statements.clear();

    if (myTxtCntnt.contains("case"))
    {
        myCaseHunter();
    }
    else
    {
        myFCallHunter();
    }

    myProcessFinished = true;

    return;
}

/* Search and Store all the "case" in txt content */
void StateExtractor::myCaseHunter()
{
    int posTemp = 0;
    do
    {
        States rs;
        rs.SetL1Pos(myTxtCntnt.indexOf("case", posTemp));

        if (posTemp > rs.L1Pos())   // Finish search after one txt process cycle
        {
            break;
        }
        posTemp = (rs.L1Pos() + 9);

        char ch;
        do
        {
            ch = myTxtCntnt.at(++posTemp);  // To find out the start of "_x_x_x_x"
        }
        while (ch != '_');

        QByteArray strTemp = "_f";
        do
        {
            strTemp.append(myTxtCntnt.at(posTemp++));   // To get the entire state number *_f_x_x_x_x

        }
        while (((myTxtCntnt.at(posTemp)) != ':') && ((myTxtCntnt.at(posTemp)) != ' '));
        //qDebug() << strTemp;
        rs.SetL1Cntnt(strTemp);

        myStateHunter(rs);

        Cases.append(rs);
    }
    while (myTxtCntnt.indexOf("case", posTemp));

    return;
}

/* Search and store all the state and its code */
void StateExtractor::myStateHunter(States &src)
{
    States rs;
    rs.SetL1Pos(myTxtCntnt.lastIndexOf(src.L1Cntnt(), src.L1Pos()));
    rs.SetL1Cntnt(myHuntMaster.ExtractCode(rs.L1Pos()));
    rs.SetStateSuffix(src.L1Cntnt());

    Statements.append(rs);

    return;
}

/* Search and store the code of ..f_Call */
void StateExtractor::myFCallHunter()
{
    States rs;
    rs.SetL1Pos(myTxtCntnt.indexOf("f_Call"));
    rs.SetL1Cntnt(myHuntMaster.ExtractCode(rs.L1Pos()));

    Statements.append(rs);

    return;
}
