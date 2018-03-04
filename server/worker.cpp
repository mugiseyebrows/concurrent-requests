#include "worker.h"

#include "thread.h"

#include <cstdlib>
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    mResponses << "one" << "two" << "three";
    mIndex = 0;
}

void Worker::onRequest()
{
    int ms = (rand() % 1000) + 1000;
    //qDebug() << ms;
    Thread::msleep(ms);
    emit response(mResponses[mIndex++ % mResponses.size()]);
}
