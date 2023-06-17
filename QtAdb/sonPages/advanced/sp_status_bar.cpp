#include "sp_status_bar.h"
#include "ui_sp_status_bar.h"

sp_status_bar::sp_status_bar(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_status_bar)
{
    ui->setupUi(this);

    process = new adbProcess();
    explainer = new textExplainer();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    setShadow(ui->pushButton_hide);
    setShadow(ui->pushButton);
    setShadow(ui->pushButton_restore);
    setShadow(ui->hide_restore);
    setShadow(ui->hide_navigation);
    setShadow(ui->hide_status);
    setShadow(ui->back_to_basePage);
    setShadow(ui->pushButton_2);
}

sp_status_bar::~sp_status_bar()
{
    delete ui;
}

void sp_status_bar::setDev(device device)
{
    dev = device;
}

void sp_status_bar::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}

void sp_status_bar::on_pushButton_hide_clicked()
{
    QString cmd = "adb shell settings put secure icon_blacklist ";
    if(ui->volume->isChecked())
    {
        cmd.append(",volume");
        qDebug() << "ui->volume->isChecked() cmd = " <<cmd;
    }
    if(ui->location->isChecked())
    {
        cmd.append(",location");
        qDebug() << "location isChecked() cmd = " <<cmd;
    }
    if(ui->speakerphone->isChecked())
    {
        cmd.append(",speakerphone");
    }
    if(ui->wifi->isChecked())
    {
        cmd.append(",wifi");
        qDebug() << "wifi isChecked() cmd = " <<cmd;
    }
    if(ui->hotspot->isChecked())
    {
        cmd.append(",hotspot");
    }
    if(ui->alarm_clock->isChecked())
    {
        cmd.append(",alarm_clock");
    }
    if(ui->bluetooth->isChecked())
    {
        cmd.append(",bluetooth");
    }
    if(ui->airplane->isChecked())
    {
        cmd.append(",airplane");
    }
    if(ui->headphone->isChecked())
    {
        cmd.append(",headphone");
    }
    if(ui->cast->isChecked())
    {
        cmd.append(",cast");
    }
    if(ui->nfc->isChecked())
    {
        cmd.append(",nfc");
    }

    process->run(cmd,dev);
    refreshBtns();

    QMessageBox::information(NULL, "隐藏图标","已隐藏选中图标");
}


void sp_status_bar::on_pushButton_restore_clicked()
{
    process->run("adb shell settings put secure icon_blacklist null",dev);
    QMessageBox::information(NULL, "取消隐藏图标","状态栏图标已全部取消隐藏");
}

void sp_status_bar::on_hide_status_clicked()
{
    process->run("adb shell settings put global policy_control immersive.status=*",dev);
    QMessageBox::information(NULL, "隐藏状态栏","已隐藏状态栏");
}


void sp_status_bar::on_hide_navigation_clicked()
{
    process->run("adb shell settings put global policy_control immersive.navigation=*",dev);
    QMessageBox::information(NULL, "隐藏导航栏","已隐藏导航栏");
}

void sp_status_bar::on_hide_restore_clicked()
{
    //adb shell settings put global policy_control null
    process->run("adb shell settings put global policy_control null",dev);
    QMessageBox::information(NULL, "重置","已将状态栏与导航栏取消隐藏");
}

void sp_status_bar::on_pushButton_2_clicked()
{
    process->run("adb shell settings put global policy_control immersive.full=*",dev);
    QMessageBox::information(NULL, "同时隐藏","已将导航栏与状态栏同时全局隐藏");
}

void sp_status_bar::refreshBtns()
{
    ui->airplane->setChecked(false);
    ui->alarm_clock->setChecked(false);
    ui->bluetooth->setChecked(false);
    ui->cast->setChecked(false);
    ui->bluetooth->setChecked(false);
    ui->headphone->setChecked(false);
    ui->hotspot->setChecked(false);
    ui->location->setChecked(false);
    ui->nfc->setChecked(false);
    ui->wifi->setChecked(false);
    ui->volume->setChecked(false);
}

