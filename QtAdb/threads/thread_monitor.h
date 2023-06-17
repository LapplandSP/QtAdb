#ifndef THREAD_MONITOR_H
#define THREAD_MONITOR_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "../adbprocess.h"


class thread_monitor  : public QThread
{
    Q_OBJECT

public:
    thread_monitor(device dev);
    adbProcess *process;
    textExplainer *explainer;
    //QTimer *timer;

    device dev;

    QString cpu_t1 = "#FIRSTBOOT#";
    QString cpu_t2;
    QString mem;

signals:
    void signal_output(QString);
    void signal_monitor(float,float);

protected:
    void run() override;

public slots:
    void getInfo();
};

#endif // THREAD_MONITOR_H
