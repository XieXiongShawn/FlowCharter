#include "txtreader.h"
#include <QFile>
#include <QDebug>

/* Construct an object */
TxtReader::TxtReader()
{
}

/* Construct an object with file path */
TxtReader::TxtReader(QString &path)
{
    myPath = path;

    ReadTxt();
}

/* Read the content of file */
void TxtReader::ReadTxt()
{
    QFile txtFile(myPath);

    if (txtFile.exists())
    {
        if (txtFile.open(QFile::ReadOnly))
        {
            TxtContent = txtFile.readAll();
            //qDebug() << TxtContent;

            if (TxtContent.isEmpty())
            {
                qDebug() << "Empty File";
            }
            else
            {
                TxtProxer.SetTxtContent(TxtContent);    // Transmit text to txt percessor
            }
        }
    }
    else
    {
        qDebug() << "File Not Exists";
    }

    return;
}

/* Determine if the content is empty */
bool TxtReader::IsEmpty()
{
    return (TxtContent.isEmpty());
}

/* Return whether the process is finished */
bool TxtReader::ProcessFinished()
{
    return TxtProxer.ProcessFinished();
}

/* Set file path */
void TxtReader::SetPath(QString &path)
{
    myPath = path;
    ReadTxt();

    return;
}

/* Show file path */
QString TxtReader::ShowPath()
{
    return myPath;
}
