#include "devitem.h"
#include "ui_devitem.h"

devItem::devItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::devItem)
{
    ui->setupUi(this);
    explainer = new textExplainer();
    QGraphicsDropShadowEffect *shadowEffect_wgt = new QGraphicsDropShadowEffect(this);

    shadowEffect_wgt->setOffset(0,0);
    shadowEffect_wgt->setColor(Qt::gray);
    shadowEffect_wgt->setBlurRadius(5);
    ui->widget_phone->setGraphicsEffect(shadowEffect_wgt);
    ui->widget_2->setStyleSheet("QToolTip{border:1px solid #BDBDBD; background-color: #ffffff; color:rgba(117, 117, 117, 0.9);font-family: MiSans Medium; font-size:12px;border-radius:4px;}");

    ui->lineEdit->hide();
}

devItem::~devItem()
{
    delete ui;
}

void devItem::setAddr(QString s)
{
    ui->label_addr_info->setText("序列号\n" + s);
}
void devItem::setDevModel(QString s)
{
    ui->label_model_info->setText("型号\n" + explainer->get_words_after(s, ":"));
}

void devItem::setDevice(QString s)
{
    ui->label_device_info->setText("设备代号\n" + explainer->get_words_after(s, ":"));
}

void devItem::setName(QString s)
{
    ui->lineEdit->setText(s);
}

void devItem::setStat(QString s)
{
    ui->label_stat_info->setText(s);
    if(s=="[未授权]")
    {
        ui->label_stat_info->setStyleSheet("background-color: rgba(237,90,101,0.6);"
                                           "border:0px solid #BDBDBD;"
                                           "border-radius:15px;");
    }
}

void devItem::on_lineEdit_editingFinished()
{
    emit addName(ui->label_addr_info->text(),ui->lineEdit->text());
}
