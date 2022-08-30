#include "sp_captive_portal.h"
#include "ui_sp_captive_portal.h"

sp_captive_portal::sp_captive_portal(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_captive_portal)
{
    ui->setupUi(this);
    setParent(parent);

    process = new adbProcess();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    setShadow(ui->label);
    setShadow(ui->label_3);
    setShadow(ui->label_5);
    setShadow(ui->android_version);
    setShadow(ui->back_to_basePage);
    setShadow(ui->current_server);
    //setShadow(ui->delete_directly);
    setShadow(ui->restore);
    setShadow(ui->modify);
    //setShadow(ui->comboBox);
    setShadow(ui->pushButton);

    QStringList serverLists;
    serverLists.append("connect.rom.miui.com/generate_204");
    serverLists.append("connectivitycheck.platform.hicloud.com/generate_204");
    serverLists.append("wifi.vivo.com.cn/generate_204");
    serverLists.append("www.qualcomm.cn/generate_204");
    serverLists.append("edge.microsoft.com/captiveportal/generate_204");
    serverLists.append("cp.cloudflare.com/generate_204");
    serverLists.append("g.cn/generate_204");
    serverLists.append("google.cn/generate_204");
    serverLists.append("dl.google.com/generate_204");
    serverLists.append("google.com");
    ui->comboBox->addItems(serverLists);
    ui->comboBox->setStyleSheet("QComboBox{color:black; border:0px; border-bottom:1px solid #BDBDBD; border-radius:0px; background-color:rgba(255,255,255,255);}"
                                "QComboBox::drop-down{border: 0px solid rgba(255,255,255,0);background-color:rgba(255,255,255,0);border-bottom-right-radius: 0px;}"
                                "QComboBox QAbstractItemView{border:1px solid #BDBDBD;border-radius:0px 0px 0px 0px;outline: 0px;}"
                                "QComboBox QAbstractItemView::item{height:30px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;}"
                                "QComboBox QAbstractItemView::item:hover{height:30px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black}"
                                "QComboBox QAbstractItemView::item:selected{height:30px;border:1px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black}"
                                );



    //process->run("adb shell settings get secure android_id", dev).simplified();
}

sp_captive_portal::~sp_captive_portal()
{
    delete ui;
}

void sp_captive_portal::setDev(device device)
{
    dev = device;
    refresh();
}

void sp_captive_portal::setShadow(QWidget* wgt)
{
    QGraphicsDropShadowEffect *shadowEffect_widget = new QGraphicsDropShadowEffect(this);
    shadowEffect_widget->setOffset(0,0);
    shadowEffect_widget->setColor(Qt::gray);
    shadowEffect_widget->setBlurRadius(5);
    wgt->setGraphicsEffect(shadowEffect_widget);
}

void sp_captive_portal::refresh()
{
    ui->android_version->setText(process->run("adb shell getprop ro.build.version.release", dev).simplified());
    QString ver = ui->android_version->text().simplified().simplified()[0];
    if(ver.toInt() < 7 && ver.toInt() >= 5)
    {
        ui->current_server->setVisible(true);
        ui->label->setVisible(true);
        //adb shell settings get global captive_portal_server
        ui->current_server->setText(process->run("adb shell settings get global captive_portal_server", dev).simplified());
    }
    else
    {
        ui->current_server->setVisible(false);
        ui->label->setVisible(false);
    }


    ui->comboBox->setPlaceholderText("服务器未选择");
    ui->comboBox->setCurrentIndex(-1);
}

void sp_captive_portal::on_modify_clicked()
{
    if(ui->comboBox->currentIndex() >= 0)
    {
        QMessageBox::StandardButton result=QMessageBox::question(NULL, "修改","您确定要将验证服务器修改为" + ui->comboBox->currentText() + "吗？");
        if(result)
        {
                QString ver = ui->android_version->text().simplified().simplified()[0];
                if(ver.toInt() < 7 && ver.toInt() >= 5)
                {
                    //adb shell settings put global captive_portal_server
                    QString cmd = "adb shell settings put global captive_portal_server ";
                    cmd.append("http://");
                    cmd.append(ui->comboBox->currentText());
                    qDebug() << "cmd = " << cmd;
                    process->run(cmd, dev);
                }
                else
                {
                    QString cmd_http = "adb shell settings put global captive_portal_http_url ";
                    cmd_http.append("http://");
                    cmd_http.append(ui->comboBox->currentText());

                    QString cmd_https = "adb shell settings put global captive_portal_https_url ";
                    cmd_https.append("https://");
                    cmd_https.append(ui->comboBox->currentText());
                    process->run(cmd_http, dev);
                    process->run(cmd_https,dev);
                }
                QMessageBox::information(NULL, "修改","已修改");


            refresh();
        }
    }
    else
    {
        ui->comboBox->setPlaceholderText("服务器未选择");
    }
}

void sp_captive_portal::on_restore_clicked()
{
    QMessageBox::StandardButton result=QMessageBox::question(NULL, "重置","您确定要重置吗？");

    if(result)
    {
        QString ver = ui->android_version->text().simplified().simplified()[0];
        if(ver.toInt() < 7 && ver.toInt() >= 5)
        {
            //adb shell settings put global captive_portal_server
            QString cmd = "adb shell settings delete global captive_portal_server";
            process->run(cmd, dev);
        }
        else
        {
            QString cmd_http = "adb shell settings delete global captive_portal_https_url";
            QString cmd_https = "adb shell settings delete global captive_portal_http_url";
            process->run(cmd_http, dev);
            process->run(cmd_https,dev);
        }
        QMessageBox::information(NULL, "重置","已重置");
        refresh();
    }
}



//屎山
void sp_captive_portal::on_delete_directly_clicked()
{

}
