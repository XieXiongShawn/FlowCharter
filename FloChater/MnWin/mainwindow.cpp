#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

/* Construct the main window */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/* Deconstruct the object */
MainWindow::~MainWindow()
{
    delete ui;
}

/* Initialization the user interface */
void MainWindow::init()
{
    myCtrlPressed = false;

    this->setWindowTitle("FloCharter");

    ui->graphicsView->setScene(MnWinScene.GScene);
    ui->graphicsView->setSceneRect(-1000,-1000, 2000,2000);
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

/* Function for btnState clicking */
void MainWindow::on_btnState_clicked()
{
    MnWinScene.AddStatement(0, 0);
}

/* Function for btnStage clicking */
void MainWindow::on_btnStage_clicked()
{
    MnWinScene.AddStage(0, 0);
}

/* Function for btnLink clicking */
void MainWindow::on_btnLink_clicked()
{
    MnWinScene.AddLinkers();
}

/* Function for btnDel clicking */
void MainWindow::on_btnDel_clicked()
{
    MnWinScene.DeleteItems();
}

/* Function for btnUpdate clicking (Update the scene wholly) */
void MainWindow::on_btnUpdate_clicked()
{
    MnWinScene.GScene->update();
}

/* Function for menu open */
void MainWindow::on_actionOpen_triggered()
{
    MnWinScene.ClearScene();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Code..."),
                                              tr("/home/william/Desktop/src"), tr("*.c"));
    if (!(fileName.isEmpty()))
    {
        //myTxtObj->SetPath(fileName);
    }

    autoConvertion();
}

/* Function for menu Help */
void MainWindow::on_actionHelp_triggered()
{
    QString context;
    context.append("'State'");
    context.append('\t');
    context.append("Add a rectangle");
    context.append('\n');

    context.append("'Stage'");
    context.append('\t');
    context.append("Add a circle");
    context.append('\n');

    context.append("'Link'");
    context.append('\t');
    context.append("Add two selected items");
    context.append('\n');

    context.append("'Delete'");
    context.append('\t');
    context.append("Delete the selected items");
    context.append('\n');

    context.append("'Update'");
    context.append('\t');
    context.append("Update the scene");
    context.append('\n');

    QMessageBox::information(this, tr("Help"), context);
}

/* Function for menu About */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"), tr("Version: 00.01"));
}

/* Function for painting according to text process result */
void MainWindow::autoConvertion()
{
    /*
    if (!(myTxtObj->IsEmpty()))
    {
        myMiddleware->InitORUpdate();
    }
    */

    return;
}
