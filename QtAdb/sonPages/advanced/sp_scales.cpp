#include "sp_scales.h"
#include "ui_sp_scales.h"

sp_scales::sp_scales(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_scales)
{
    ui->setupUi(this);

    process = new adbProcess();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    setShadow(ui->back_to_basePage);
    setShadow(ui->pushButton);
    setShadow(ui->pushButton_animation);
    setShadow(ui->pushButton_transition);
    setShadow(ui->pushButton_window);
    setShadow(ui->current_window);
    setShadow(ui->current_animator);
    setShadow(ui->current_transition);
    setShadow(ui->label_animator);
    setShadow(ui->label_window);
    setShadow(ui->label_transition);

    ui->lineEdit_window->setPlaceholderText("修改为");
    ui->lineEdit_animator->setPlaceholderText("修改为");
    ui->lineEdit_transition->setPlaceholderText("修改为");

    ui->lineEdit_transition->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_animator->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_window->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
}

sp_scales::~sp_scales()
{
    delete ui;
}

void sp_scales::setDev(device device)
{
    dev = device;
    qDebug() << "//////////////////////////////////////////////" << dev.model;
    refresh();
}


void sp_scales::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}

void sp_scales::refresh()
{
    /*
    pageListItemStruct *screen_resolution = initStruct(devInfo);
    screen_resolution->item->setText_title("屏幕分辨率");
    screen_resolution->item->setPic(":/ico/image/ico/fullscreen-line.svg");
    screen_resolution->thread->initThread("adb shell wm size", dev, ": ");
    QEventLoop::connect(screen_resolution->thread,SIGNAL(signal_output(QString)),screen_resolution->item,SLOT(slot_setText_profile(QString)));
    screen_resolution->thread->start();
    screen_resolution->item->setSelectable();
    devInfo->addItemsToList(screen_resolution->item);
    */


    adbThread *thread_animator = new adbThread(this);
    thread_animator->initThread("adb shell settings get global animator_duration_scale", dev);
    QEventLoop::connect(thread_animator,SIGNAL(signal_output(QString)),this,SLOT(setText_animator(QString)));
    thread_animator->start();

    adbThread *thread_transition = new adbThread(this);
    thread_transition->initThread("adb shell settings get global transition_animation_scale", dev);
    QEventLoop::connect(thread_transition,SIGNAL(signal_output(QString)),this,SLOT(setText_transition(QString)));
    thread_transition->start();

    adbThread *thread_window = new adbThread(this);
    thread_window->initThread("adb shell settings get global window_animation_scale", dev);
    QEventLoop::connect(thread_window,SIGNAL(signal_output(QString)),this,SLOT(setText_window(QString)));
    thread_window->start();

    //ui->current_animator->setText("当前：" + process->run("adb shell settings get global animator_duration_scale",dev).simplified());
    //ui->current_transition->setText("当前：" + process->run("adb shell settings get global transition_animation_scale",dev).simplified());
    //ui->current_window->setText("当前：" + process->run("adb shell settings get global window_animation_scale",dev).simplified());
    ui->lineEdit_transition->clear();
    ui->lineEdit_window->clear();
    ui->lineEdit_animator->clear();
}

void sp_scales::on_pushButton_animation_clicked()
{
    //QMessageBox::StandardButton result=QMessageBox::warning(NULL, "动画时长缩放","确定修改");
    process->run("adb shell settings put global animator_duration_scale " + ui->lineEdit_animator->text().simplified(), dev);
    refresh();
}

void sp_scales::on_pushButton_transition_clicked()
{
    process->run("adb shell settings put global transition_animation_scale " + ui->lineEdit_transition->text().simplified(), dev);
    refresh();
}

void sp_scales::on_pushButton_window_clicked()
{
    process->run("adb shell settings put global window_animation_scale " + ui->lineEdit_window->text().simplified(), dev);
    refresh();
}

void sp_scales::setText_animator(QString s)
{
    ui->current_animator->setText("当前：" + s.simplified());
}

void sp_scales::setText_transition(QString s)
{
    ui->current_transition->setText("当前：" + s.simplified());
}

void sp_scales::setText_window(QString s)
{
    ui->current_window->setText("当前：" + s.simplified());
}
