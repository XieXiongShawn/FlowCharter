#include "codeextractor.h"
#include <QDebug>

/* Construct an object */
CodeExtractor::CodeExtractor()
{
}

/* Set txt content with given QByteArray */
void CodeExtractor::SetTxt(QByteArray &txt)
{
    myTxt = txt;

    return;
}

/* Extract code with default parameter, except start postion or boundary symbol */
QByteArray CodeExtractor::ExtractCode(int pos, char sym)
{
    return ExtractCode(pos, (myTxt.size() - 1), sym);
}

/* Extract code with given start position, end position and boundary symbol */
QByteArray CodeExtractor::ExtractCode(int fromPos, int endPos, char sym)
{
    bool        processing  = true;
    bool        extracting  = false;
    QByteArray  tempCntnt   = NULL;
    int         prncsCnt    = 0;

    /* Determine the reverse boundary symbol */
    char    rSym;
    if (sym == '{')
    {
        rSym = '}';
    }
    else if (sym == '(')
    {
        rSym = ')';
    }
    else
    {
        qDebug() << "The Symbol Should Be Filtered Is Not '{' Nor '(' ";
    }

    while (processing)
    {
        QChar ch = myTxt.at(++fromPos);

        if ((ch == sym))
        {
            ++prncsCnt;

            if (prncsCnt == 1)
            {
                ch = myTxt.at(++fromPos); //If first left boundary was found, skip the boundary character
                if (ch == sym)
                {
                    ++prncsCnt;
                }
            }
        }
        else if (ch == rSym)
        {
            --prncsCnt;

            /* If the given code is wrong with a missing leftboundary */
            if (prncsCnt < 0)
            {
                qDebug() << "Detected '}' before '{' ";

                processing = false;
            }
        }

        /* To determine whether to start the extract or finish extraction */
        if ((!extracting) && prncsCnt)
        {
            extracting = true;
        }
        else if (extracting && (!prncsCnt))
        {
            extracting = false;

            processing = false;
        }

        /* If annotation symbole "/" was found, ignore the annotation */
        if (ch == '/')
        {
            /* get the new fromPos which is after the annotation*/
            fromPos = myAnnotationSkip(fromPos);

            ch = myTxt.at(++fromPos);
            if (ch == sym)
            {
                ++prncsCnt;
            }
            else if (ch == rSym)
            {
                --prncsCnt;
            }
        }

        /* To finish the extraction */
        if (fromPos >= (endPos - 1))
        {
            extracting = false;

            processing = false;
        }

        /* Store the effective code */
        if (extracting && prncsCnt)
        {
            tempCntnt.append(ch);
        }
    }

    /* Simplify the statements */
    return (myCntntSimplification(tempCntnt));
}

/* Annotation skipper */
int CodeExtractor::myAnnotationSkip(int pos)
{
    char ch = myTxt.at(++pos);

    if (ch == '*')
    {
        pos = (myTxt.indexOf("*/", pos));
        pos = (myTxt.indexOf('\n', pos));

        return pos;
    }
    else if (ch == '/')
    {
        while (true)
        {
            if (myTxt.at(++pos) == '\n')
            {
                return --pos;
            }
        }
    }

    return pos;
}

/* Simplify the given QByteArray */
QByteArray CodeExtractor::myCntntSimplification(QByteArray &str)
{
    QByteArray  returnStr = str.trimmed().simplified().append(" ");

    for (int i = 1; i < returnStr.size(); i++)
    {
        QChar ch1 = returnStr.at(i - 1);
        QChar ch2 = returnStr.at(i);
        if ((ch1 == ";") && (ch2.isSpace()))
        {
            returnStr.insert(i + 1, "\n");
            ++i;
        }
    }

    return returnStr.trimmed();
}

/* Determine if the given char-type variable is a space character */
bool CodeExtractor::myIsSpace(const char c)
{
    if ((c == ' ') && (c == '\n') && (c == '\t'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
