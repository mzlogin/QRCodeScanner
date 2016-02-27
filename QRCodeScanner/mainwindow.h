#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void tryScan();

private:
    void startScan();
    void resetState();

private:
    Ui::MainWindow *ui;

    bool mIsWait;
};

#endif // MAINWINDOW_H
