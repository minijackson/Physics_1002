#include "springmdisubwindow.h"

SpringMdiSubWindow::SpringMdiSubWindow(QWidget *parent) :
    QMdiSubWindow(parent)
{
    this->setWindowTitle("Objet tombant");

    spring = new GraphicsSpringItem(50, 200, 10, 0.9, 1, 0.62, Qt::black); // 0.62 = friction coefficient of concrete wood
    ball = new DragDropBallGraphicsItem(10, 10, 200, 0, false, true, spring);

    graphicsScene = new QGraphicsScene(this);
    graphicsScene->addItem(spring);
    graphicsScene->addItem(ball);
    graphicsView = new QGraphicsView(graphicsScene);
    graphicsView->setGeometry(0,0,700,700);
//    graphicsView->setFixedSize(550,550);

    QWidget *zoneCentrale = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *controllerLayout = new QHBoxLayout();
    controllerLayout->addWidget(new QLabel("Constante de raideur"));
    QDoubleSpinBox *springConstantControllerSlider = new QDoubleSpinBox();
    springConstantControllerSlider->setRange(0.01, 0.99);
    springConstantControllerSlider->setDecimals(2);
    springConstantControllerSlider->setSingleStep(0.05);
    springConstantControllerSlider->setValue(0.9);
    controllerLayout->addWidget(springConstantControllerSlider);

    controllerLayout->addWidget(new QLabel("Coefficient de frottement"));
    QDoubleSpinBox *frictionConstantControllerSlider = new QDoubleSpinBox();
    frictionConstantControllerSlider->setRange(0,1.5);
    frictionConstantControllerSlider->setDecimals(2);
    frictionConstantControllerSlider->setSingleStep(0.1);
    frictionConstantControllerSlider->setValue(0.62);
    controllerLayout->addWidget(frictionConstantControllerSlider);

    controllerLayout->addWidget(new QLabel("Masse de l'objet"));
    QDoubleSpinBox *objectMassControllerSlider = new QDoubleSpinBox();
    objectMassControllerSlider->setRange(0.1,10);
    objectMassControllerSlider->setDecimals(1);
    objectMassControllerSlider->setSingleStep(0.1);
    objectMassControllerSlider->setValue(1);
    controllerLayout->addWidget(objectMassControllerSlider);

    mainLayout->addLayout(controllerLayout);
    mainLayout->addWidget(graphicsView);

    zoneCentrale->setLayout(mainLayout);

    this->setGeometry(0,0,700,600);
    this->setWidget(zoneCentrale);

    connect(ball, SIGNAL(dragStart()), spring, SLOT(stopAnimation()));
    connect(ball, SIGNAL(dragEnd()), spring, SLOT(startAnimation()));
    connect(ball, SIGNAL(dragMove(QPointF)), spring, SLOT(updateSpring(QPointF)));

    connect(springConstantControllerSlider, SIGNAL(valueChanged(double)), spring, SLOT(setSpringConstant(double)));
    connect(frictionConstantControllerSlider, SIGNAL(valueChanged(double)), spring, SLOT(setFrictionConstant(double)));
    connect(objectMassControllerSlider, SIGNAL(valueChanged(double)), spring, SLOT(setObjectMass(double)));

    connect(spring, SIGNAL(springGeometryAnimationChange(int)), ball, SLOT(moveX(int)));
}
