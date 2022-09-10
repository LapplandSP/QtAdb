#include "comboboxlistwidget.h"



comboboxListWidget::comboboxListWidget(QWidget *parent)
    : QListWidget{parent}
{
    explainer = new textExplainer();

    nameList[0] = name;
    nameList[1] = addr;
    //this->setModelColumn(count);
    this->setResizeMode(QListView::Adjust);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    QFile file_qss("://qss/scrollbar.qss");
    file_qss.open(QFile::ReadOnly);
    this->verticalScrollBar()->setStyleSheet(file_qss.readAll());
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
/*
    file = new QFile(":/cfgs/cfg/name.cfg");
    file->open(QFile::ReadWrite);*/
}

comboboxListWidget::~comboboxListWidget()
{

}

void comboboxListWidget::setUpList(QList<device> devList, QList<int> off)
{
    /*
    QFile file(":/cfgs/cfg/name.cfg");
    file.open(QFile::ReadOnly);
    QString names = file.readAll();
    names = explainer->get_words_before(explainer->get_words_after(names,"###NAME###"),"###ENDNAME###");
    QStringList tmpList = names.split("\n");*/
    //qDebug() << tmpList;
/*
    for(int i = 0 ;i < tmpList.size() ; i++)
    {
        nameList[0].append(explainer->get_words_after(tmpList[i],":"));
        nameList[1].append(explainer->get_words_before(tmpList[i],":"));
    }*/

    for (int i = 0 ; i < devList.size() ; i++ )
    {
        devItem *wgt = new devItem(this);
        wgt->setAddr(devList[i].addr);
        wgt->setDevice(devList[i].device_product);
        wgt->setDevModel(devList[i].model);
        wgt->setStat(devList[i].state);

        qDebug() << "nameList[1] (addr)" << nameList[1];
        qDebug() << "devList[i].addr" << devList[i].addr;
        if(nameList[1].contains(devList[i].addr))
        {
            wgt->setName(nameList[0][nameList[1].indexOf(devList[i].addr)]);
            //qDebug() << nameList[0][nameList[1].indexOf(devList[i].addr)];
        }
        else
        {
            wgt->setName(explainer->get_words_after(devList[i].model,":"));
        }

        QListWidgetItem *item = new QListWidgetItem(this);

        this->addItem(item);
        this->setItemWidget(item, wgt);

        connect(wgt,SIGNAL(addName(QString,QString)),this,SLOT(addName(QString,QString)));
    }
/*
    file.close();*/
    qDebug() << "closed";
    //file.deleteLater();
}

void comboboxListWidget::addName(QString addr,QString name)
{/*
    addr = explainer->get_words_after(addr, ": ");
    qDebug() << "addr:" << addr << "name:" << name;

    if(nameList[1].contains(addr))
    {
        nameList[0][nameList[1].indexOf(addr)] = name;
    }
    else
    {
        nameList[0].append(name);
        nameList[1].append(addr);
    }

    QString text = "###NAME###\n";

    for(int i = 0 ;i < nameList->size() ; i++)
    {
        text.append(nameList[1][i]).append(":").append(nameList[0][i]).append("\n");
    }

    text.append("###ENDNAME###");

    //file.open(QFile::ReadWrite);
    //file.close();
    QFile file(":/cfgs/cfg/name.cfg");
    file.setPermissions(QFile::WriteUser);
    file.open(QIODevice::Truncate | QIODevice::WriteOnly);
    qDebug() << file.isWritable();
    file.write(text.toUtf8());
    file.close();
    file.deleteLater();*/
}
