#ifndef COMBOBOXLISTWIDGET_H
#define COMBOBOXLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QListView>
#include <QHeaderView>
#include <QFile>
#include <QList>
#include "../devitem.h"
#include "../textexplainer.h"
#include "qstandarditemmodel.h"
#include "qscrollbar.h"

class comboboxListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit comboboxListWidget(QWidget *parent = nullptr);
    ~comboboxListWidget();

    void setUpList(QList<device>, QList<int> off);

    QStringList nameList[2];
    QStringList name;
    QStringList addr;

signals:

private slots:
    void addName(QString addr,QString name);

private:
    textExplainer *explainer;

    //QFile *file;

};

#endif // COMBOBOXLISTWIDGET_H
