#ifndef SP_CAPTIVE_PORTAL_H
#define SP_CAPTIVE_PORTAL_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"
#include <QScrollBar>
#include <QFile>
#include "../../animationwidget.h"

namespace Ui {
class sp_captive_portal;
}

class sp_captive_portal : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_captive_portal(QWidget *parent = nullptr);
    ~sp_captive_portal();

    device dev;
    void setDev(device dev);

    void refresh();

private slots:
    void on_modify_clicked();

    void on_delete_directly_clicked();

    void on_restore_clicked();

private:
    Ui::sp_captive_portal *ui;

    adbProcess *process;
    textExplainer *explainer;
    void setShadow(QWidget* wgt);
};

#endif // SP_CAPTIVE_PORTAL_H
