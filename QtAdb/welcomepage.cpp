#include "welcomepage.h"
#include "ui_welcomepage.h"

welcomePage::welcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomePage)
{
    ui->setupUi(this);
}

welcomePage::~welcomePage()
{
    delete ui;
}
