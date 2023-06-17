#include "indexlistitem.h"
#include "ui_indexlistitem.h"

indexListItem::indexListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indexListItem)
{
    ui->setupUi(this);
}

indexListItem::~indexListItem()
{
    delete ui;
}

void indexListItem::setText(QString text)
{
    ui->text->setText(text);
}

void indexListItem::setPic(QString qss)
{
    ui->pic->setStyleSheet(qss);
}
