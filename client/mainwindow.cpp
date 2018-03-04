#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QTcpSocket>

#include <QHostAddress>
#include <QTimer>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mRequested(false)
{
    ui->setupUi(this);

    mSocket = new QTcpSocket();
    mSocket->connectToHost(QHostAddress("127.0.0.1"),3000);
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    QTimer* timerPing = new QTimer(this);
    timerPing->setInterval(1000);
    connect(timerPing,SIGNAL(timeout()),this,SLOT(onTimer1()));
    timerPing->start();

    QTimer* timerRead = new QTimer(this);
    timerRead->setInterval(3100);
    connect(timerRead,SIGNAL(timeout()),this,SLOT(onTimer2()));
    timerRead->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead() {

    QTextCodec* c = QTextCodec::codecForName("utf-8");
    QStringList msgs = c->toUnicode(mSocket->readAll()).split("\n");
    QString msg;

    foreach(msg,msgs) {
        if (msg.isEmpty())
            continue;

        ui->plainTextEdit->appendPlainText("< " + msg);
        if (msg == "pong") {
            ui->plainTextEdit->appendPlainText(QString("ping response in %1ms").arg(mTimePing.restart()));
        } else if (msg == "one" || msg == "two" || msg == "three") {
            ui->plainTextEdit->appendPlainText(QString("read response in %1ms").arg(mTimeRead.restart()));
            mRequested = false;
        } else {
            qDebug() << "unknown message" << msg;
        }
    }

}

void MainWindow::onTimer1() {
    mSocket->write("ping\n");
    ui->plainTextEdit->appendPlainText("> ping");
    mTimePing.restart();
}

void MainWindow::onTimer2() {

    if (mRequested)
        return;

    mSocket->write("read\n");
    ui->plainTextEdit->appendPlainText("> read");
    mTimeRead.restart();

    mRequested = true;
}
