#include "adbthread.h"

adbThread::adbThread(QObject* parent)
{

}

void adbThread::initThread(QString cmd, device d)
{
    command = cmd;
    dev = d;
    explain = false;
}

void adbThread::initThread(QString cmd, device d, QString key)
{
    command = cmd;
    dev = d;
    explain = true;
    explainKey = key;
}

void adbThread::run()
{
    process = new adbProcess();
    //qDebug() << "explainKey is " << explainKey;
    //sleep(3);
    if(explain == false)
    {
        QString output = process->run(command,dev).simplified();
        emit signal_output(output);
        exit();
        //exec();
    }

    else if(explainKey == "#CPU#")
    {
        QString output = explainer->explain_cpu_output(process->run(command, dev));
        emit signal_output(output);
        exit();
    }

    else if(explain == true && explainKey != "#CPU#")
    {
        QString output = explainer->get_words_after(process->run(command, dev), explainKey);
        emit signal_output(output);
        exit();
    }
}
