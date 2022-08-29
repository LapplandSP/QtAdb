#include "links.h"
#include "qgraphicseffect.h"
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

    setShadow(ui->widget_11);
    setShadow(ui->widget_12);
    setShadow(ui->widget_14);
    setShadow(ui->widget_15);
}

links::~links()
{
    delete ui;
}

void links::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}
