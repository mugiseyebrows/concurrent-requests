#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QStringList>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    
protected:
    QStringList mResponces;
    int mIndex;

signals:
    
    void responce(QString);

public slots:

    void onRequest();

};

#endif // WORKER_H
