#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>
#include "worker.h"
#include <QTextCodec>
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mServer = new QTcpServer(this);
    connect(mServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    mServer->listen(QHostAddress::Any, 3000);

    Worker* mWorker = new Worker();

    connect(this,SIGNAL(request()),mWorker,SLOT(onRequest()));
    connect(mWorker,SIGNAL(response(QString)),this,SLOT(onResponse(QString)));

    QThread* thread = new QThread();

    mWorker->moveToThread(thread);

    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection() {
    mSocket = mServer->nextPendingConnection();
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}



void MainWindow::onReadyRead() {

    QTextCodec* c = QTextCodec::codecForName("utf-8");

    QStringList msgs = c->toUnicode(mSocket->readAll()).split("\n");
    QString msg;

    foreach(msg,msgs) {

        if (msg.isEmpty())
            continue;

        ui->plainTextEdit->appendPlainText("< " + msg);
        if (msg == "ping") {
            mSocket->write("pong\n");
            ui->plainTextEdit->appendPlainText("> pong");
        } else if (msg == "read") {
            emit request();
            mTime.restart();
        } else {
            qDebug() << "unknown message" << msg;
        }
    }
}

void MainWindow::onResponse(QString res) {
    QTextCodec* c = QTextCodec::codecForName("utf-8");
    mSocket->write(c->fromUnicode(res));
    mSocket->write("\n");
    ui->plainTextEdit->appendPlainText("> " + res);
    qDebug() << "responsed in" << mTime.restart() << "ms";
}
