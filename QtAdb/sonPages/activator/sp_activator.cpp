#include "sp_activator.h"
#include "ui_sp_activator.h"

sp_activator::sp_activator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_activator)
{
    ui->setupUi(this);
    process = new adbProcess;
    parents = parent;

    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    QGraphicsDropShadowEffect *shadowEffect_runBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_showOutputBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);

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

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->runBtn->setGraphicsEffect(shadowEffect_runBtn);
    ui->showOutputBtn->setGraphicsEffect(shadowEffect_showOutputBtn);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);

    QGraphicsDropShadowEffect *shadowEffect_textBrowser = new QGraphicsDropShadowEffect(this);
    shadowEffect_textBrowser->setOffset(0,0);
    shadowEffect_textBrowser->setColor(Qt::gray);
    shadowEffect_textBrowser->setBlurRadius(5);
    ui->textBrowser->setGraphicsEffect(shadowEffect_textBrowser);
}

sp_activator::~sp_activator()
{
    //delete process;
    delete ui;
}

void sp_activator::setUp(QString qss, QString title, QString profile, QString cmd)
{
    ui->appIcon->setStyleSheet(qss);
    ui->appName->setText(title);
    ui->textBrowser->setMarkdown(profile);
    command = cmd;
}

void sp_activator::on_runBtn_clicked()
{
    process->run(command, dev);
}

void sp_activator::setDev(device device)
{
    dev = device;
}

void sp_activator::on_showOutputBtn_clicked(bool checked)
{
    if(checked)
    {
        page = new standardOutputPage(NULL,process);
        /*
        parents->mapToGlobal(parents->pos());
        page->move(parents->pos().x() + parents->width() + this->width()/2 + 22,0);*/
        //page->setWindowFlags(Qt::FramelessWindowHint);parents->pos().x() + parents->width() +this->width() + 22
        page->show();
    }
    else
    {
        page->~standardOutputPage();
    }
}
