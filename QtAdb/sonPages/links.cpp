#include "links.h"
#include "qicon.h"
#include "qscrollbar.h"
#include "ui_links.h"

links::links(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::links)
{
    ui->setupUi(this);


    this->setWindowTitle("相关链接");
    this->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));

    QFile file("://qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(file.readAll());
    ui->scrollArea->horizontalScrollBar()->setStyleSheet(file.readAll());
}

links::~links()
{
    delete ui;
}
