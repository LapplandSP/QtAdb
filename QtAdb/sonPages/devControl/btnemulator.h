#ifndef BTNEMULATOR_H
#define BTNEMULATOR_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "textexplainer.h"
#include "adbprocess.h"
#include "../../animationwidget.h"

namespace Ui {
class btnEmulator;
}

class btnEmulator : public animationWidget
{
    Q_OBJECT

public:
    explicit btnEmulator(QWidget *parent = nullptr);
    ~btnEmulator();

    adbProcess* process;
    textExplainer* explainer;
    device dev;
    void setDev(device device);
    void setShadow(QWidget* wgt);
    void setStyles();

private slots:
    void on_btn_back_clicked();

    void on_btn_home_clicked();

    void on_btn_menu_clicked();

    void on_btn_changeWindow_clicked();

    void on_btn_power_clicked();

    void on_btn_volUp_clicked();

    void on_btn_volDown_clicked();

    void on_btn_mute_clicked();

    void on_btn_shoot_clicked();

    void on_btn_play_stop_clicked();

    void on_btn_stop_clicked();

    void on_last_clicked();

    void on_btn_play_clicked();

    void on_btn_pause_clicked();

    void on_btn_next_clicked();

    void on_btn_light_down_clicked();

    void on_btn_light_up_clicked();

    void on_btn_sleep_clicked();

    void on_btn_sleep2_clicked();

    void on_btn_delight_clicked();

    void on_btn_call_AI_clicked();

    void on_btn_hang_up_clicked();

    void on_btn_settings_clicked();

    void on_btn_contacts_clicked();

    void on_btn_phone_clicked();

    void on_btn_browser_clicked();

    void on_btn_music_clicked();

    void on_btn_calender_clicked();

    void on_btn_calc_clicked();

private:
    Ui::btnEmulator *ui;
};

#endif // BTNEMULATOR_H
