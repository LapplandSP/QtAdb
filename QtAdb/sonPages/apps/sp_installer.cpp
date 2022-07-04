#include "sp_installer.h"
#include "ui_sp_installer.h"

sp_installer::sp_installer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_installer)
{
    ui->setupUi(this);

    process = new adbProcess();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    QGraphicsDropShadowEffect *shadowEffect_runBtn = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *shadowEffect_showOutputBtn = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *shadowEffect_selectBtn = new QGraphicsDropShadowEffect();

    shadowEffect_runBtn->setOffset(0,0);
    shadowEffect_runBtn->setColor(Qt::gray);
    shadowEffect_runBtn->setBlurRadius(5);

    shadowEffect_showOutputBtn->setOffset(0,0);
    shadowEffect_showOutputBtn->setColor(Qt::gray);
    shadowEffect_showOutputBtn->setBlurRadius(5);

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);

    shadowEffect_selectBtn->setOffset(0,0);
    shadowEffect_selectBtn->setColor(Qt::gray);
    shadowEffect_selectBtn->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->runBtn->setGraphicsEffect(shadowEffect_runBtn);
    ui->showOutputBtn->setGraphicsEffect(shadowEffect_showOutputBtn);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);
    ui->selectBtn->setGraphicsEffect(shadowEffect_selectBtn);

    /*
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect();
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    ui->widget->setGraphicsEffect(shadowEffect_widget);*/

}

sp_installer::~sp_installer()
{
    delete ui;
}

void sp_installer::setDev(device device)
{
    dev = device;
}
void sp_installer::on_runBtn_clicked()
{
    qDebug() << "enter runBtn slot";
    QString command;
    if(apkPath != "")
    {
        command = "adb install ~ " + apkPath + " ~";
    }
    else
    {
        command = "adb install";
    }
    qDebug() << "enter runBtn slot 1";
    qDebug() << "enter runBtn slot 2";
    qDebug() << "enter runBtn slot 4";
    qDebug() << "command: " << command;
    qDebug() << "running";
    process->run_contains_empty(command, dev);
    apkPath.clear();
    labelDisplay.clear();
    ui->filePaths->clear();
}

void sp_installer::on_selectBtn_clicked()
{
    qDebug() << "enter pushbutton slot";
    apkPath.clear();
    apkPath = QFileDialog::getOpenFileName(this, QStringLiteral("选择安装包"), "F:",QStringLiteral("安装包(*.apk)"));

    ui->filePaths->setText(apkPath);

    qDebug() << "apkPathis:" << apkPath;
}
