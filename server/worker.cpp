#include "worker.h"

#include "thread.h"

#include <cstdlib>
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    mResponces << "one" << "two" << "three";
    mIndex = 0;
}

void Worker::onRequest()
{
    int ms = (rand() % 1000) + 1000;
    //qDebug() << ms;
    Thread::msleep(ms);
    emit responce(mResponces[mIndex++ % mResponces.size()]);
}
