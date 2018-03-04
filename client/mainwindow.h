#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTcpSocket;
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTcpSocket* mSocket;

    QTime mTimePing;
    QTime mTimeRead;
    bool mRequested;

private slots:
    void onReadyRead();
    void onTimerPing();
    void onTimerRead();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
