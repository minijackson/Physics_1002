#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fallingobjectmdisubwindow.h"
#include "springmdisubwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QKeySequence>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QWidget>
#include <QHash>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    
public slots:
    void newFallingObjectSubWindow();
    void newCurveFollowingObjectSubWindow();
    void newSpringSubWindow();

    void enableTabView(bool ena);
    void cascadeSubWindows();

private:
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;

    QMdiArea *zoneCentrale;

    QTimeLine *calcFallingObject(QGraphicsItem *ellipse);
};

#endif // MAINWINDOW_H
