#include "tp_packageprofile.h"
#include "ui_tp_packageprofile.h"

tp_packageProfile::tp_packageProfile(QWidget *parent ,QString packageName) :
    QWidget(parent),
    ui(new Ui::tp_packageProfile)
{
    ui->setupUi(this);

    this->setWindowTitle("软件包 ' "+packageName+" '");
    name = packageName;
    explainer = new textExplainer();
    process = new adbProcess();

    thread_file = new adbThread();

    //this->setStyleSheet("background-color:white;");


    thread_installer = new adbThread();

    ui->lineEdit_name->setText(name);
    ui->lineEdit_name->isReadOnly();
    ui->lineEdit_installer->isReadOnly();
    ui->lineEdit_path->isReadOnly();

    setShadow(ui->label);
    setShadow(ui->label_2);
    setShadow(ui->label_3);
    setShadow(ui->tips);
    setShadow(ui->uninstall);
    setShadow(ui->clear);
    setShadow(ui->enable);
    setShadow(ui->disable);

    //this->setStyleSheet("background-color:white;");
}

tp_packageProfile::~tp_packageProfile()
{
    delete ui;
}

void tp_packageProfile::set_file(QString s)
{
    ui->lineEdit_path->setText(explainer->get_words_after(s,"package:"));
}

void tp_packageProfile::set_installer(QString s)
{
    ui->lineEdit_installer->setText(explainer->get_words_after(s,"installer="));
}

void tp_packageProfile::on_uninstall_clicked()
{
    if(uninstall_clicked)
    {
        ui->tips->setText("已执行「卸载」命令，本窗口将关闭");

        QString cmd = "adb shell pm uninstall ";
        cmd.append(name);
        process->run(cmd,dev);

        emit packageChanged();
        this->close();

        uninstall_clicked = false;
    }
    else
    {
        ui->tips->setText("再次点击以卸载，卸载后本窗口将关闭");
        uninstall_clicked = true;
    }
}


void tp_packageProfile::on_clear_clicked()
{
    if(clear_clicked)
    {
        ui->tips->setText("已执行「清除应用数据」命令");

        QString cmd = "adb shell pm clear ";
        cmd.append(name);
        process->run(cmd,dev);

        clear_clicked = false;
    }
    else
    {
        ui->tips->setText("再次点击以清除");
        clear_clicked = true;
    }
}


void tp_packageProfile::on_enable_clicked()
{
    if(enable_clicked)
    {
        ui->tips->setText("已执行「启用」命令");

        QString cmd = "adb shell pm enable ";
        cmd.append(name);
        process->run(cmd,dev);

        emit packageChanged();

        enable_clicked = false;
    }
    else
    {
        ui->tips->setText("再次点击以启用");
        enable_clicked = true;
    }
}


void tp_packageProfile::on_disable_clicked()
{
    if(disable_clicked)
    {
        ui->tips->setText("已执行「停用」命令");

        QString cmd = "adb shell pm disable ";
        cmd.append(name);
        process->run(cmd,dev);

        emit packageChanged();

        disable_clicked = false;
    }
    else
    {
        ui->tips->setText("再次点击以停用");
        disable_clicked = true;
    }

}

void tp_packageProfile::setDevice(device d)
{
    dev = d;

    QString command_file = "adb shell pm list packages -f ";
    command_file.append(name);
    thread_file->initThread(command_file , dev);
    connect(thread_file,SIGNAL(signal_output(QString)),this,SLOT(set_file(QString)));
    thread_file->start();

    QString command_installer = "adb shell pm list packages -i ";
    command_installer.append(name);
    thread_installer->initThread(command_installer , dev);
    connect(thread_installer,SIGNAL(signal_output(QString)),this,SLOT(set_installer(QString)));
    thread_installer->start();
}

void tp_packageProfile::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}
