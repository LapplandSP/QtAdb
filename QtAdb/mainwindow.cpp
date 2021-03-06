#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * 待实现：
 * ******************************adbProcess 的read std output不应与主页面位于同一个线程
 * 显示输出
 * 代码规范化，提升封装程度
 * 写注释
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initEnvironmentPATH();

    /*加载动画GIF*/
    movie = new QMovie(":/gif/image/gif/final.gif");
    //sub = new QThread;

    /*页面内容更新线程*/
    //thread_BPCreator = new thread_createPage;
    //thread_BPCreator->moveToThread(sub);
    //sub->start();

    /*currentPage指针*/
    currentPage = NULL;
    WCMPage = NULL;

    /*devList 中的当前设备索引*/
    current_device = 0;
    ui->comboBox->setPlaceholderText("请先选择设备");

    /*连接信号与槽*/
    connect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //更改当前设备
    //connect(this->ui->indexList,SIGNAL(currentRowChanged(int)),this,SLOT(playLoadingGif()));      //播放加载动画
    connect(this->ui->indexList,SIGNAL(currentRowChanged(int)),this,SLOT(initBasePage(int)));       //创建并更改当前页面

    /*设置界面*/
    addIndexItems();    //设置左侧目录
    setStyles();        //设置样式

    /*初始化对象*/
    process = new adbProcess();
    explainer = new textExplainer();
    maker = new pageMaker();

    /*启动ADB，将延长页面创建时间，在此期间显示启动界面*/
    process->run("adb server");
    refreshDevList();

    /*用户未选择设备前，锁定界面*/
    lock();
    qDebug() << "1";
    displayWelcomePage();
    qDebug() << "2";
}

MainWindow::~MainWindow()
{
    delete process;
    delete explainer;
    delete ui;
}

void MainWindow::initEnvironmentPATH()              //方法：设置环境变量
{
    QString envPath = qgetenv("PATH");      //获取当前环境变量
    QString appDirPath = QApplication::applicationDirPath();    //获取程序所在位置
    QString userPath = appDirPath + "\\platform-tools";     //向字符串中添加ADB环境
    envPath += QDir::toNativeSeparators(userPath).prepend(';');
    qputenv("PATH",envPath.toStdString().c_str());          //更改环境变量
    //qDebug() << envPath.toStdString().c_str();
}

void MainWindow::refreshDevList()                   //方法：刷新设备列表
{
    ui->comboBox->clear();      //清空combobox
    devList.clear();            //清空设备列表

    devList = explainer->getDevList_windows(process->run("adb devices -l"));    //重新赋值

    /*将设备信息传入 List l ，并将l的值显示在combobox中*/
    QStringList l;
    l.clear();
    for (int i = 0 ; i < devList.size() ; i++ )
    {
        QString devItem =devList[i].state + " " + explainer->get_words_after(devList[i].device_product, ":") + " " + explainer->get_words_after(devList[i].model, ":");
        l.append(devItem);
    }
    ui->comboBox->addItems(l);

    current_device = 0;         //重设当前设备
}

void MainWindow::on_refreshButton_clicked()         //槽：按下刷新按钮
{
    refreshDevList();
    lock();
    if(currentPage != NULL)
    {
        currentPage->~QWidget();
        currentPage = NULL;
    }
    displayWelcomePage();
}

void MainWindow::setCurrentDevice(int index)        //槽：改变所选设备
{
    current_device = index;
    unlock();
}

void MainWindow::initBasePage(int key)              //槽：生成basePages
{
    if(WCMPage != NULL)         //销毁欢迎页面
    {
        //currentPage->setDisabled(true);
        //delete currentPage;
        WCMPage->~welcomePage();
        WCMPage = NULL;
    }

    if(currentPage != NULL)         //销毁上一个basePage
    {
        //currentPage->setDisabled(true);
        //delete currentPage;
        currentPage->~QWidget();
        currentPage = NULL;
    }

    currentPage = new QWidget(this);
    currentPage = maker->createPageWithKey(key,ui->page,devList[current_device]);   //究极开销
    qDebug() << "currentPage = maker->createPageWithKey(key,ui->page,devList[current_device]); ended";
    ui->verticalLayout_2->addWidget(currentPage);
}

void MainWindow::addItemToIndex(indexListItem *itemWidget)  //方法：向indexist中添加单个item
{
    QListWidgetItem * tmpItem = new QListWidgetItem();
    ui->indexList->addItem(tmpItem);
    ui->indexList->setItemWidget(tmpItem, itemWidget);
}

void MainWindow::addIndexItems()                    //方法：初始化向indexList中添加的item，完成indexList创建。
{
/*
        basePage *wgt = new basePage(this);
        currentPage = wgt;*/

    indexListItem *devInfo = new indexListItem(this->ui->indexList);
    devInfo->setText("设备信息");
    devInfo->setPic("image:url(:/ico/image/ico/smartphone-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(devInfo);
    /*
    QListWidgetItem * tmpItem = new QListWidgetItem();
    ui->indexList->addItem(tmpItem);
    ui->indexList->setItemWidget(tmpItem, devInfo);*/

    indexListItem *activator = new indexListItem(this->ui->indexList);
    activator->setText("激活");
    activator->setPic("image:url(:/ico/image/ico/pulse-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(activator);

    indexListItem *apps = new indexListItem(this->ui->indexList);
    apps->setText("应用");
    apps->setPic("image:url(:/ico/image/ico/google-play-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(apps);

    indexListItem *devControl = new indexListItem(this->ui->indexList);
    devControl->setText("设备控制");
    devControl->setPic("image:url(:/ico/image/ico/remote-control-2-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(devControl);

    indexListItem *recovery = new indexListItem(this->ui->indexList);
    recovery->setText("Recovery");
    recovery->setPic("image:url(:/ico/image/ico/registered-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(recovery);

    indexListItem *about = new indexListItem(this->ui->indexList);
    about->setText("关于");
    about->setPic("image:url(:/ico/image/ico/about/information-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(about);

    ui->indexList->setResizeMode(QListView::Adjust);
}

void MainWindow::lock()                             //方法：锁定mainwindow中控件
{
    ui->indexList->setEnabled(false);
    //currentPage->setEnabled(false);
    ui->page->setEnabled(false);
}

void MainWindow::unlock()                           //方法：解锁mainwindow中的控件
{
    ui->indexList->setEnabled(true);
    //currentPage->setEnabled(true);
    ui->page->setEnabled(true);
}

void MainWindow::setStyles()                        //方法：设置样式
{
    setWindowTitle("QtAdb");
    setWindowIcon(QIcon(":/ico/image/ico/logo.svg"));

    this->setWindowOpacity(0.99);

    ui->horizontalLayout_3->setAlignment(Qt::AlignLeft);
    ui->verticalLayout_2->setAlignment(Qt::AlignTop);

    ui->indexList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->indexList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->indexList->setStyleSheet("QListWidget{background-color:rgba(255,255,255,0);border-width:0px;border-radius:4px;outline:0px;}"
                                 "QListWidget::item{background-color:rgba(255,255,255,0.9);border-width:0px;border-radius:4px;margin:4px 0px 0px 0px;}"
                                 "QListWidget::item:hover{background-color:#f5f6f9;padding:5px;}"
                                 "QListWidget::item::selected{background-color:#f5f6f9;color:black;padding:10px;}"
                                 "QListView::item{height:35px;}"
                                 );

    ui->comboBox->setStyleSheet("QComboBox{color:black;border-bottom:1px solid #BDBDBD;border-radius:0px;background-color:transparent;}"
                                "QComboBox::drop-down{border: 0px solid rgba(255,255,255,0);background-color:rgba(255,255,255,0);border-bottom-right-radius: 0px;}"
                                "QComboBox QAbstractItemView{border:1px solid #BDBDBD;border-radius:0px 0px 0px 0px;outline: 0px;}"
                                "QComboBox QAbstractItemView::item{height:30px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;}"
                                "QComboBox QAbstractItemView::item:hover{height:30px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black}"
                                "QComboBox QAbstractItemView::item:selected{height:30px;border:1px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black}"
                                );

    ui->refreshButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;}"
                                     "QPushButton:hover{background-color:rgba(255,255,255,0.7);}"
                                     "QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");
    ui->iconLabel->setStyleSheet("background-color:transparent;");
    ui->fakeSpacer->setStyleSheet("background-color:transparent;");

    QGraphicsDropShadowEffect *shadowEffect_refreshButton = new QGraphicsDropShadowEffect();
    shadowEffect_refreshButton->setOffset(0,0);
    shadowEffect_refreshButton->setColor(Qt::gray);
    shadowEffect_refreshButton->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_killAdbBtn = new QGraphicsDropShadowEffect();
    shadowEffect_killAdbBtn->setOffset(0,0);
    shadowEffect_killAdbBtn->setColor(Qt::gray);
    shadowEffect_killAdbBtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_testBtn = new QGraphicsDropShadowEffect();
    shadowEffect_testBtn->setOffset(0,0);
    shadowEffect_testBtn->setColor(Qt::gray);
    shadowEffect_testBtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_WSABtn = new QGraphicsDropShadowEffect();
    shadowEffect_WSABtn->setOffset(0,0);
    shadowEffect_WSABtn->setColor(Qt::gray);
    shadowEffect_WSABtn->setBlurRadius(5);

    ui->refreshButton->setGraphicsEffect(shadowEffect_refreshButton);
    ui->adbKillerBtn->setGraphicsEffect(shadowEffect_killAdbBtn);
    ui->WIFIBtn->setGraphicsEffect(shadowEffect_testBtn);
    ui->WSABtn->setGraphicsEffect(shadowEffect_WSABtn);
}

/*
void MainWindow::hideCurrentPage()                  //方法：隐藏当前basePage
{
    currentPage->hide();
}*/

void MainWindow::initSonPage(int key)               //槽：生成子页面
{
    maker->createPageWithKey(key,currentPage,devList[current_device]);
}

void MainWindow::on_adbKillerBtn_clicked()          //槽：杀死ADB
{
    QMessageBox * msgBox = new QMessageBox;
    msgBox->setWindowIcon(QIcon(":/ico/image/ico/close-circle-line.svg"));
    msgBox->setStyleSheet("background-color:rgba(255,255,255,1);border:0px; border-radius:0px;");
    msgBox->setWindowTitle("杀死ADB");
    msgBox->setText("· 已尝试杀死ADB进程\n· 请勿连续执行！！！");
    msgBox->addButton(" ✓ ", QMessageBox::AcceptRole);
    msgBox->show();

    process->run("adb kill-server");
}

void MainWindow::playLoadingGif()                   //槽：播放加载动画
{
    qDebug() << "playLoadingGif";
    ui->loadingLabel->setMovie(movie);
    movie->start();
    ui->loadingLabel->show();
}

void MainWindow::stopLoadingGif()                   //槽：隐藏加载动画 + 设置currentpage参数，并发出完成basepage创建的信号
{
    ui->loadingLabel->setVisible(false);
}

void MainWindow::on_WIFIBtn_clicked()               //槽：获取无线调试参数
{
    getInfo = new QWidget();
    getInfo->setWindowTitle("无线调试");
    getInfo->setStyleSheet("background-color:rgba(255,255,255,1);");
    getInfo->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));
    getInfo->setWindowIconText("test");

    QLabel * title = new QLabel();
    title->setText("通过WI-FI连接设备");

    QWidget *outWgt = new QWidget();
    outWgt->setStyleSheet("border-radius: 4px;border:1px solid #BDBDBD;");
    QVBoxLayout * outLayout = new QVBoxLayout();
    QLabel * step1 = new QLabel();
    step1->setText("第一步：打开 [开发者选项 -> 无线调试]");
    step1->setStyleSheet("border-radius: 4px;border-bottom:1px solid #BDBDBD;");
    QLabel * lb_outIp = new QLabel();
    lb_outIp->setText("无线调试IP地址：");
    lb_outIp->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    QLabel * lb_outPort = new QLabel();
    lb_outPort->setText("无线调试端口：");
    lb_outPort->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");

    le_outIp = new QLineEdit();
    //le_outIp->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_outPort = new QLineEdit();
    //le_outPort->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");


    QWidget *inWgt = new QWidget();
    inWgt->setStyleSheet("border-radius: 4px;border:1px solid #BDBDBD;");
    QVBoxLayout * inLayout = new QVBoxLayout();
    QLabel * step2 = new QLabel();
    step2->setText("第二步：点击 [使用配对码配对设备]");
    step2->setStyleSheet("border-radius: 4px;border-bottom:1px solid #BDBDBD;");
    QLabel * lb_ipAddr = new QLabel();
    lb_ipAddr->setText("配对IP地址：");
    lb_ipAddr->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;border-bottom:2px");
    QLabel * lb_port = new QLabel();
    lb_port->setText("配对端口：");
    lb_port->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    QLabel * lb_code = new QLabel();
    lb_code->setText("配对码：");
    lb_code->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");

    le_ipAddr = new QLineEdit();
    //le_ipAddr->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_port = new QLineEdit();
    //le_port->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_code = new QLineEdit();
    //le_code->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");

    QHBoxLayout * lo_outIp = new QHBoxLayout();
    lo_outIp->addWidget(lb_outIp);
    lo_outIp->addWidget(le_outIp);
    QHBoxLayout * lo_outPort = new QHBoxLayout();
    lo_outPort->addWidget(lb_outPort);
    lo_outPort->addWidget(le_outPort);

    QHBoxLayout * lo_ipAddr = new QHBoxLayout();
    lo_ipAddr->addWidget(lb_ipAddr);
    lo_ipAddr->addWidget(le_ipAddr);
    QHBoxLayout * lo_port = new QHBoxLayout();
    lo_port->addWidget(lb_port);
    lo_port->addWidget(le_port);
    QHBoxLayout * lo_code = new QHBoxLayout();
    lo_code->addWidget(lb_code);
    lo_code->addWidget(le_code);

    QPushButton * getInfoBtn = new QPushButton(getInfo);
    getInfoBtn->setText("连接");
    getInfoBtn->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;}QPushButton:hover{background-color:rgba(255,255,255,0.7);}QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");
    QVBoxLayout * mainLayout = new QVBoxLayout();

    QGraphicsDropShadowEffect *shadowEffect_getInfoBtn = new QGraphicsDropShadowEffect();
    shadowEffect_getInfoBtn->setOffset(0,0);
    shadowEffect_getInfoBtn->setColor(Qt::gray);
    shadowEffect_getInfoBtn->setBlurRadius(5);

    getInfoBtn->setGraphicsEffect(shadowEffect_getInfoBtn);

    getInfo->setLayout(mainLayout);
    mainLayout->addWidget(title);

    mainLayout->addWidget(outWgt);

    outWgt->setLayout(outLayout);
    outLayout->addWidget(step1);
    outLayout->addLayout(lo_outIp);
    outLayout->addLayout(lo_outPort);

    mainLayout->addWidget(inWgt);

    inWgt->setLayout(inLayout);
    inLayout->addWidget(step2);
    inLayout->addLayout(lo_ipAddr);
    inLayout->addLayout(lo_port);
    inLayout->addLayout(lo_code);

    mainLayout->addWidget(getInfoBtn);

    connect(getInfoBtn,SIGNAL(clicked()),this,SLOT(connectWIFIDev()));
    getInfo->show();
}

void MainWindow::connectWIFIDev()                   //槽：连接无线调试设备
{
    QString ip = le_ipAddr->text().simplified();
    QString port = le_port->text().simplified();
    QString outIp = le_outIp->text().simplified();
    QString outPort = le_outPort->text().simplified();
    QString code = le_code->text().simplified();
    QString command_connect_to_WIFI_dev = "adb pair " + ip + ":" + port;

    process->run(command_connect_to_WIFI_dev, code + "\n");
    process->run("adb connect " + outIp + ":" + outPort);

    le_ipAddr->clear();
    le_port->clear();
    le_code->clear();
    le_outIp->clear();
    le_outPort->clear();
    getInfo->deleteLater();
}

void MainWindow::on_WSABtn_clicked()                //槽：连接WSA
{
    process->run("adb connect 127.0.0.1:58526");

    QMessageBox * msgBox = new QMessageBox;
    msgBox->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));
    msgBox->setStyleSheet("background-color:rgba(255,255,255,1);border:0px; border-radius:0px;");
    msgBox->setWindowTitle("无线调试");
    msgBox->setText("· 已尝试连接，请刷新设备列表并选择WSA");
    msgBox->addButton(" ✓ ", QMessageBox::AcceptRole);
    msgBox->show();
}

/*
void MainWindow::emit_signal_createBasePage(int key)
{
    emit createBasePage(key, ui->widget, devList[current_device], currentPage);
}
*/

void MainWindow::displayWelcomePage()
{
    if(WCMPage != NULL)         //销毁上一个basePage
    {
        //currentPage->setDisabled(true);
        //delete currentPage;
        WCMPage->~welcomePage();
        WCMPage = NULL;
    }

    WCMPage = new welcomePage();
    ui->verticalLayout_2->addWidget(WCMPage);
}
