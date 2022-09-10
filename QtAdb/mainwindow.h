#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QSizePolicy>
#include <QScroller>
#include <QLineEdit>
#include <QMouseEvent>
#include <QTextCodec>
#include <QRegExp>
#include "adbprocess.h"
#include "textexplainer.h"
#include "indexlistitem.h"
#include "basepage.h"
#include "pagemaker.h"
#include "about.h"
#include "usb_listener.h"
#include "threads/thread_monitor.h"
#include "devitem.h"
#include "abstract/comboboxlistwidget.h"

#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>
#include <QMovie>

#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void adbDeviceChanged();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    adbProcess *process;
    textExplainer *explainer;
    pageMaker *maker;

    QWidget * getInfo;
    QLineEdit * le_outIp;
    QLineEdit * le_outPort;
    QLineEdit * le_ipAddr;
    QLineEdit * le_port;
    QLineEdit * le_code;

    int current_device;
    QList<device> devList;
    indexListItem listItems[10];
    void refreshDevList();
    void addItemToIndex(indexListItem *itemWidget);
    void lock();
    void unlock();
    void hideCurrentPage();

private slots:
    void on_refreshButton_clicked();
    void setCurrentDevice(int index);
    void initBasePage(int key);
    void initSonPage(int key);
    void on_adbKillerBtn_clicked();

    void on_WIFIBtn_clicked();
    void connectWIFIDev();

    void on_WSABtn_clicked();
    void slot_taiChi();

    void on_cmdBtn_clicked();

private:
    Ui::MainWindow *ui;

    void initEnvironmentPATH();
    void addIndexItems();
    void setStyles();

    bool taiChi = true;     //界面锁定定时器
    bool liangYi = false;   //判断刷新按钮槽函数是被谁调用：false：刷新按钮 click（）调用 ； true： 热插拔相关
    bool bagua = true;      //忘了是干啥的了

    //布尔 太极 为 真;

    bool firstBoot = true;
    QTimer *taiChiTimer;
    QTimer *baguaTimer;
    QTimer *siXiangTimer = NULL;

    basePage * currentPage;
    animationWidget * tmpPage;
    about * WCMPage2;
    usb_listener *listener;

    thread_monitor *thread_mon = NULL;

    comboboxListWidget *view;

public slots:
    void DevicePlugIn();
    void DevicePlugOut();
    void DeviceChanged();
    void slot_refreshDevList();     //如下
    void refreshDevListLater();     //与信号 usb_listener 连接的槽，在设备热插拔后启动定时器，超时1s后调用slot_refreshDevList();
    void slot_update_monitor(float,float);
    void reset_monitorBars();
};

#endif // MAINWINDOW_H
