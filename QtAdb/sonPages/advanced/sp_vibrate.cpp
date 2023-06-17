#include "sp_vibrate.h"
#include "qscrollbar.h"
#include "ui_sp_vibrate.h"

sp_vibrate::sp_vibrate(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_vibrate)
{
    ui->setupUi(this);

    process = new adbProcess();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    QFile file("://qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(file.readAll());

    ui->lineEdit_all->setPlaceholderText("0关   1开");
    ui->lineEdit_all_charge->setPlaceholderText("0关   1开");
    ui->lineEdit_all_haptic->setPlaceholderText("0关   1开");
    ui->lineEdit_all_ring->setPlaceholderText("0关   1开");
    ui->lineEdit_haptic->setPlaceholderText("请输入等级");
    ui->lineEdit_haptic_hardware->setPlaceholderText("请输入等级");
    ui->lineEdit_media->setPlaceholderText("请输入等级");
    ui->lineEdit_alarm->setPlaceholderText("请输入等级");
    ui->lineEdit_ring->setPlaceholderText("请输入等级");
    ui->lineEdit_notification->setPlaceholderText("请输入等级");

    ui->lineEdit_alarm->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_all->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_all_charge->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_all_haptic->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_all_ring->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_haptic->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_haptic_hardware->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_media->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_notification->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));
    ui->lineEdit_ring->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*))$")));

    setShadow(ui->label_all);
    setShadow(ui->label_all_charge);
    setShadow(ui->label_all_haptic);
    setShadow(ui->label_all_ring);
    setShadow(ui->label_level_haptic);
    setShadow(ui->label_level_haptic_hardware);
    setShadow(ui->label_level_alarm);
    setShadow(ui->label_level_media);
    setShadow(ui->label_level_notification);
    setShadow(ui->label_level_ring);

    setShadow(ui->current_all);
    setShadow(ui->current_all_charge);
    setShadow(ui->current_all_haptic);
    setShadow(ui->current_all_ring);
    setShadow(ui->current_haptic);
    setShadow(ui->current_haptic_hardware);
    setShadow(ui->current_alarm);
    setShadow(ui->current_media);
    setShadow(ui->current_ring);
    setShadow(ui->current_notification);

    setShadow(ui->pushButton_all);
    setShadow(ui->pushButton_all_charge);
    setShadow(ui->pushButton_all_ring);
    setShadow(ui->pushButton_all_thaptic);
    setShadow(ui->pushButton_alarm);
    setShadow(ui->pushButton_haptic);
    setShadow(ui->pushButton_media);
    setShadow(ui->pushButton_haptic_hardware);
    setShadow(ui->pushButton_ring);
    setShadow(ui->pushButton_notificaton);

    setShadow(ui->back_to_basePage);
    setShadow(ui->pushButton);
}

sp_vibrate::~sp_vibrate()
{
    delete ui;
}

void sp_vibrate::setDev(device device)
{
    dev = device;
    qDebug() << "//////////////////////////////////////////////" << dev.model;
    refresh();
}

void sp_vibrate::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}


void sp_vibrate::refresh()
{
    /*
     *     void setText_all(QString);
    void setText_all_haptics(QString);
    void setText_all_charge(QString);
    void setText_all_ring(QString);
    void setText_level_haptic(QString);
    void setText_level_haptic_hardware(QString);
    void setText_level_alarm(QString);
    void setText_level_media(QString);
    void setText_level_notification(QString);
    void setText_level_ring(QString);
     *
     * */
    adbThread *thread_all = new adbThread(this);
    thread_all->initThread("adb shell settings get system vibrate_on", dev);
    QEventLoop::connect(thread_all,SIGNAL(signal_output(QString)),this,SLOT(setText_all(QString)));
    thread_all->start();

    adbThread *thread_all_haptics = new adbThread(this);
    thread_all_haptics->initThread("adb shell settings get system haptic_feedback_enabled", dev);
    QEventLoop::connect(thread_all_haptics,SIGNAL(signal_output(QString)),this,SLOT(setText_all_haptics(QString)));
    thread_all_haptics->start();

    adbThread *thread_all_ring = new adbThread(this);
    thread_all_ring->initThread("adb shell settings get system vibrate_when_ringing", dev);
    QEventLoop::connect(thread_all_ring,SIGNAL(signal_output(QString)),this,SLOT(setText_all_ring(QString)));
    thread_all_ring->start();

    adbThread *thread_all_charge = new adbThread(this);
    thread_all_charge->initThread("adb shell settings get system charging_vibration_enabled", dev);
    QEventLoop::connect(thread_all_charge,SIGNAL(signal_output(QString)),this,SLOT(setText_all_charge(QString)));
    thread_all_charge->start();

    adbThread *thread_level_haptics = new adbThread(this);
    thread_level_haptics->initThread("adb shell settings get system haptic_feedback_intensity", dev);
    QEventLoop::connect(thread_level_haptics,SIGNAL(signal_output(QString)),this,SLOT(setText_level_haptics(QString)));
    thread_level_haptics->start();

    adbThread *thread_level_haptics_hardware = new adbThread(this);
    thread_level_haptics_hardware->initThread("adb shell settings get system hardware_haptic_feedback_intensity", dev);
    QEventLoop::connect(thread_level_haptics_hardware,SIGNAL(signal_output(QString)),this,SLOT(setText_level_haptics_hardware(QString)));
    thread_level_haptics_hardware->start();

    adbThread *thread_level_notification = new adbThread(this);
    thread_level_notification->initThread("adb shell settings get system notification_vibration_intensity", dev);
    QEventLoop::connect(thread_level_notification,SIGNAL(signal_output(QString)),this,SLOT(setText_level_notification(QString)));
    thread_level_notification->start();

    adbThread *thread_level_alarm = new adbThread(this);
    thread_level_alarm->initThread("adb shell settings get system alarm_vibration_intensity", dev);
    QEventLoop::connect(thread_level_alarm,SIGNAL(signal_output(QString)),this,SLOT(setText_level_alarm(QString)));
    thread_level_alarm->start();

    adbThread *thread_level_media = new adbThread(this);
    thread_level_media->initThread("adb shell settings get system media_vibration_intensity", dev);
    QEventLoop::connect(thread_level_media,SIGNAL(signal_output(QString)),this,SLOT(setText_level_media(QString)));
    thread_level_media->start();

    adbThread *thread_level_ring = new adbThread(this);
    thread_level_ring->initThread("adb shell settings get system ring_vibration_intensity", dev);
    QEventLoop::connect(thread_level_ring,SIGNAL(signal_output(QString)),this,SLOT(setText_level_ring(QString)));
    thread_level_ring->start();

    //ui->current_animator->setText("当前：" + process->run("adb shell settings get global animator_duration_scale",dev).simplified());
    //ui->current_transition->setText("当前：" + process->run("adb shell settings get global transition_animation_scale",dev).simplified());
    //ui->current_window->setText("当前：" + process->run("adb shell settings get global window_animation_scale",dev).simplified());
    //ui->lineEdit_transition->clear();
    //ui->lineEdit_window->clear();
    //ui->lineEdit_animator->clear();
    ui->lineEdit_all->clear();
    ui->lineEdit_all_charge->clear();
    ui->lineEdit_all_haptic->clear();
    ui->lineEdit_all_ring->clear();
    ui->lineEdit_haptic->clear();
    ui->lineEdit_haptic_hardware->clear();
    ui->lineEdit_alarm->clear();
    ui->lineEdit_media->clear();
    ui->lineEdit_notification->clear();
    ui->lineEdit_ring->clear();
}

void sp_vibrate::setText_all(QString s)
{
    ui->current_all->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_all_haptics(QString s)
{
    ui->current_all_haptic->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_all_charge(QString s)
{
    ui->current_all_charge->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_all_ring(QString s)
{
    ui->current_all_ring->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_haptics(QString s)
{
    ui->current_haptic->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_haptics_hardware(QString s)
{
    ui->current_haptic_hardware->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_alarm(QString s)
{
    ui->current_alarm->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_media(QString s)
{
    ui->current_media->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_notification(QString s)
{
    ui->current_notification->setText("当前：" + s.simplified());
}

void sp_vibrate::setText_level_ring(QString s)
{
    ui->current_ring->setText("当前：" + s.simplified());
}

void sp_vibrate::on_pushButton_all_clicked()
{
    process->run("adb shell settings put system vibrate_on " + ui->lineEdit_all->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_all_thaptic_clicked()
{
    process->run("adb shell settings put system haptic_feedback_enabled " + ui->lineEdit_all_haptic->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_all_ring_clicked()
{
    process->run("adb shell settings put system vibrate_when_ringing " + ui->lineEdit_all_ring->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_all_charge_clicked()
{
    process->run("adb shell settings put system charging_vibration_enabled " + ui->lineEdit_all_charge->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_haptic_clicked()
{
    process->run("adb shell settings put system haptic_feedback_intensity " + ui->lineEdit_haptic->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_haptic_hardware_clicked()
{
    process->run("adb shell settings put system hardware_haptic_feedback_intensity " + ui->lineEdit_haptic_hardware->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_notificaton_clicked()
{
    process->run("adb shell settings put system notification_vibration_intensity " + ui->lineEdit_notification->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_alarm_clicked()
{
    process->run("adb shell settings put system alarm_vibration_intensity " + ui->lineEdit_alarm->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_media_clicked()
{
    process->run("adb shell settings put system media_vibration_intensity " + ui->lineEdit_media->text().simplified(), dev);
    refresh();
}


void sp_vibrate::on_pushButton_ring_clicked()
{
    process->run("adb shell settings put system ring_vibration_intensity " + ui->lineEdit_ring->text().simplified(), dev);
    refresh();
}

