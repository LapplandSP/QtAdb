#ifndef SP_PERMISSIONS_H
#define SP_PERMISSIONS_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QStandardItemModel>
#include "../../textexplainer.h"
#include "../../threads/adbthread.h"

namespace Ui {
class sp_permissions;
}

class sp_permissions : public QWidget
{
    Q_OBJECT

public:
    explicit sp_permissions(QWidget *parent = nullptr);
    ~sp_permissions();

    device dev;
    void setDev(device dev);
    QWidget *pa;

private slots:
    void on_back_to_basePage_2_clicked();
    void setArg();

    void on_refreshBtn_clicked();

    void on_open_another_window_clicked();

public slots:
    void refresh_tableView(QString);

private:
    Ui::sp_permissions *ui;
    QString arg = "";

    QStandardItemModel* current_model;
    adbThread *thread;
    textExplainer *explainer;

    bool arg_g = false;
    bool arg_f = false;
    bool arg_s = false;
    bool arg_d = false;
    bool arg_u = false;

    QDialog *settings;
    QButtonGroup *group;
    QRadioButton *btn_g;
    QRadioButton *btn_f;
    QRadioButton *btn_s;
    QRadioButton *btn_d;
    QRadioButton *btn_u;
    QPushButton *closeBtn;

    void generalMode(QString s);
};

#endif // SP_PERMISSIONS_H
