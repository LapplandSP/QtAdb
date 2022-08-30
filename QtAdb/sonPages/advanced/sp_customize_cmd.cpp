#include "sp_customize_cmd.h"
#include "ui_sp_customize_cmd.h"

sp_customize_cmd::sp_customize_cmd(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_customize_cmd)
{
    ui->setupUi(this);
    process = new adbProcess();

    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    QGraphicsDropShadowEffect *shadowEffect_runBtn = new QGraphicsDropShadowEffect(this);
    //QGraphicsDropShadowEffect *shadowEffect_showOutputBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);

    shadowEffect_runBtn->setOffset(0,0);
    shadowEffect_runBtn->setColor(Qt::gray);
    shadowEffect_runBtn->setBlurRadius(5);
/*
    shadowEffect_showOutputBtn->setOffset(0,0);
    shadowEffect_showOutputBtn->setColor(Qt::gray);
    shadowEffect_showOutputBtn->setBlurRadius(5);*/

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->runBtn->setGraphicsEffect(shadowEffect_runBtn);
    //ui->showOutputBtn->setGraphicsEffect(shadowEffect_showOutputBtn);

    QGraphicsDropShadowEffect *shadowEffect_textBrowser = new QGraphicsDropShadowEffect(this);
    shadowEffect_textBrowser->setOffset(0,0);
    shadowEffect_textBrowser->setColor(Qt::gray);
    shadowEffect_textBrowser->setBlurRadius(5);
    ui->textBrowser->setGraphicsEffect(shadowEffect_textBrowser);

    QGraphicsDropShadowEffect *shadowEffect_label = new QGraphicsDropShadowEffect(this);
    shadowEffect_label->setOffset(0,0);
    shadowEffect_label->setColor(Qt::gray);
    shadowEffect_label->setBlurRadius(5);
    ui->label->setGraphicsEffect(shadowEffect_label);
}

sp_customize_cmd::~sp_customize_cmd()
{
    delete ui;
}


void sp_customize_cmd::on_runBtn_clicked()
{
    process->run(ui->lineEdit->text());
}
