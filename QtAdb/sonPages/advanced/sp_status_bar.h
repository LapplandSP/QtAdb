#ifndef SP_STATUS_BAR_H
#define SP_STATUS_BAR_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "../../adbprocess.h"
#include "../../animationwidget.h"

namespace Ui {
class sp_status_bar;
}

class sp_status_bar : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_status_bar(QWidget *parent = nullptr);
    ~sp_status_bar();

    device dev;
    void setDev(device dev);


private slots:
    void on_pushButton_hide_clicked();

    void on_pushButton_restore_clicked();

    void on_hide_status_clicked();

    void on_hide_navigation_clicked();

    void on_hide_restore_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::sp_status_bar *ui;

    adbProcess *process;
    textExplainer *explainer;

    void setShadow(QWidget* wgt);
    void refreshBtns();
};

#endif // SP_STATUS_BAR_H
