#ifndef TXTREADER_H
#define TXTREADER_H

#include "TxtProc/CodeBlocks/stateextractor.h"
#include <QString>

class TxtReader
{
public:
    TxtReader();
    TxtReader(QString &path);

    void            ReadTxt();
    bool            IsEmpty();
    bool            ProcessFinished();

    void            ShowTxt();
    void            SetPath(QString &path);
    QString         ShowPath();

    QByteArray      TxtContent;
    StateExtractor  TxtProxer;

private:
    QString         myPath;
};

#endif // TXTREADER_H
