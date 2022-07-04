#include "pagelistitem.h"
#include "ui_pagelistitem.h"

pageListItem::pageListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pageListItem)
{
    ui->setupUi(this);
    ui->enableLight->setVisible(false);

    ui->widget->setStyleSheet("background-color:transparent; border-radius:4px; border-color:gray;border:0px;");

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setOffset(0,0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(5);
    ui->enableLight->setGraphicsEffect(shadowEffect);

    QGraphicsDropShadowEffect *shadowEffect_icon = new QGraphicsDropShadowEffect();
    shadowEffect_icon->setOffset(0,0);
    shadowEffect_icon->setColor(Qt::gray);
    shadowEffect_icon->setBlurRadius(5);
    ui->pic->setGraphicsEffect(shadowEffect_icon);
    //this->setGraphicsEffect(shadowEffect);
}

pageListItem::~pageListItem()
{
    delete ui;
}

void pageListItem::setText(QString title, QString profile)
{
    ui->title->setText(title);
    ui->profile->setText(profile);
}

void pageListItem::setPic(QString ico)
{
    ui->pic->setIcon(QIcon(ico));
}

void pageListItem::on_copyButton_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(ui->profile->text());

    QMessageBox *msgBox = new QMessageBox;
    msgBox->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));
    msgBox->setStyleSheet("background-color:rgba(255,255,255,1);border:0px; border-radius:0px;");
    msgBox->setWindowTitle("复制到剪贴板");
    msgBox->setText("·已将文本\n" + ui->profile->text() + "\n复制到剪贴板");
    msgBox->addButton(" ✓ ", QMessageBox::AcceptRole);
    msgBox->show();
}

void pageListItem::setSelectable()
{
    ui->enableLight->setVisible(true);
}
