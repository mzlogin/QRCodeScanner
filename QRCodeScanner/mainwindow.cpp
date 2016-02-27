#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // transparent background
    setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);

    ui->statusBar->hide();
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    // TODO: implement responsibility layout and remove the below line
    setFixedSize(width(), height());

    connect(ui->startScan, SIGNAL(clicked()), this, SLOT(startScan()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startScan()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPoint pos = QWidget::mapToGlobal(this->rect().topLeft());
    int x = pos.x();
    int y = pos.y();
    int w = this->width() / screen->devicePixelRatio();
    int h = this->height() / screen->devicePixelRatio();

    QPixmap pixmap = screen->grabWindow(QApplication::desktop()->winId(), x, y, w, h);

    QLabel *ql = new QLabel();
    ql->setPixmap(pixmap);
    ql->show();
}
