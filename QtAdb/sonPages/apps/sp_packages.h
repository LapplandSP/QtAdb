#ifndef SP_PACKAGES_H
#define SP_PACKAGES_H

#include <QWidget>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QStandardItemModel>
#include "adbprocess.h"
#include <QFileDialog>
#include "../../threads/adbthread.h"
#include "tp_packageprofile.h"
#include <QScrollBar>
#include <QFile>
#include "../../animationwidget.h"

/*
struct package
{
    QString package_name;
};*/

namespace Ui {
class sp_packages;
}

class sp_packages : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_packages(QWidget *parent = nullptr);
    ~sp_packages();

    device dev;
    void setDev(device dev);

    QWidget *pa;

    QString current_package = "";

private slots:
    void on_refreshBtn_clicked();

    void on_listView_clicked(const QModelIndex &index);
    void setArgs();

public slots:
    void refresh_tableView(QString);

private:
    Ui::sp_packages *ui;
    adbThread *thread;
    textExplainer *explainer;

    QString arg = "";
};
#endif // SP_PACKAGES_H
