#include "thread_monitor.h"

thread_monitor::thread_monitor(device dev)
{
    process = new adbProcess();
    explainer = new textExplainer();
    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(getInfo()));
    //adb shell cat /proc/meminfo
    //adb shell cat proc/stat
}

void thread_monitor::run()
{
    process->thread = true;
    //timer->start(1000);
    /*
    while(true)
    {

    }*/
}

void thread_monitor::getInfo()
{
    //qDebug() << ">> getInfo()";
    cpu_t2 = process->run("adb shell cat proc/stat", dev);
    mem = process->run("adb shell cat /proc/meminfo",dev);

    //qDebug() << "cpu_t2 =" << cpu_t2;
    //qDebug() << mem;

    if(cpu_t1 != "#FIRSTBOOT#" && !cpu_t2.isEmpty() && !mem.isEmpty())
    {
        //qDebug() << "before, cpu_t1 = " <<cpu_t1;
        QStringList list_t2 = cpu_t2.split("\n")[0].split(" ");
        list_t2.removeAll("");
        QStringList list_t1 = cpu_t1.split("\n")[0].split(" ");
        list_t1.removeAll("");
        //qDebug() << "list_t2[1].toInt() = " << list_t2[1].toInt();
        //qDebug() << "list_t1[1].toInt() = " << list_t1[1].toInt();
        int timeTotal_t2 = list_t2[1].toInt() + list_t2[2].toInt() + list_t2[3].toInt() + list_t2[4].toInt() + list_t2[5].toInt() + list_t2[6].toInt() + list_t2[7].toInt();
        //qDebug() << "timeTotal_t2 = " <<timeTotal_t2;
        int timeTotal_t1 = list_t1[1].toInt() + list_t1[2].toInt() + list_t1[3].toInt() + list_t1[4].toInt() + list_t1[5].toInt() + list_t1[6].toInt() + list_t1[7].toInt();
        //qDebug() << "timeTotal_t1 = " <<timeTotal_t1;
        //qDebug() << "total complete";
        int timeIdle_t2 = list_t2[4].toInt();
        //qDebug() << "timeIdle_t2 = " <<timeIdle_t2;
        int timeIdle_t1 = list_t1[4].toInt();
        //qDebug() << "timeIdle_t1 = " <<timeIdle_t1;
        //qDebug() << "idle complete";

        float cpu_use = 1 - ((float)(timeIdle_t2 - timeIdle_t1) / (float)(timeTotal_t2 - timeTotal_t1));
        //qDebug() << "cpu_use = " << cpu_use;
        cpu_t1 = cpu_t2;
        cpu_t2 = "";

        int MemTotal = explainer->get_words_before(explainer->get_words_after(mem.split("\n")[0] , "MemTotal:") , "kB").simplified().simplified().toInt();
        //int MemFree = explainer->get_words_before(explainer->get_words_after(mem.split("\n")[1] , "MemFree:") , "kB").simplified().simplified().toInt();
        int MemAvailable = explainer->get_words_before(explainer->get_words_after(mem.split("\n")[2] , "MemAvailable:") , "kB").simplified().simplified().toInt();
        qDebug() << "Mem = " << mem;
        qDebug() << "MemTotal = " << MemTotal;
        //qDebug() << "MemFree = " << MemFree;
        //float mem_use = (float)(MemTotal - MemFree) / (float)MemTotal;
        float mem_use = (float)(MemTotal - MemAvailable) / (float)MemTotal;

        qDebug() << "mem_use = " << mem_use;

        mem = "";
        emit signal_monitor(cpu_use, mem_use);
    }
    else
    {
        //qDebug() << "cpu_t2.isEmpty?" << cpu_t2.isEmpty();
        //qDebug() << "mem.isEmpty?" << mem.isEmpty();
        cpu_t1 = process->run("adb shell cat proc/stat", dev);
    }
    //cpu_t1 = "";
}
