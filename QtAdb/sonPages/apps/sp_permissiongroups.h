#ifndef SP_PERMISSIONGROUPS_H
#define SP_PERMISSIONGROUPS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"

namespace Ui {
class sp_permissionGroups;
}

class sp_permissionGroups : public QWidget
{
    Q_OBJECT

public:
    explicit sp_permissionGroups(QWidget *parent = nullptr);
    ~sp_permissionGroups();

    device dev;
    void setDev(device dev);

private slots:
    void on_refreshBtn_clicked();

public slots:
    void refresh_tableView(QString);

private:
    Ui::sp_permissionGroups *ui;
    adbThread *thread;
    textExplainer *explainer;
};

#endif // SP_PERMISSIONGROUPS_H
