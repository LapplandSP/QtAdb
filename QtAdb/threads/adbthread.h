#ifndef ADBTHREAD_H
#define ADBTHREAD_H
#include <QThread>
#include "../textexplainer.h"
#include "../adbprocess.h"
#include <Windows.h>

class adbThread : public QThread
{
    Q_OBJECT
public:
    explicit adbThread(QObject* parent = nullptr);

    void initThread(QString cmd, device dev);
    void initThread(QString cmd, device dev, QString explainKey);
    void initThread_for_cpu(QString cmd, device dev);
    bool explain = false;
    QString command;
    QString explainKey;
    device dev;

    adbProcess *process;
    textExplainer *explainer;

signals:
    void signal_output(QString);

public slots:
    //static void myThreadSlot(int);

protected:
    void run() override;
};

#endif // ADBTHREAD_H
