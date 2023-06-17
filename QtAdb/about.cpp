#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    basePage(parent),
    ui(new Ui::about)
{
    self_castrate();
    ui->setupUi(this);

    QGraphicsDropShadowEffect *shadowEffect_btn_website = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_website->setOffset(0,0);
    shadowEffect_btn_website->setColor(Qt::gray);
    shadowEffect_btn_website->setBlurRadius(5);
    ui->btn_website->setGraphicsEffect(shadowEffect_btn_website);

    QGraphicsDropShadowEffect *shadowEffect_btn_coolapk = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_coolapk->setOffset(0,0);
    shadowEffect_btn_coolapk->setColor(Qt::gray);
    shadowEffect_btn_coolapk->setBlurRadius(5);
    ui->btn_coolapk->setGraphicsEffect(shadowEffect_btn_coolapk);

    QGraphicsDropShadowEffect *shadowEffect_btn_github = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_github->setOffset(0,0);
    shadowEffect_btn_github->setColor(Qt::gray);
    shadowEffect_btn_github->setBlurRadius(5);
    ui->btn_github->setGraphicsEffect(shadowEffect_btn_github);

    QGraphicsDropShadowEffect *shadowEffect_btn_money = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_money->setOffset(0,0);
    shadowEffect_btn_money->setColor(Qt::gray);
    shadowEffect_btn_money->setBlurRadius(5);
    //ui->btn_money->setGraphicsEffect(shadowEffect_btn_money);

    QGraphicsDropShadowEffect *shadowEffect_btn_money2 = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_money2->setOffset(0,0);
    shadowEffect_btn_money2->setColor(QColorConstants::Svg::orange);
    shadowEffect_btn_money2->setBlurRadius(5);
    ui->btn_money_2->setGraphicsEffect(shadowEffect_btn_money2);/*
    QGraphicsDropShadowEffect *shadowEffect_btn_money3 = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_money3->setOffset(0,0);
    shadowEffect_btn_money3->setColor(Qt::gray);
    shadowEffect_btn_money3->setBlurRadius(5);
    ui->btn_money_3->setGraphicsEffect(shadowEffect_btn_money3);
    QGraphicsDropShadowEffect *shadowEffect_btn_money4 = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_money4->setOffset(0,0);
    shadowEffect_btn_money4->setColor(Qt::gray);
    shadowEffect_btn_money4->setBlurRadius(5);
    ui->btn_money_4->setGraphicsEffect(shadowEffect_btn_money4);*/

    QGraphicsDropShadowEffect *shadowEffect_btn_qq = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_qq->setOffset(0,0);
    shadowEffect_btn_qq->setColor(Qt::gray);
    shadowEffect_btn_qq->setBlurRadius(5);
    ui->btn_qq_dis->setGraphicsEffect(shadowEffect_btn_qq);

    QGraphicsDropShadowEffect *shadowEffect_btn_qGroup = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_qGroup->setOffset(0,0);
    shadowEffect_btn_qGroup->setColor(Qt::gray);
    shadowEffect_btn_qGroup->setBlurRadius(5);
    ui->btn_qgroup->setGraphicsEffect(shadowEffect_btn_qGroup);

    QGraphicsDropShadowEffect *shadowEffect_btn_version = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_version->setOffset(0,0);
    shadowEffect_btn_version->setColor(Qt::gray);
    shadowEffect_btn_version->setBlurRadius(5);
    ui->btn_version->setGraphicsEffect(shadowEffect_btn_version);

    QGraphicsDropShadowEffect *shadowEffect_btn_links = new QGraphicsDropShadowEffect(this);
    shadowEffect_btn_links->setOffset(0,0);
    shadowEffect_btn_links->setColor(QColorConstants::Svg::skyblue);
    shadowEffect_btn_links->setBlurRadius(5);
    ui->btn_links->setGraphicsEffect(shadowEffect_btn_links);


    QFont font1;
    font1.setFamilies({QString::fromUtf8("LXGW WenKai Lite")});
    font1.setPointSize(12);
    //ui->setFont(font1);

    /*
    ui->btn_money->hide();
    ui->btn_money_3->hide();
    ui->btn_money_4->hide();*/
    //this->setStyleSheet("QToolTip{border:1px solid #BDBDBD; background-color: #ffffff; color:rgba(117, 117, 117, 0.9);font-family: MiSans Medium; font-size:12px;border-radius:4px;}");
    //this->setStyleSheet("QToolTip{border:1px solid #BDBDBD; background-color: #ffffff; color:rgba(117, 117, 117, 0.9);font-family: MiSans Medium; font-size:12px;border-radius:4px;}");
}

about::~about()
{
    delete ui;
}

void about::on_btn_website_clicked()
{
    QDesktopServices::openUrl(QUrl("https://lapplandsp.github.io/QtAdb-Pages/", QUrl::TolerantMode));
}

void about::on_btn_coolapk_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.coolapk.com/u/692559", QUrl::TolerantMode));
}

void about::on_btn_github_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/LapplandSP", QUrl::TolerantMode));
}

void about::on_btn_money_2_clicked()
{
    pay * payPage = new pay();
    payPage->setStyleSheet("background-color:rgba(255,255,255,1);");
    payPage->setWindowIcon(QIcon(":/ico/image/ico/about/cola.svg"));
    payPage->setBaseSize(300,500);
    payPage->setWindowTitle("请我喝可乐");
    payPage->show();
}

void about::on_btn_links_clicked()
{
    links *linksPage = new links();
    linksPage->show();
}


void about::on_btn_version_clicked()
{
    QDesktopServices::openUrl(QUrl("https://lapplandsp.github.io/QtAdb-Pages/qa/", QUrl::TolerantMode));
}


void about::on_btn_qq_dis_clicked()
{
    QDesktopServices::openUrl(QUrl("https://pd.qq.com/s/k96ej1", QUrl::TolerantMode));
}


void about::on_btn_qgroup_clicked()
{
    QDesktopServices::openUrl(QUrl("http://qm.qq.com/cgi-bin/qm/qr?_wv=1027&k=5s7RHXEhHg54Zng2B9NgOJ1f1LT1j-JU&authKey=Sxp0Mgvc0F8Esh6YuANcWe4n1abjXvZ%2BPPMfw8pIf85FEdRuRxGgbwpxcBGyaGR4&noverify=0&group_code=860105291", QUrl::TolerantMode));
}

