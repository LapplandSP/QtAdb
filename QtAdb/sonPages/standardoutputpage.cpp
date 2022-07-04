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
    ui->textBrowser->setText("该功能暂未实现，敬请期待！");
}

standardOutputPage::~standardOutputPage()
{
    delete ui;
}

void standardOutputPage::update()
{
    ui->textBrowser->setText(process->standardOutput);
}

void standardOutputPage::on_refreshBtn_clicked()
{
    update();
}


void standardOutputPage::on_clearBtn_clicked()
{
    ui->textBrowser->clear();
}

void standardOutputPage::on_copyBtn_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(ui->textBrowser->toPlainText());
}
