#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
    static void msleep(unsigned long msecs) {
        QThread::msleep(msecs);
    }
    static void usleep(unsigned long usecs) {
        QThread::usleep(usecs);
    }

signals:
    
public slots:
    
};

#endif // THREAD_H
