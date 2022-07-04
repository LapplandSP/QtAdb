#include "pay.h"
#include "ui_pay.h"

pay::pay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pay)
{
    ui->setupUi(this);
}

pay::~pay()
{
    delete ui;
}
