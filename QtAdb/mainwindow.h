#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QSizePolicy>
#include <QScroller>
#include <QLineEdit>
#include "adbprocess.h"
#include "textexplainer.h"
#include "indexlistitem.h"
#include "basepage.h"
#include "pagemaker.h"
#include "threads/thread_createpage.h"
#include "welcomepage.h"

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
    //void createBasePage(int, QWidget*, device, basePage*);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    adbProcess *process;
    textExplainer *explainer;
    pageMaker *maker;
    QMovie *movie;

    QWidget * getInfo;
    QLineEdit * le_outIp;
    QLineEdit * le_outPort;
    QLineEdit * le_ipAddr;
    QLineEdit * le_port;
    QLineEdit * le_code;

    //QThread* sub;
    //thread_createPage * thread_BPCreator;

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
    void playLoadingGif();
    void stopLoadingGif();

    void on_adbKillerBtn_clicked();

    void on_WIFIBtn_clicked();
    void connectWIFIDev();


    //void emit_signal_createBasePage(int key);
    /*(int key, QWidget *parent, device dev)*/

    void on_WSABtn_clicked();

private:
    Ui::MainWindow *ui;

    void initEnvironmentPATH();
    void addIndexItems();
    void setStyles();
    void displayWelcomePage();

    basePage * currentPage;
    animationWidget * tmpPage;
    welcomePage * WCMPage;
};
#endif // MAINWINDOW_H
