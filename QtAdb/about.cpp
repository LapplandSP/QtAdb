#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    basePage(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    self_castrate();

    QGraphicsDropShadowEffect *shadowEffect_btn_website = new QGraphicsDropShadowEffect();
    shadowEffect_btn_website->setOffset(0,0);
    shadowEffect_btn_website->setColor(Qt::gray);
    shadowEffect_btn_website->setBlurRadius(5);
    ui->btn_website->setGraphicsEffect(shadowEffect_btn_website);

    QGraphicsDropShadowEffect *shadowEffect_btn_coolapk = new QGraphicsDropShadowEffect();
    shadowEffect_btn_coolapk->setOffset(0,0);
    shadowEffect_btn_coolapk->setColor(Qt::gray);
    shadowEffect_btn_coolapk->setBlurRadius(5);
    ui->btn_coolapk->setGraphicsEffect(shadowEffect_btn_coolapk);

    QGraphicsDropShadowEffect *shadowEffect_btn_github = new QGraphicsDropShadowEffect();
    shadowEffect_btn_github->setOffset(0,0);
    shadowEffect_btn_github->setColor(Qt::gray);
    shadowEffect_btn_github->setBlurRadius(5);
    ui->btn_github->setGraphicsEffect(shadowEffect_btn_github);

    QGraphicsDropShadowEffect *shadowEffect_btn_money = new QGraphicsDropShadowEffect();
    shadowEffect_btn_money->setOffset(0,0);
    shadowEffect_btn_money->setColor(Qt::gray);
    shadowEffect_btn_money->setBlurRadius(5);
    ui->btn_money->setGraphicsEffect(shadowEffect_btn_money);
    QGraphicsDropShadowEffect *shadowEffect_btn_money2 = new QGraphicsDropShadowEffect();
    shadowEffect_btn_money2->setOffset(0,0);
    shadowEffect_btn_money2->setColor(Qt::gray);
    shadowEffect_btn_money2->setBlurRadius(5);
    ui->btn_money_2->setGraphicsEffect(shadowEffect_btn_money2);
    QGraphicsDropShadowEffect *shadowEffect_btn_money3 = new QGraphicsDropShadowEffect();
    shadowEffect_btn_money3->setOffset(0,0);
    shadowEffect_btn_money3->setColor(Qt::gray);
    shadowEffect_btn_money3->setBlurRadius(5);
    ui->btn_money_3->setGraphicsEffect(shadowEffect_btn_money3);
    QGraphicsDropShadowEffect *shadowEffect_btn_money4 = new QGraphicsDropShadowEffect();
    shadowEffect_btn_money4->setOffset(0,0);
    shadowEffect_btn_money4->setColor(Qt::gray);
    shadowEffect_btn_money4->setBlurRadius(5);
    ui->btn_money_4->setGraphicsEffect(shadowEffect_btn_money4);

    QGraphicsDropShadowEffect *shadowEffect_btn_version = new QGraphicsDropShadowEffect();
    shadowEffect_btn_version->setOffset(0,0);
    shadowEffect_btn_version->setColor(Qt::gray);
    shadowEffect_btn_version->setBlurRadius(5);

    ui->btn_version->setGraphicsEffect(shadowEffect_btn_version);

    ui->btn_money->hide();
    ui->btn_money_3->hide();
    ui->btn_money_4->hide();
}

about::~about()
{
    delete ui;
}

void about::on_btn_website_clicked()
{
    QDesktopServices::openUrl(QUrl("https://lapplandsp.github.io/QtAdb-pages/", QUrl::TolerantMode));
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

