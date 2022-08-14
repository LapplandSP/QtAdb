#ifndef ADBTHREAD_H
#define ADBTHREAD_H
#include <QThread>
#include <QTimer>
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
    void initThread_timer(QString cmd, device dev);
    //void initThread(QString cmd, device dev);
    bool explain = false;
    bool timer = false;
    QString command;
    QString explainKey;
    device dev;
    QTimer *refreshTimer;

    adbProcess *process;
    textExplainer *explainer;

    QString str_result = "#NORESULTS#";
signals:
    void signal_output(QString);
    void regularResult(QString);

public slots:
    void result(QString);
    void updateResult(int,QProcess::ExitStatus);
    void sendResult();
    //void timerEnd();

protected:
    void run() override;
};

#endif // ADBTHREAD_H
