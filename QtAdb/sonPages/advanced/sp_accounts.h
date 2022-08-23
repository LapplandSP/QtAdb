#ifndef SP_ACCOUNTS_H
#define SP_ACCOUNTS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"
#include <QScrollBar>
#include <QFile>

namespace Ui {
class sp_accounts;
}

class sp_accounts : public QWidget
{
    Q_OBJECT

public:
    explicit sp_accounts(QWidget *parent = nullptr);
    ~sp_accounts();

    device dev;
    void setDev(device dev);

private slots:
    void on_refreshBtn_clicked();

    void on_pushButton_clicked();

public slots:
    void refresh_tableView(QString);


private:
    Ui::sp_accounts *ui;

    adbProcess *process;
    adbThread *thread;
    textExplainer *explainer;
};


#endif // SP_ACCOUNTS_H
