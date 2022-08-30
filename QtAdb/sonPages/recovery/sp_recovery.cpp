#include "sp_recovery.h"
#include "ui_sp_recovery.h"

sp_recovery::sp_recovery(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_recovery)
{
    ui->setupUi(this);

    process = new adbProcess();
    thread = new adbThread();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    shadowEffect_runBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_showOutputBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    //shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_selectBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_output = new QGraphicsDropShadowEffect(this);
    shadowEffect_tips = new QGraphicsDropShadowEffect(this);

    shadowEffect_runBtn->setOffset(0,0);
    shadowEffect_runBtn->setColor(Qt::gray);
    shadowEffect_runBtn->setBlurRadius(5);

    shadowEffect_showOutputBtn->setOffset(0,0);
    shadowEffect_showOutputBtn->setColor(Qt::gray);
    shadowEffect_showOutputBtn->setBlurRadius(5);

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    /*
    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);*/

    shadowEffect_selectBtn->setOffset(0,0);
    shadowEffect_selectBtn->setColor(Qt::gray);
    shadowEffect_selectBtn->setBlurRadius(5);

    shadowEffect_output->setOffset(0,0);
    shadowEffect_output->setColor(Qt::gray);
    shadowEffect_output->setBlurRadius(5);

    shadowEffect_tips->setOffset(0,0);
    shadowEffect_tips->setColor(Qt::red);
    shadowEffect_tips->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->runBtn->setGraphicsEffect(shadowEffect_runBtn);
    ui->showOutputBtn->setGraphicsEffect(shadowEffect_showOutputBtn);
    //ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);
    ui->selectBtn->setGraphicsEffect(shadowEffect_selectBtn);
    ui->output->setGraphicsEffect(shadowEffect_output);
    ui->tips->setGraphicsEffect(shadowEffect_tips);

    ui->progressBar->setVisible(false);
    ui->output->setText("暂时仅支持 .zip 格式\n进度将显示在设备端");
}

sp_recovery::~sp_recovery()
{
    if(page != NULL)
    {
        delete page;
    }

    delete ui;
}

void sp_recovery::setDev(device device)
{
    dev = device;

    if(dev.state != "[侧载]")
    {
        ui->runBtn->setDisabled(true);
        shadowEffect_tips->setColor(Qt::green);
        ui->tips->setText("请先打开设备的「Sideload」模式");
    }
    else
    {
        ui->tips->setText("「Sideload」为实验功能，请谨慎使用");
    }
}

void sp_recovery::on_runBtn_clicked()
{
    //qDebug() << "enter runBtn slot";
    ui->progressBar->setVisible(true);
    ui->output->setText("正在刷入，请在设备端查看进度，切勿插拔设备");

    QString command;

    if(zipPath != "")
    {
        command = "adb sideload ~ " + zipPath + " ~";
    }
    else
    {
        command = "adb sideload";
    }

    thread->initThread(command, dev, "#SIDELOAD#");
    qDebug() << "command =" << command;
    connect(thread,SIGNAL(signal_output(QString)),this,SLOT(updateProgress(QString)));
    thread->start();


    this->setDisabled(true);

    zipPath.clear();
    labelDisplay.clear();

}

void sp_recovery::on_selectBtn_clicked()
{
    //qDebug() << "enter pushbutton slot";
    zipPath.clear();
    zipPath = QFileDialog::getOpenFileName(this, QStringLiteral("选择zip包"), "F:",QStringLiteral("压缩包(*.zip)"));

    ui->filePaths->setText(zipPath);

    //qDebug() << "zipPathis:" << zipPath;
}

void sp_recovery::on_showOutputBtn_clicked(bool checked)
{
    qDebug() << "2";
    if(checked)
    {
        page = new standardOutputPage(NULL,process);
        page->setWindowTitle("命令行输出");
        qDebug() << "1";
        connect(process,SIGNAL(outputGet(QString)),page,SLOT(update(QString)));
        /*
        parents->mapToGlobal(parents->pos());
        page->move(parents->pos().x() + parents->width() + this->width()/2 + 22,0);*/
        //page->setWindowFlags(Qt::FramelessWindowHint);parents->pos().x() + parents->width() +this->width() + 22
        page->show();
    }
    else
    {
        qDebug() << "1?";
        page->~standardOutputPage();
    }
}

void sp_recovery::updateProgress(QString s)
{
    ui->progressBar->hide();
    ui->filePaths->clear();

    qDebug() << "侧载已结束，请在设备上查看结果" << s;
    ui->output->setText("侧载已结束，请在设备上查看结果");
    ui->tips->setText("设备将退出侧载模式，请刷新设备列表以返回");
    ui->back_to_basePage->hide();
    this->setEnabled(true);
}
