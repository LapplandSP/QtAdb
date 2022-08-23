#include "monitor.h"
#include "ui_monitor.h"

monitor::monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::monitor)
{
    ui->setupUi(this);
}

monitor::~monitor()
{
    delete ui;
}
