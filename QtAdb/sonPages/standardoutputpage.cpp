#include "standardoutputpage.h"
#include "ui_standardoutputpage.h"

standardOutputPage::standardOutputPage(QWidget *parent, adbProcess *cess) :
    QWidget(parent),
    ui(new Ui::standardOutputPage)
{
    ui->setupUi(this);
    process = cess;

    QTimer *timer = new QTimer(this);   //初始化一个定时器。
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));   //设置信号与槽 ，槽函数update()需要再类中声明一下。
    timer->start(1000 / 30);    //设置定时器刷新频率，即变量刷新频率。
    ui->textBrowser->setText(text);

    QGraphicsDropShadowEffect *shadowEffect_textBrowser = new QGraphicsDropShadowEffect(this);
    shadowEffect_textBrowser->setOffset(0,0);
    shadowEffect_textBrowser->setColor(Qt::gray);
    shadowEffect_textBrowser->setBlurRadius(5);
    ui->textBrowser->setGraphicsEffect(shadowEffect_textBrowser);

    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);

    QGraphicsDropShadowEffect *shadowEffect_copyBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_copyBtn->setOffset(0,0);
    shadowEffect_copyBtn->setColor(Qt::gray);
    shadowEffect_copyBtn->setBlurRadius(5);
    ui->copyBtn->setGraphicsEffect(shadowEffect_copyBtn);

    QGraphicsDropShadowEffect *shadowEffect_clearBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_clearBtn->setOffset(0,0);
    shadowEffect_clearBtn->setColor(Qt::gray);
    shadowEffect_clearBtn->setBlurRadius(5);
    ui->clearBtn->setGraphicsEffect(shadowEffect_clearBtn);
}

standardOutputPage::~standardOutputPage()
{
    delete ui;
}

void standardOutputPage::update(QString s)
{
    qDebug() << "update:" << s;
    text.append(s);
    on_refreshBtn_clicked();
}

void standardOutputPage::on_refreshBtn_clicked()
{
    ui->textBrowser->setText(text);
}

void standardOutputPage::on_clearBtn_clicked()
{
    ui->textBrowser->clear();
    text.clear();
}

void standardOutputPage::on_copyBtn_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(ui->textBrowser->toPlainText());
}
