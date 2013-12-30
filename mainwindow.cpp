#include "mainwindow.h"

MainWindow::MainWindow() :
    QMainWindow()
{
    // ===========
    // == Menus ==
    // ===========

    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("É&dition");

        QMenu *menuNvFenetre = new QMenu("&Nouvelle Fenêtre");
        menuFichier->addMenu(menuNvFenetre);

        QAction *actionNewSubWindowObjetTombe = new QAction("&Objet qui &tombe",this);
        menuNvFenetre->addAction(actionNewSubWindowObjetTombe);

        QAction *actionNewSubWindowSuitCourbe = new QAction("Objet suivant une &courbe",this);
        menuNvFenetre->addAction(actionNewSubWindowSuitCourbe);

        QAction *actionNewSubWindowSpring = new QAction("&Ressort", this);
        menuNvFenetre->addAction(actionNewSubWindowSpring);

    QAction *actionQuitter = new QAction("&Quitter",this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    menuFichier->addAction(actionQuitter);

    menuAffichage = menuBar()->addMenu("&Affichage");

        QAction *actionToggleTabView = new QAction("Vue en &onglets",this);
        actionToggleTabView->setCheckable(true);
        actionToggleTabView->setChecked(false);
        menuAffichage->addAction(actionToggleTabView);

        QAction *actionCascade = new QAction("&Cascade",this);
        menuAffichage->addAction(actionCascade);


    connect(actionNewSubWindowObjetTombe, SIGNAL(triggered()), this, SLOT(newFallingObjectSubWindow()));
//    connect(actionNewSubWindowSuitCourbe, SIGNAL(triggered()), this, SLOT(newCurveFollowingObjectSubWindow()));
    connect(actionNewSubWindowSpring, SIGNAL(triggered()), this, SLOT(newSpringSubWindow()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(actionToggleTabView, SIGNAL(toggled(bool)), this, SLOT(enableTabView(bool)));
    connect(actionToggleTabView, SIGNAL(toggled(bool)), actionCascade, SLOT(setDisabled(bool)));

    connect(actionCascade, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    // ================
    // == SubWindows ==
    // ================

    zoneCentrale = new QMdiArea;

    setCentralWidget(zoneCentrale);
}

void MainWindow::newFallingObjectSubWindow() {
    FallingObjectMdiSubWindow *newSubWindow = new FallingObjectMdiSubWindow;
    zoneCentrale->addSubWindow(newSubWindow);
    newSubWindow->show();
    newSubWindow->activateAnimation();
}

void MainWindow::newCurveFollowingObjectSubWindow() {

}

void MainWindow::newSpringSubWindow() {
    SpringMdiSubWindow *newSubWindow = new SpringMdiSubWindow;
    zoneCentrale->addSubWindow(newSubWindow);
    newSubWindow->show();
}

void MainWindow::enableTabView(bool ena) {
    if(ena)
        zoneCentrale->setViewMode(QMdiArea::TabbedView);
    else
        zoneCentrale->setViewMode(QMdiArea::SubWindowView);
}

void MainWindow::cascadeSubWindows() {
    this->zoneCentrale->cascadeSubWindows();
}
