#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MnWin/cgraphicsview.h"
#include "Painter/Scene/scene.h"
#include "TxtProc/TxtOperation/txtreader.h"
#include "PaintingAlgorithm/middleware.h"
#include <QMainWindow>
#include <QShortcut>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();

    Scene MnWinScene;

private:
    Ui::MainWindow* ui;
    QShortcut*      delShortCut;
    TxtReader*      myTxtObj;
    bool            myCtrlPressed;

    Middleware*     myMiddleware;

    QSystemTrayIcon *trayIcon;

    void            keyPressEvent(QKeyEvent *event);
    void            keyReleaseEvent(QKeyEvent *event);

    void            autoConvertion();

private slots:
    void            on_btnState_clicked();
    void            on_btnLink_clicked();
    void            on_btnStage_clicked();
    void            on_btnDel_clicked();
    void            on_btnUpdate_clicked();

    void            on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
