#include "btnemulator.h"
#include "ui_btnemulator.h"

btnEmulator::btnEmulator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btnEmulator)
{
    ui->setupUi(this);
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));
    process = new adbProcess();
    explainer = new textExplainer();
    this->setStyleSheet("QToolTip{border:1px solid #BDBDBD; background-color: #ffffff; color:rgba(117, 117, 117, 0.9);font-family: MiSans Medium; font-size:12px;border-radius:4px;}");

    setStyles();
}

btnEmulator::~btnEmulator()
{
    delete ui;
}

void btnEmulator::setDev(device device)
{
    dev = device;
}

void btnEmulator::on_btn_back_clicked()
{
    process->run("adb shell input keyevent 4", dev);
}

void btnEmulator::on_btn_home_clicked()
{
    process->run("adb shell input keyevent 3", dev);
}

void btnEmulator::on_btn_menu_clicked()
{
    process->run("adb shell input keyevent 82", dev);
}

void btnEmulator::on_btn_changeWindow_clicked()
{
    process->run("adb shell input keyevent 187", dev);
}

void btnEmulator::on_btn_power_clicked()
{
    process->run("adb shell input keyevent 26", dev);
}

void btnEmulator::on_btn_volUp_clicked()
{
    process->run("adb shell input keyevent 24", dev);
}

void btnEmulator::on_btn_volDown_clicked()
{
    process->run("adb shell input keyevent 25", dev);
}

void btnEmulator::on_btn_mute_clicked()
{
    process->run("adb shell input keyevent 164", dev);
}

void btnEmulator::on_btn_shoot_clicked()
{
    process->run("adb shell input keyevent 27", dev);
}

void btnEmulator::on_btn_play_stop_clicked()
{
    process->run("adb shell input keyevent 85", dev);
}

void btnEmulator::on_btn_stop_clicked()
{
    process->run("adb shell input keyevent 86", dev);
}

void btnEmulator::on_last_clicked()
{
    process->run("adb shell input keyevent 88", dev);
}

void btnEmulator::on_btn_play_clicked()
{
    process->run("adb shell input keyevent 126", dev);
}

void btnEmulator::on_btn_pause_clicked()
{
    process->run("adb shell input keyevent 127", dev);
}

void btnEmulator::on_btn_next_clicked()
{
    process->run("adb shell input keyevent 87", dev);
}

void btnEmulator::on_btn_light_down_clicked()
{
    process->run("adb shell input keyevent 220", dev);
}

void btnEmulator::on_btn_light_up_clicked()
{
    process->run("adb shell input keyevent 221", dev);
}

void btnEmulator::on_btn_sleep_clicked()
{
    process->run("adb shell input keyevent 223", dev);
}

void btnEmulator::on_btn_sleep2_clicked()
{
    process->run("adb shell input keyevent 276", dev);
}

void btnEmulator::on_btn_delight_clicked()
{
    process->run("adb shell input keyevent 224", dev);
}

void btnEmulator::on_btn_call_AI_clicked()
{
    process->run("adb shell input keyevent 231", dev);
}

void btnEmulator::on_btn_hang_up_clicked()
{
    process->run("adb shell input keyevent 6", dev);
}

void btnEmulator::on_btn_settings_clicked()
{
    process->run("adb shell input keyevent 176", dev);
}

void btnEmulator::on_btn_contacts_clicked()
{
    process->run("adb shell input keyevent 207", dev);
}

void btnEmulator::on_btn_phone_clicked()
{
    process->run("adb shell input keyevent 5", dev);
}

void btnEmulator::on_btn_browser_clicked()
{
    process->run("adb shell input keyevent 64", dev);
}

void btnEmulator::on_btn_music_clicked()
{
    process->run("adb shell input keyevent 209", dev);
}

void btnEmulator::on_btn_calender_clicked()
{
    process->run("adb shell input keyevent 208", dev);
}

void btnEmulator::on_btn_calc_clicked()
{
    process->run("adb shell input keyevent 210", dev);
}

void btnEmulator::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect();
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}

void btnEmulator::setStyles()
{
    /*
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect();
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    ui->widget->setGraphicsEffect(shadowEffect_widget);*/

    setShadow(ui->btn_back);
    setShadow(ui->btn_home);
    setShadow(ui->btn_menu);
    setShadow(ui->btn_changeWindow);
    setShadow(ui->btn_power);
    setShadow(ui->btn_volUp);
    setShadow(ui->btn_volDown);
    setShadow(ui->btn_mute);
    setShadow(ui->btn_shoot);
    setShadow(ui->btn_play_stop);
    setShadow(ui->btn_stop);
    setShadow(ui->last);
    setShadow(ui->btn_play);
    setShadow(ui->btn_pause);
    setShadow(ui->btn_next);
    setShadow(ui->btn_light_down);
    setShadow(ui->btn_light_up);
    setShadow(ui->btn_sleep);
    setShadow(ui->btn_sleep2);
    setShadow(ui->btn_delight);
    setShadow(ui->btn_call_AI);
    setShadow(ui->btn_hang_up);
    setShadow(ui->btn_settings);
    setShadow(ui->btn_contacts);
    setShadow(ui->btn_phone);
    setShadow(ui->btn_browser);
    setShadow(ui->btn_music);
    setShadow(ui->btn_calender);
    setShadow(ui->btn_calc);
    setShadow(ui->back_to_basePage);

    setShadow(ui->label);
    setShadow(ui->label_2);
    setShadow(ui->label_3);
    setShadow(ui->label_4);
    setShadow(ui->label_5);

    ui->label->setStyleSheet("border:0px;background-color:rgba(255,255,255,0.7);");
    ui->label_2->setStyleSheet("border:0px;background-color:rgba(255,255,255,0.7);");
    ui->label_3->setStyleSheet("border:0px;background-color:rgba(255,255,255,0.7);");
    ui->label_4->setStyleSheet("border:0px;background-color:rgba(255,255,255,0.7);");
    ui->label_5->setStyleSheet("border:0px;background-color:rgba(255,255,255,0.7);");
}
