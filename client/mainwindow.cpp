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

    QTimer* timer1 = new QTimer(this);
    timer1->setInterval(1000);
    connect(timer1,SIGNAL(timeout()),this,SLOT(onTimer1()));
    timer1->start();

    QTimer* timer2 = new QTimer(this);
    timer2->setInterval(5100);
    connect(timer1,SIGNAL(timeout()),this,SLOT(onTimer2()));
    timer2->start();
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
            ui->plainTextEdit->appendPlainText(QString("ping responce in %1ms").arg(mTime1.restart()));
        } else if (msg == "one" || msg == "two" || msg == "three") {
            ui->plainTextEdit->appendPlainText(QString("read responce in %1ms").arg(mTime2.restart()));
            mRequested = false;
        }
    }

}

void MainWindow::onTimer1() {
    mSocket->write("ping\n");
    ui->plainTextEdit->appendPlainText("> ping");
    mTime1.restart();
}

void MainWindow::onTimer2() {

    if (mRequested)
        return;

    mSocket->write("read\n");
    ui->plainTextEdit->appendPlainText("> read");
    mTime2.restart();

    mRequested = true;
}
