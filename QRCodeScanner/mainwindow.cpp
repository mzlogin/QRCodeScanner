#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include "../qzxing/qzxing.h"

#ifndef Q_OS_WIN32
#define TMP_FILE_PATH "/tmp/qrcode-scanner-tmp.jpg"
#else
#define TMP_FILE_PATH "qrcode-scanner-tmp.jpg"
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mIsWait(true)
{
    // transparent background
    setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);

    ui->statusBar->hide();
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    // TODO: implement responsibility layout and remove the below line
    setFixedSize(width(), height());

    connect(ui->startScan, SIGNAL(clicked()), this, SLOT(tryScan()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tryScan()
{
    if (mIsWait) {
        startScan();
    } else {
        resetState();
    }
}

void MainWindow::startScan()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPoint pos = QWidget::mapToGlobal(this->rect().topLeft());
    int x = pos.x();
    int y = pos.y();
    int w = this->width() / screen->devicePixelRatio();
    int h = this->height() / screen->devicePixelRatio();

    const QString& tmp = TMP_FILE_PATH;
    const char* fmt = "JPG";

    QPixmap pixmap = screen->grabWindow(QApplication::desktop()->winId(), x, y, w, h);
    pixmap.save(tmp, fmt);

    QImage img;
    img.load(tmp, fmt);
    QZXing zxing;
    QString decode = zxing.decodeImage(img);
    if (!decode.isEmpty()) {
        mIsWait = false;
        ui->scanArea->setStyleSheet("background:rgba(255,255,255,255);");
        ui->scanArea->setText(decode);
        ui->scanArea->setEnabled(true);
        ui->startScan->setText("Scan More");
    }
}

void MainWindow::resetState()
{
    ui->scanArea->setStyleSheet("background: rgba(255,255,255,0);");
    ui->scanArea->setText("");
    ui->scanArea->setEnabled(false);
    ui->startScan->setText("Start Scan");

    mIsWait = true;
}
