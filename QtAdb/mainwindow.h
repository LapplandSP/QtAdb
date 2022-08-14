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
#include "adbprocess.h"
#include "textexplainer.h"
#include "indexlistitem.h"
#include "basepage.h"
#include "pagemaker.h"
#include "threads/thread_createpage.h"
#include "about.h"

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

    bool taiChi = true;
    QTimer *taiChiTimer;

    basePage * currentPage;
    animationWidget * tmpPage;
    about * WCMPage2;
};

#endif // MAINWINDOW_H
