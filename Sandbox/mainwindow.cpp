#include "mainwindow.h"
#include "lifewidget.h"
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LifeWidget *lifeWidget = new LifeWidget(this);
    setCentralWidget(lifeWidget);

    QToolBar *toolBar = addToolBar("Controls");
    QAction *clearAction = toolBar->addAction("Clear");
    QAction *randomizeAction = toolBar->addAction("Randomize");
    QAction *pauseAction = toolBar->addAction("Pause");
    QAction *resumeAction = toolBar->addAction("Resume");

    connect(clearAction, &QAction::triggered, lifeWidget, &LifeWidget::clear);
    connect(randomizeAction, &QAction::triggered, lifeWidget, &LifeWidget::randomize);
    connect(pauseAction, &QAction::triggered, lifeWidget, &LifeWidget::pause);
    connect(resumeAction, &QAction::triggered, lifeWidget, &LifeWidget::resume);

    setWindowTitle("Conway's Game of Life");
}
