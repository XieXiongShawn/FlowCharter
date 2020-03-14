#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

/* Construct the main window */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":icons/icon.jpg"));
}

/* Deconstruct the object */
MainWindow::~MainWindow()
{
    delete ui;

    if (myMiddleware)
    {
        delete myMiddleware;
    }

    if (myTxtObj)
    {
        delete myTxtObj;
    }
}

/* Initialization the user interface */
void MainWindow::init()
{
    myTxtObj = new TxtReader;
    myMiddleware = new Middleware(&MnWinScene, myTxtObj);
    myCtrlPressed = false;

    this->setWindowTitle("FloChater");

    ui->graphicsView->setScene(MnWinScene.GScene);
    //ui->graphicsView->setSceneRect(-1000,-1000, 2000,2000);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    ui->btnDel->setShortcut(Qt::Key_Delete);
}

/* Reimplement keyPressEvent() for shortcuts of menu option.
    When there is a need to configurate shortcut for pushbutton and menu option,
    Qt4.8 cannot configurate shortcut correctly */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);

    if (event->key() == (Qt::Key_Control))
    {
        myCtrlPressed = true;
    }
    if (myCtrlPressed && (event->key() == Qt::Key_O))
    {
        on_actionOpen_triggered();
    }
}

/* Reimplement keyReleaseEvent() */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    QMainWindow::keyReleaseEvent(event);

    myCtrlPressed = false;
}

/* Function call for btnState clicking */
void MainWindow::on_btnState_clicked()
{
    MnWinScene.AddStatement(0, 0);
}

/* Function call for btnLink clicking */
void MainWindow::on_btnLink_clicked()
{
    MnWinScene.AddLinkers();
}

/* Function call for btnStage clicking */
void MainWindow::on_btnStage_clicked()
{
    MnWinScene.AddStage(0, 0);
}

/* Function call for btnDel clicking */
void MainWindow::on_btnDel_clicked()
{
    MnWinScene.DeleteItems();
}

/* Function call for btnUpdate clicking (Update the scene wholly) */
void MainWindow::on_btnUpdate_clicked()
{
    MnWinScene.GScene->update();
}

/* Function call for menu open */
void MainWindow::on_actionOpen_triggered()
{

    MnWinScene.ClearScene();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Code..."),
                                              NULL, tr("*.c"));

    if (!(fileName.isEmpty()))
    {
        myTxtObj->SetPath(fileName);
    }

    autoConvertion();
}

/* Function call for painting according to text process result */
void MainWindow::autoConvertion()
{
    if (!(myTxtObj->IsEmpty()))
    {
        myMiddleware->InitORUpdate();
    }

    return;
}
