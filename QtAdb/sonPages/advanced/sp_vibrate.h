#ifndef SP_VIBRATE_H
#define SP_VIBRATE_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpressionValidator>
#include <QFile>
//#include <QRegularExpressionValidator>
#include "../../adbprocess.h"
#include "../../threads/adbthread.h"
#include "../../animationwidget.h"


namespace Ui {
class sp_vibrate;
}

class sp_vibrate : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_vibrate(QWidget *parent = nullptr);
    ~sp_vibrate();

    device dev;
    void setDev(device dev);

private:
    Ui::sp_vibrate *ui;


    adbProcess *process;
    textExplainer *explainer;

    void setShadow(QWidget* wgt);
    void refresh();


private slots:
    void setText_all(QString);
    void setText_all_haptics(QString);
    void setText_all_charge(QString);
    void setText_all_ring(QString);
    void setText_level_haptics(QString);
    void setText_level_haptics_hardware(QString);
    void setText_level_alarm(QString);
    void setText_level_media(QString);
    void setText_level_notification(QString);
    void setText_level_ring(QString);

    void on_pushButton_all_clicked();
    void on_pushButton_all_thaptic_clicked();
    void on_pushButton_all_ring_clicked();
    void on_pushButton_all_charge_clicked();
    void on_pushButton_haptic_clicked();
    void on_pushButton_haptic_hardware_clicked();
    void on_pushButton_notificaton_clicked();
    void on_pushButton_alarm_clicked();
    void on_pushButton_media_clicked();
    void on_pushButton_ring_clicked();
};

#endif // SP_VIBRATE_H
