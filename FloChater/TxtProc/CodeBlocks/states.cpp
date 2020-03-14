#include "states.h"
#include <QDebug>

/* Construct an object */
States::States()
{
}

/* Store the position of Level-1 content with given int */
void States::SetL1Pos(int pos)
{
    myL1Pos = pos;

    return;
}

/* Set Level-1 content with given QByteArray */
void States::SetL1Cntnt(QByteArray cntnt)
{
    myL1Cntnt = cntnt;
    myHuntMaster.SetTxt(myL1Cntnt); // Store the content for myHuntMaster

    return;
}

/* Store the state suffix of Level-1 content */
void States::SetStateSuffix(QByteArray sfx)
{
    myStateSuffix = sfx;            // sfx is "_f_x_x_x_x"
    myStateSuffix.remove(0, 3);     // Remove "_f_"
    myStateNumber = myStateSuffix;  // Store the state number "x_x_x_x"
    myStateSuffix.chop(1);          // Remove the last number (actual state number), "x_x_x_"

    return;
}

/* Return the position information of Level-1 content */
int States::L1Pos() const
{
    return myL1Pos;
}

/* Return Level-1 content */
QByteArray States::L1Cntnt() const
{
    return myL1Cntnt;
}

/* Return Level-2 elements (all the Level-2 content) */
QVector<ST_L2Element> States::L2Elements() const
{
    return myL2Lmts;
}

/* Generate Level-2 element by character extraction */
void States::ExtractL2Cntnts()
{
    if (myL1Cntnt.contains("if"))
    {
        int fromPos         = 0;
        int endPos          = 0;
        int suffixSize      = myStateSuffix.size();
        do
        {
            ST_L2Element element;

            endPos              = (myL1Cntnt.indexOf("NEXTSTATE", fromPos));
            while ((myL1Cntnt.at(endPos - 1)) != ' ')
            {
                endPos--;
            }

            /* Get the state number which should be jumped to, "x_x_x_" + "x" */
            element.NextState   = (myStateSuffix +
                                   (myL1Cntnt.at(myL1Cntnt.indexOf("STATE_", (endPos + 9)) + 6 + suffixSize)));

            element.Condition   = myHuntMaster.ExtractCode(fromPos, endPos, '(');
            fromPos             += element.Condition.size();

            element.Statement   = myHuntMaster.ExtractCode(fromPos, endPos, '{');
            fromPos             += element.Statement.size();

            element.Pos         = myL1Cntnt.indexOf("if", fromPos);
            fromPos             = element.Pos;

            myL2Lmts.append(element);
        }
        while (fromPos > endPos);
    }
    else
    {
        int endPos = 0;
        ST_L2Element element;

        endPos              = myL1Cntnt.indexOf("NEXTSTATE", 0);
        /* Get the state number which should be jumped to, "x_x_x_" + "x" */
        if (endPos != (-1))
        {
            element.NextState   = (myStateSuffix +
                                    (myL1Cntnt.at(myL1Cntnt.indexOf(myStateSuffix, endPos) + myStateSuffix.size())));
        }
        else
        {
            element.NextState = "";
        }

        element.Pos         = 0;

        element.Condition   = "";

        element.Statement   = ((myL1Cntnt.remove(endPos, myL1Cntnt.size())).trimmed());

        myL2Lmts.append(element);
    }

    return;
}

/* Return that whether Level-2 content was extracted */
bool States::hasL2Cntnt()
{
    /* If myL2Lmts is empty or Level-2 content was not extracted, extract (again) */
    if (myL2Lmts.isEmpty())
    {
        ExtractL2Cntnts();
    }

    return (!(myL2Lmts.isEmpty()));
}

/* Return state number */
QByteArray States::StateNumber() const
{
    return myStateNumber;
}
