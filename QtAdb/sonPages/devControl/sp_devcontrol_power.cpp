#include "sp_devcontrol_power.h"
#include "ui_sp_devcontrol_power.h"

sp_devControl_power::sp_devControl_power(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_devControl_power)
{
    ui->setupUi(this);
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));
    process = new adbProcess();
    explainer = new textExplainer();

    /*
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect();
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    ui->widget->setGraphicsEffect(shadowEffect_widget);*/

    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect();
    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);
    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);

    QGraphicsDropShadowEffect *shadowEffect_btn_powerDown = new QGraphicsDropShadowEffect();
    shadowEffect_btn_powerDown->setOffset(0,0);
    shadowEffect_btn_powerDown->setColor(Qt::gray);
    shadowEffect_btn_powerDown->setBlurRadius(5);
    ui->btn_powerDown->setGraphicsEffect(shadowEffect_btn_powerDown);

    QGraphicsDropShadowEffect *shadowEffect_btn_rebootToSystem = new QGraphicsDropShadowEffect();
    shadowEffect_btn_rebootToSystem->setOffset(0,0);
    shadowEffect_btn_rebootToSystem->setColor(Qt::gray);
    shadowEffect_btn_rebootToSystem->setBlurRadius(5);
    ui->btn_rebootToSystem->setGraphicsEffect(shadowEffect_btn_rebootToSystem);

    QGraphicsDropShadowEffect *shadowEffect_rebootToRecovery_clicked = new QGraphicsDropShadowEffect();
    shadowEffect_rebootToRecovery_clicked->setOffset(0,0);
    shadowEffect_rebootToRecovery_clicked->setColor(Qt::gray);
    shadowEffect_rebootToRecovery_clicked->setBlurRadius(5);
    ui->btn_rebootToRecovery->setGraphicsEffect(shadowEffect_rebootToRecovery_clicked);

    QGraphicsDropShadowEffect *shadowEffect_btn_rebootToFastboot = new QGraphicsDropShadowEffect();
    shadowEffect_btn_rebootToFastboot->setOffset(0,0);
    shadowEffect_btn_rebootToFastboot->setColor(Qt::gray);
    shadowEffect_btn_rebootToFastboot->setBlurRadius(5);
    ui->btn_rebootToFastboot->setGraphicsEffect(shadowEffect_btn_rebootToFastboot);
}

sp_devControl_power::~sp_devControl_power()
{
    delete ui;
}

void sp_devControl_power::on_btn_powerDown_clicked()
{
    process->run("adb shell reboot -p", dev);
}

void sp_devControl_power::setDev(device device)
{
    dev = device;
}

void sp_devControl_power::on_btn_rebootToSystem_clicked()
{
    qDebug() << "calling process->run('adb reboot', dev);";
    process->run("adb reboot", dev);
    qDebug() << "calling process->run('adb reboot', dev);";
}

void sp_devControl_power::on_btn_rebootToRecovery_clicked()
{
    process->run("adb reboot recovery", dev);
}

void sp_devControl_power::on_btn_rebootToFastboot_clicked()
{
    process->run("adb reboot bootloader", dev);
}
