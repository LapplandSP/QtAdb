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


    thread_installer = new adbThread();

    ui->lineEdit_name->setText(name);
    ui->lineEdit_name->isReadOnly();
    ui->lineEdit_installer->isReadOnly();
    ui->lineEdit_path->isReadOnly();
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
    QString cmd = "adb shell pm uninstall ";
    cmd.append(name);
    process->run(cmd,dev);

    emit packageChanged();
    this->close();
}


void tp_packageProfile::on_clear_clicked()
{
    QString cmd = "adb shell pm clear ";
    cmd.append(name);
    process->run(cmd,dev);
}


void tp_packageProfile::on_enable_clicked()
{
    QString cmd = "adb shell pm enable ";
    cmd.append(name);
    process->run(cmd,dev);

    emit packageChanged();
}


void tp_packageProfile::on_disable_clicked()
{
    QString cmd = "adb shell pm disable ";
    cmd.append(name);
    process->run(cmd,dev);

    emit packageChanged();
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
