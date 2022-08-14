#include "adbthread.h"

adbThread::adbThread(QObject* parent)
{
    setParent(parent);
}

void adbThread::initThread(QString cmd, device d)
{
    command = cmd;
    dev = d;
    explain = false;
}

void adbThread::initThread_timer(QString cmd, device d)
{
    //refreshTimer = new QTimer(this);
    //connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(updateResult(int,QProcess::ExitStatus)));
    command = cmd;
    dev = d;
    explain = false;
    //timer = true;
}

void adbThread::initThread(QString cmd, device d, QString key)
{
    //qDebug() << "d = " << d.model <<cmd << key;
    command = cmd;
    dev = d;
    //qDebug() << "dev = " << dev.model;
    explain = true;
    explainKey = key;
}

void adbThread::run()
{
    process = new adbProcess();
    process->thread = true;
    //qDebug() << "explainKey is " << explainKey;
    //sleep(3);
    /*
    if(timer == true)
    {
        qDebug() << "oid adbThread::run()-timer == true";
        connect(refreshTimer,SIGNAL(animationEnd()),this,SLOT(sendResult()));
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateResult()));
        process->run_contains_empty(command,dev);
        refreshTimer->start(200);
    }
    else
    {*/
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

        else if(explainKey == "#PERMISSIONGROUPS#")
        {
            //qDebug() << "dev = " << &dev;
            QString output = process->run(command, dev);
            emit signal_output(output);
            exit();
        }

        else if(explainKey == "#INSTALL#")
        {
            connect(process,SIGNAL(outputGet(QString)),this,SLOT(result(QString)));
            /*QString output = */process->run_contains_empty(command, dev);
            //emit signal_output(output);
            exit();
        }

        else if(explainKey == "#SIDELOAD#")
        {
            connect(process,SIGNAL(outputGet(QString)),this,SLOT(result(QString)));
            /*QString output = */process->run_contains_empty(command, dev);
            //emit signal_output(output);
            exit();
        }

        else if(explain == true && explainKey != "#CPU#")
        {
            QString output = explainer->get_words_after(process->run(command, dev), explainKey);
            emit signal_output(output);
            exit();
        }
    //}
}

void adbThread::result(QString str)
{
    emit signal_output(str);
}

void adbThread::updateResult(int,QProcess::ExitStatus)
{
    str_result = "#STD_OUT_PUT#:\n" + process->readAllStandardOutput() + "#STD_ERR#:\n" + process->readAllStandardError();
}

void adbThread::sendResult()
{
    emit regularResult(str_result);
}
