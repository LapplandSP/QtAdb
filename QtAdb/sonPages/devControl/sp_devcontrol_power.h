#ifndef SP_DEVCONTROL_POWER_H
#define SP_DEVCONTROL_POWER_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "textexplainer.h"
#include "adbprocess.h"

namespace Ui {
class sp_devControl_power;
}

class sp_devControl_power : public QWidget
{
    Q_OBJECT

public:
    explicit sp_devControl_power(QWidget *parent = nullptr);
    ~sp_devControl_power();

    adbProcess* process;
    textExplainer* explainer;
    device dev;
    void setDev(device device);

private slots:
    void on_btn_powerDown_clicked();

    void on_btn_rebootToSystem_clicked();

    void on_btn_rebootToRecovery_clicked();

    void on_btn_rebootToFastboot_clicked();

private:
    Ui::sp_devControl_power *ui;
};

#endif // SP_DEVCONTROL_POWER_H
