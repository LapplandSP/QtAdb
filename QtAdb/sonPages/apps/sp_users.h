#ifndef SP_USERS_H
#define SP_USERS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"
#include <QScrollBar>
#include <QFile>
#include "../../animationwidget.h"

namespace Ui {
class sp_users;
}

class sp_users : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_users(QWidget *parent = nullptr);
    ~sp_users();

    device dev;
    void setDev(device dev);

private slots:
    void on_refreshBtn_clicked();

    void on_pushButton_clicked();

public slots:
    void refresh_tableView(QString);

private:
    Ui::sp_users *ui;

    adbProcess *process;
    adbThread *thread;
    textExplainer *explainer;
};

#endif // SP_USERS_H
