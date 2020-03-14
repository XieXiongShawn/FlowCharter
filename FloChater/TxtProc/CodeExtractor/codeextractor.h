#ifndef CODEEXTRACTOR_H
#define CODEEXTRACTOR_H

#include <QByteArray>

class CodeExtractor
{
public:
    CodeExtractor();

    void        SetTxt(QByteArray &txt);

    QByteArray  ExtractCode(int pos, char sym='{');
    QByteArray  ExtractCode(int fromPos, int endPos, char sym='{');

private:
    QByteArray  myTxt;

    int         myAnnotationSkip(int pos);
    QByteArray  myCntntSimplification(QByteArray &str);
    bool        myIsSpace(const char c);
};

#endif // CODEEXTRACTOR_H
