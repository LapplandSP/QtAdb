#include "sp_recovery.h"
#include "ui_sp_recovery.h"

sp_recovery::sp_recovery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_recovery)
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
}

sp_recovery::~sp_recovery()
{
    delete ui;
}

void sp_recovery::setDev(device device)
{
    dev = device;
}
void sp_recovery::on_runBtn_clicked()
{
    qDebug() << "enter runBtn slot";
    QString command;

    if(zipPath != "")
    {
        command = "adb sideload ~ " + zipPath + " ~";
    }
    else
    {
        command = "adb sideload";
    }

    qDebug() << "command: " << command;
    qDebug() << "running";
    process->run_contains_empty(command, dev);
    zipPath.clear();
    labelDisplay.clear();
    ui->filePaths->clear();
}

void sp_recovery::on_selectBtn_clicked()
{
    qDebug() << "enter pushbutton slot";
    zipPath.clear();
    zipPath = QFileDialog::getOpenFileName(this, QStringLiteral("选择zip包"), "F:",QStringLiteral("压缩包(*.zip)"));

    ui->filePaths->setText(zipPath);

    qDebug() << "zipPathis:" << zipPath;
}
