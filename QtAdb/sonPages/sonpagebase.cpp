#include "sonpagebase.h"
#include "ui_sonpagebase.h"

sonPageBase::sonPageBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sonPageBase)
{
    ui->setupUi(this);
}

sonPageBase::~sonPageBase()
{
    delete ui;
}
