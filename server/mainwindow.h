#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTcpServer;
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

signals:
    void request();

public slots:
    void onNewConnection();
    void onReadyRead();
    void onResponse(QString res);

private:
    Ui::MainWindow *ui;
    QTcpServer* mServer;
    QTcpSocket* mSocket;
    QTime mTime;
};

#endif // MAINWINDOW_H
