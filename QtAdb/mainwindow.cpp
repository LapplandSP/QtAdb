#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initEnvironmentPATH();

    /*加载动画GIF*/
    //movie = new QMovie(":/gif/image/gif/final.gif");

    /*currentPage指针*/
    currentPage = NULL;
    //WCMPage = NULL;

    /*devList 中的当前设备索引*/
    current_device = 0;
    ui->dynamic_island->setText("请先选择设备");
    ui->dynamic_island->setStyleSheet("background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;");
    //ui->comboBox->setPlaceholderText("点击此处选择设备");

    /*连接信号与槽*/
    connect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //更改当前设备
    //connect(this->ui->indexList,SIGNAL(currentRowChanged(int)),this,SLOT(playLoadingGif()));      //播放加载动画
    connect(this->ui->indexList,SIGNAL(currentRowChanged(int)),this,SLOT(initBasePage(int)));       //创建并更改当前页面

    /*设置界面*/
    addIndexItems();    //设置左侧目录
    setStyles();        //设置样式
    view = new comboboxListWidget(ui->comboBox);
    ui->comboBox->setModel(view->model());
    ui->comboBox->setView(view);
    //ui->pluginBtn->hide();

    /*初始化对象*/
    process = new adbProcess();
    explainer = new textExplainer();
    maker = new pageMaker();
    listener = new usb_listener();

    connect(listener, SIGNAL(DeviceChanged()),this,SLOT(refreshDevListLater()));
    connect(this, SIGNAL(adbDeviceChanged()),this,SLOT(DeviceChanged()));

    qApp->installNativeEventFilter(listener);

    //listener->EmitMySignal();
    this->setAttribute(Qt::WA_NativeWindow);

    /*启动监听*/

    /*启动ADB，将延长页面创建时间，在此期间显示启动界面，显示了个勾八*/
    process->run("adb server");
    refreshDevList();

    /*用户未选择设备前，锁定界面*/
    this->update();

    initBasePage(6);
    currentPage->playLoadAnimation(427);
    lock();

    reset_monitorBars();
}

MainWindow::~MainWindow()
{
    ui->indexList->clear();
    delete process;
    delete explainer;
    delete maker;
    delete ui;
}

void MainWindow::initEnvironmentPATH()              //方法：设置环境变量
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF_8"));

    /*
    QString envPath = qgetenv("PATH");      //获取当前环境变量
    QString appDirPath = QApplication::applicationDirPath();    //获取程序所在位置
    QString userPath = appDirPath + "\\platform-tools";     //向字符串中添加ADB环境
    envPath += QDir::toNativeSeparators(userPath).prepend(';');
    qputenv("PATH",envPath.toStdString().c_str());*/          //更改环境变量
    //qDebug() << envPath.toStdString().c_str();

    //QTextCodec *code = QTextCodec::codecForName("UTF_8");

    QString envPath = qgetenv("PATH");      //获取当前环境变量
    //qDebug() << "envpath" << envPath;

    //QMessageBox::warning(NULL, "nvpath",envPath);

    QString appDirPath = QApplication::applicationDirPath();    //获取程序所在位置
    //qDebug() << "appDirPath" << appDirPath;
    if(appDirPath.contains(QRegularExpression("[\u4e00-\u9fa5]")))
    {
        //qDebug() << "-------------------" << appDirPath.contains(QRegularExpression("[\\x4e00-\\x9fa5]+"));
        //qDebug() << "\\x4e00" ;
        //qDebug() << "\\x9fa5" ;
        QMessageBox::warning(NULL, "路径问题","请将程序置于纯英文路径下，否则将无法正确设置ADB环境\n"
                                             "您当前的路径为：\n"
                                             + appDirPath);
    }

#ifdef Q_OS_WIN32
    QString userPath = appDirPath + "\\Resources\\platform-tools";     //向字符串中添加ADB环境
#endif

#ifdef Q_OS_OSX
    QString userPath = appDirPath + "\\platform-tools-OSX";     //向字符串中添加ADB环境
#endif

#ifdef Q_OS_LINUX
    QString userPath = appDirPath + "\\platform-tools-linux";     //向字符串中添加ADB环境
#endif
    //QString userPath = appDirPath + "\\platform-tools";     //向字符串中添加ADB环境
    //qDebug() << "userPath" << userPath;
    //QMessageBox::warning(NULL, "userPath",userPath);

    envPath += QDir::toNativeSeparators(userPath).prepend(';');
    //qDebug() << "envPath" << envPath;
    //QMessageBox::warning(NULL, "envPath",envPath);

    qputenv("PATH",envPath.toStdString().c_str());         //更改环境变量
}

void MainWindow::refreshDevList()                   //方法：刷新设备列表
{

    //ui->comboBox->clear();
    /*DEBUG*/
    bool changed = false;       //这个是判断列表有没有变化用的
    //qDebug() << "******************一次调用*********************";
    //qDebug() << "refreshDevList devList is empty? " << devList.isEmpty() << QTime::currentTime();
    //qDebug() << "devList.size()" << devList.size();
/*
    for(int i = 0; i < devList.size();i++)
    {
        //qDebug() << "devList[" << i << "] is :" << devList[i].addr;
    }
*/
    /*DEBUG_END*/
    //qDebug() << "shit 0";
    bool devList_is_empty = devList.isEmpty();

    QList<device> tmpList;  //暂时的list，存储刷新前的devlist，用来与之后的devlist对比以确认设备是否有改变

    /*给tmpList赋值*/
    if(!devList_is_empty)
    {
        for(int i = 0; i < devList.size();i++)
        {
            //Debug() << "shit 3.1";
            device dev;
            dev.device_debug = devList[i].device_debug;
            dev.device_product = devList[i].device_product;
            dev.addr = devList[i].addr;
            dev.model = devList[i].model;
            dev.state = devList[i].state;
            dev.transport_id = devList[i].transport_id;
            tmpList.append(dev);
        }
    }
    //qDebug() << "tmpList.size()" << tmpList.size();

    //ui->comboBox->clear();
    devList.clear();            //清空设备列表
    qDebug() << "Bug#01 finding!";
    devList.append(explainer->getDevList_windows(process->run("adb devices -l")));    //重新赋值
    //devList = explainer->getDevList_windows(process->run("adb devices -l"));    //重新赋值
    qDebug() << "Bug#01 found!";
    //qDebug() << "devList after explain:" << devList.isEmpty();

    /*
    qDebug() << "shit 1";
    for(int i = 0; i < tmpList.size();i++)
    {
        qDebug() << "shit 2";
        qDebug() << "tmpList[" << i << "] is :" << devList[i].addr;
    }
    for(int i = 0; i < devList.size();i++)
    {
        qDebug() << "shit 3";
        qDebug() << "devList new[" << i << "] is :" << devList[i].addr;
    }
    qDebug() << "shit finish";*/


    /*判断列表内容是否变化，若变化则发送 adbDeviceChanged 信号*/
    if(!devList_is_empty)
    {
        if(devList.size() == tmpList.size())
        {
            for(int i = 0; i < devList.size() && i < tmpList.size() ; i++)
            {
                if(devList[i].addr != tmpList[i].addr)
                {
                    emit adbDeviceChanged();
                    changed = true;
                    break;
                }
            }
        }
        else
        {
            emit adbDeviceChanged();
            changed = true;
        }
    }
    else if(!devList.isEmpty() && tmpList.isEmpty())
    {
        emit adbDeviceChanged();
        changed = true;
    }
    else if(devList.isEmpty() && !tmpList.isEmpty())
    {
        emit adbDeviceChanged();
        changed = true;
    }
    else
    {
        //qDebug() << "else:" << devList.isEmpty() << tmpList.isEmpty() << devList_is_empty;
    }

    QList<int> off;    //未响应设备索引

    /*将设备信息传入 List l ，并将l的值显示在combobox中*/
    QStringList l;
    l.clear();

    /*一条一条添加*/
    for (int i = 0 ; i < devList.size() ; i++ )
    {
        /*原来的*/
        QString devItem = devList[i].state + " " + explainer->get_words_after(devList[i].model, ":") + " " + devList[i].addr;
        l.append(devItem);
        //qDebug() << "l[" << i << "] = " << l[i];
        if(devList[i].state == "[未响应]")
        {
            off.append(i);
            /*
            QVariant v(0);
            ui->comboBox->setItemData(i, v, Qt::UserRole - 1);
            */
        }
        /*原来的END*/

        /*新的*/

        if(changed)     //changed为true则设备列表有所变化，此时才更新
        {
            //qDebug() <<"changed so clear";

            disconnect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //取消连接
            ui->comboBox->clear();
            view->setUpList(devList, off);
            qDebug() << "1";
            connect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //重新连接
        }

        /*新的END*/
    }

    /*出意外弄回来
    if(changed)     //changed为true则设备列表有所变化，此时才更新
    {
        //qDebug() <<"changed so clear";
        ui->comboBox->clear();
        ui->comboBox->addItems(l);
    }*/

    if(!liangYi)    //
    {
        disconnect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //取消连接
        ui->comboBox->clear();
        view->setUpList(devList, off);
        connect(this->ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentDevice(int)));  //重新连接
    }

    liangYi = false;

    /*将离线设备设为不可选*/
    for(int i = 0; i < off.count();i++)
    {
        QVariant v(0);
        ui->comboBox->setItemData(off[i], v, Qt::UserRole - 1);
    }

    /*若没有设备，重置*/
    if(devList.isEmpty())
    {
        current_device = -1;         //重设当前设备
        ui->dynamic_island->setText("请先选择设备");
        ui->dynamic_island->setStyleSheet("background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;");
    }
    else
    {
        current_device = 0;
        ui->dynamic_island->setText(devList[current_device].addr);
        qDebug()<<"devList[current_device].state="<<devList[current_device].state;
        if(devList[current_device].state=="[未授权]")
        {
            ui->dynamic_island->setStyleSheet("background-color:rgba(237,90,101,1);border-radius:4px;border:0px;");
            //this->update();
            //rgba(237,90,101,0.6)
        }
        else
        {
            ui->dynamic_island->setStyleSheet("background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;");
        }
    }

    liangYi = false;        //重置两仪

    //qDebug() << "******************一次调用结束*********************";
}

void MainWindow::on_refreshButton_clicked()         //槽：按下刷新按钮
{
    if(thread_mon != NULL)
    {
        //siXiangTimer->stop();
        siXiangTimer->deleteLater();
        siXiangTimer = NULL;
        //qDebug() <<"thread_mon != NULL";
        //qDebug() <<"disconnect";
        thread_mon->disconnect();
        //qDebug() <<"exit()";
        thread_mon->quit();
        //qDebug() <<"deleteLater()";
        //thread_mon->deleteLater();
    }

    refreshDevList();

    lock();
    /*
    if(currentPage != NULL)
    {
        currentPage->~basePage();
        currentPage = NULL;
    }*/

    initBasePage(6);
    reset_monitorBars();

    resetMonitorThread(ui->comboBox->currentIndex());
}

void MainWindow::resetMonitorThread(int index)
{
    if(thread_mon != NULL && siXiangTimer != NULL)
    {
        //qDebug() <<"stop";
        //siXiangTimer->stop();
        //qDebug() <<"delete";
        siXiangTimer->deleteLater();
        //qDebug() <<"=NULL";
        siXiangTimer = NULL;
        //qDebug() <<"thread_mon != NULL";
        //qDebug() <<"disconnect";
        thread_mon->disconnect();
        //qDebug() <<"exit()";
        thread_mon->quit();
        //qDebug() <<"deleteLater()";
        thread_mon->deleteLater();
    }

    //ui->widget_height->layout()->addWidget(ui->comboBox.it)


    if(index >= 0)
    {
        //qDebug() <<"NEW";
        siXiangTimer = new QTimer();
        thread_mon = new thread_monitor(devList[current_device]);
        //qDebug() <<"devList[current_device]:" << "current_device=" << current_device << "dev:" << devList[current_device].addr;
        //qDebug() <<"CONNECT";
        connect(siXiangTimer,SIGNAL(timeout()),thread_mon,SLOT(getInfo()));
        connect(thread_mon,SIGNAL(signal_monitor(float,float)),this,SLOT(slot_update_monitor(float,float)));
        //qDebug() <<"START";
        thread_mon->start();
        siXiangTimer->start(2000);
        ui->progressBar_CPU->setRange(0,100);
        ui->progressBar_RAM->setRange(0,100);
    }
}

void MainWindow::setCurrentDevice(int index)        //槽：改变所选设备
{
    //qDebug() <<"MainWindow:if" << "index = " << index;

    if(thread_mon != NULL && siXiangTimer != NULL)
    {
        //qDebug() <<"stop";
        //siXiangTimer->stop();
        //qDebug() <<"delete";
        siXiangTimer->deleteLater();
        //qDebug() <<"=NULL";
        siXiangTimer = NULL;
        //qDebug() <<"thread_mon != NULL";
        //qDebug() <<"disconnect";
        thread_mon->disconnect();
        //qDebug() <<"exit()";
        thread_mon->quit();
        //qDebug() <<"deleteLater()";
        thread_mon->deleteLater();
    }

    //ui->widget_height->layout()->addWidget(ui->comboBox.it)


    if(index >= 0)
    {
        //qDebug() <<"NEW";
        siXiangTimer = new QTimer();
        thread_mon = new thread_monitor(devList[current_device]);
        //qDebug() <<"devList[current_device]:" << "current_device=" << current_device << "dev:" << devList[current_device].addr;
        //qDebug() <<"CONNECT";
        connect(siXiangTimer,SIGNAL(timeout()),thread_mon,SLOT(getInfo()));
        connect(thread_mon,SIGNAL(signal_monitor(float,float)),this,SLOT(slot_update_monitor(float,float)));
        //qDebug() <<"START";
        thread_mon->start();
        siXiangTimer->start(2000);
        ui->progressBar_CPU->setRange(0,100);
        ui->progressBar_RAM->setRange(0,100);

        if(currentPage != NULL)
        {
            delete currentPage;
            //currentPage->~basePage();
            currentPage = NULL;
        }
        //initBasePage(6);
        //ui->indexList->setCurrentRow(6);

        current_device = index;
        //initBasePage(0);
        /*
        if(devList[current_device].state == "[侧载]")
        {
            initBasePage(5);
        }*/

        if(ui->indexList->currentRow() == 0)
        {
            //qDebug() << "initBasePage";
            initBasePage(0);
        }
        else
        {
            //qDebug() << "setCurrentRow";
            ui->indexList->setCurrentRow(0);
        }

        ui->dynamic_island->setText(explainer->get_words_after(devList[current_device].model,":"));
    }
    unlock();
}

void MainWindow::initBasePage(int key)              //槽：生成basePages
{
    while(key != -1)
    {
        //this->setEnabled(false);
        this->lock();

        if(currentPage != NULL)         //销毁上一个basePage
        {
            //currentPage->playExitAnimation();

            //qDebug() << "deleting currentPage";
            delete currentPage;
            //currentPage->~basePage();

            //qDebug() << "delete currentPage";
            //currentPage->~basePage();
            currentPage = NULL;
        }

        /*动画*/
        //ui->indexList[key]

        /**/

        currentPage = new basePage(this);

        //qDebug() << "height in initBasePage()" << ui->widget_height->height();
        currentPage->wgtHeight = ui->widget_height->height();
        //qDebug() << "height2 in initBasePage()" << currentPage->wgtHeight;
        connect(currentPage,SIGNAL(animationEnd()),this,SLOT(slot_taiChi()));

        if(devList.isEmpty())
        {
            device * noDevice = new device;
            noDevice->addr = "#EMPTY#";
            currentPage = maker->createPageWithKey(6,ui->page,*noDevice);
        }
        else
        {
            currentPage = maker->createPageWithKey(key,ui->page,devList[current_device]);
        }

        ui->verticalLayout_2->addWidget(currentPage);

        currentPage->playLoadAnimation(ui->widget_height->height());
        //currentPage->playExitAnimation();
        //currentPage->setVisible(true);
        taiChiTimer = new QTimer(this);
        connect(taiChiTimer, SIGNAL(timeout()), this, SLOT(slot_taiChi()));
        taiChiTimer->setSingleShot(true);
        taiChiTimer->start(700);

        break;
    }
}

void MainWindow::addItemToIndex(indexListItem *itemWidget)  //方法：向indexist中添加单个item
{
    QListWidgetItem * tmpItem = new QListWidgetItem();
    ui->indexList->addItem(tmpItem);
    ui->indexList->setItemWidget(tmpItem, itemWidget);
}

void MainWindow::addIndexItems()                    //方法：初始化向indexList中添加的item，完成indexList创建。
{
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
    apps->setText("软件包管理器");
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

    //:/ico/image/ico/code-s-slash-line.svg //05
    indexListItem *advanced = new indexListItem(this->ui->indexList);
    advanced->setText("其它");
    advanced->setPic("image:url(:/ico/image/ico/code-s-slash-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(advanced);

    indexListItem *about = new indexListItem(this->ui->indexList);
    about->setText("关于");
    about->setPic("image:url(:/ico/image/ico/about/information-line.svg);background-color:rgba(255,255,255,0);");
    addItemToIndex(about);

    ui->indexList->setResizeMode(QListView::Adjust);
}

void MainWindow::lock()                             //方法：锁定mainwindow中控件
{
    //this->setEnabled(false);
    ui->indexList->setEnabled(false);
    //currentPage->setEnabled(false);
    ui->page->setEnabled(false);
}

void MainWindow::unlock()                           //方法：解锁mainwindow中的控件
{
    //this->setEnabled(false);
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

    ui->comboBox->setStyleSheet("QComboBox{color:black; border:0px solid #BDBDBD; border-radius:4px; background-color:rgba(255,255,255,0.9);image:url(:/ico/image/ico/devices.svg);background-color:rgba(255,255,255,0.9);}"
                                "QComboBox::drop-down{border: 0px solid rgba(255,255,255,0);background-color:rgba(255,255,255,0);border-radius: 8px;}"
                                "QComboBox QAbstractItemView{border:1px solid #BDBDBD;border-radius:0px 0px 0px 0px;outline: 0px;background-color:rgba(255,255,255,0);}"
                                "QComboBox QAbstractItemView::item{height:300px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;background-color:rgba(255,255,255,255);}"//height:30px;
                                "QComboBox QAbstractItemView::item:hover{height:300px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black;background-color:rgba(255,255,255,255);}"
                                "QComboBox QAbstractItemView::item:selected{height:300px;border:0px solid #BDBDBD;border-radius:0px 0px 0px 0px;color:black;background-color:rgba(255,255,255,255);}"
                                );

    /*
    ui->refreshButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;}"
                                     "QPushButton:hover{background-color:rgba(255,255,255,0.7);}"
                                     "QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");*/
    //ui->iconLabel->setStyleSheet("background-color:transparent;");
    ui->fakeSpacer->setStyleSheet("background-color:transparent;");

    QGraphicsDropShadowEffect *shadowEffect_refreshButton = new QGraphicsDropShadowEffect(this);
    shadowEffect_refreshButton->setOffset(0,0);
    shadowEffect_refreshButton->setColor(Qt::gray);
    shadowEffect_refreshButton->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_killAdbBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_killAdbBtn->setOffset(0,0);
    shadowEffect_killAdbBtn->setColor(Qt::gray);
    shadowEffect_killAdbBtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_testBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_testBtn->setOffset(0,0);
    shadowEffect_testBtn->setColor(Qt::gray);
    shadowEffect_testBtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_WSABtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_WSABtn->setOffset(0,0);
    shadowEffect_WSABtn->setColor(Qt::gray);
    shadowEffect_WSABtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_cmdBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_cmdBtn->setOffset(0,0);
    shadowEffect_cmdBtn->setColor(Qt::gray);
    shadowEffect_cmdBtn->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_island = new QGraphicsDropShadowEffect(this);
    shadowEffect_island->setOffset(0,0);
    shadowEffect_island->setColor(Qt::gray);
    shadowEffect_island->setBlurRadius(5);

    QGraphicsDropShadowEffect *shadowEffect_pluginBtn = new QGraphicsDropShadowEffect(this);
    shadowEffect_pluginBtn->setOffset(0,0);
    shadowEffect_pluginBtn->setColor(Qt::gray);
    shadowEffect_pluginBtn->setBlurRadius(5);


    QGraphicsDropShadowEffect *shadowEffect_combo = new QGraphicsDropShadowEffect(this);
    shadowEffect_combo->setOffset(0,0);
    shadowEffect_combo->setColor(Qt::gray);
    shadowEffect_combo->setBlurRadius(5);
    QGraphicsDropShadowEffect *shadowEffect_CPU = new QGraphicsDropShadowEffect(this);
    shadowEffect_CPU->setOffset(0,0);
    shadowEffect_CPU->setColor(Qt::gray);
    shadowEffect_CPU->setBlurRadius(5);
    QGraphicsDropShadowEffect *shadowEffect_RAM = new QGraphicsDropShadowEffect(this);
    shadowEffect_RAM->setOffset(0,0);
    shadowEffect_RAM->setColor(Qt::gray);
    shadowEffect_RAM->setBlurRadius(5);

    ui->refreshButton->setGraphicsEffect(shadowEffect_refreshButton);
    ui->adbKillerBtn->setGraphicsEffect(shadowEffect_killAdbBtn);
    ui->WIFIBtn->setGraphicsEffect(shadowEffect_testBtn);
    ui->WSABtn->setGraphicsEffect(shadowEffect_WSABtn);
    ui->cmdBtn->setGraphicsEffect(shadowEffect_cmdBtn);
    ui->dynamic_island->setGraphicsEffect(shadowEffect_island);
    ui->comboBox->setGraphicsEffect(shadowEffect_combo);
    ui->widget_mon_CPU->setGraphicsEffect(shadowEffect_CPU);
    ui->widget_mon_RAM->setGraphicsEffect(shadowEffect_RAM);
    ui->pluginBtn->setGraphicsEffect(shadowEffect_pluginBtn);

    ui->comboBox->setMaxVisibleItems(1);
    ui->comboBox->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->comboBox->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false);

}

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

void MainWindow::on_WIFIBtn_clicked()               //槽：弹出无线调试连接窗口，获取无线调试参数
{
    getInfo = new QWidget();
    getInfo->setMaximumSize(500,300);
    getInfo->setWindowTitle("无线调试");
    getInfo->setStyleSheet("background-color:rgba(255,255,255,1);");
    getInfo->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));
    getInfo->setWindowIconText("test");

    QLabel * title = new QLabel(getInfo);
    title->setText("通过WI-FI连接设备");

    QWidget *outWgt = new QWidget(getInfo);
    outWgt->setStyleSheet("border-radius: 4px;border:1px solid #BDBDBD;");
    QVBoxLayout * outLayout = new QVBoxLayout();
    QLabel * step1 = new QLabel(getInfo);
    step1->setText("第一步：打开 [开发者选项 -> 无线调试]");
    step1->setStyleSheet("border-radius: 4px;border-bottom:1px solid #BDBDBD;");
    QLabel * lb_outIp = new QLabel(getInfo);
    lb_outIp->setText("无线调试IP地址：");
    lb_outIp->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    QLabel * lb_outPort = new QLabel(getInfo);
    lb_outPort->setText("无线调试端口：");
    lb_outPort->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");

    le_outIp = new QLineEdit(getInfo);
    //le_outIp->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_outPort = new QLineEdit(getInfo);
    //le_outPort->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");


    QWidget *inWgt = new QWidget(getInfo);
    inWgt->setStyleSheet("border-radius: 4px;border:1px solid #BDBDBD;");
    QVBoxLayout * inLayout = new QVBoxLayout();
    QLabel * step2 = new QLabel(getInfo);
    step2->setText("第二步：点击 [使用配对码配对设备]");
    step2->setStyleSheet("border-radius: 4px;border-bottom:1px solid #BDBDBD;");
    QLabel * lb_ipAddr = new QLabel(getInfo);
    lb_ipAddr->setText("配对IP地址：");
    lb_ipAddr->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;border-bottom:2px");
    QLabel * lb_port = new QLabel(getInfo);
    lb_port->setText("配对端口：");
    lb_port->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    QLabel * lb_code = new QLabel(getInfo);
    lb_code->setText("配对码：");
    lb_code->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");

    le_ipAddr = new QLineEdit(getInfo);
    //le_ipAddr->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_port = new QLineEdit(getInfo);
    //le_port->setStyleSheet("border-radius: 4px;border-bottom:2px solid #146AFF;");
    le_code = new QLineEdit(getInfo);
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
    QVBoxLayout * mainLayout = new QVBoxLayout(getInfo);

    QGraphicsDropShadowEffect *shadowEffect_getInfoBtn = new QGraphicsDropShadowEffect(getInfo);
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
    //qDebug() << "size is " << getInfo->geometry();
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
    msgBox->setWindowTitle("WSA");
    msgBox->setText("· 已尝试连接，请刷新设备列表并选择WSA\n· 请谨慎对WSA使用某些功能");
    msgBox->addButton(" ✓ ", QMessageBox::AcceptRole);
    msgBox->show();
}

void MainWindow::slot_taiChi()
{
    //qDebug() <<"taiChi -" << taiChi;
    /*
    if(taiChi)
    {
        this->resize(this->geometry().width() + 5,this->geometry().height());
    }
    else
    {
        this->resize(this->geometry().width() - 5,this->geometry().height());
    }*/
    taiChi = !taiChi;
    //currentPage->resize(1,1);
    delete taiChiTimer;
    taiChiTimer = NULL;

    if(ui->comboBox->currentIndex() != -1)
    {
        this->unlock();
        //currentPage->setDisabled(false);
    }
    //this->setEnabled(true);
}

void MainWindow::on_cmdBtn_clicked()
{
    QString appDirPath = QApplication::applicationDirPath();
    QString batPath = appDirPath + "/Resources/platform-tools/open-cmd-here.bat";
    //qDebug()<<"batPath = " << batPath;
    QProcess batProcess;
    batProcess.start(batPath);
    batProcess.waitForFinished();
}

void MainWindow::DevicePlugIn()
{
    qDebug() << "DevicePlugIn";
}

void MainWindow::DevicePlugOut()
{
    qDebug() << "DevicePlugout";
}

void MainWindow::DeviceChanged()
{
    if(firstBoot == true)
    {
        firstBoot = false;
    }
    else
    {
        QMessageBox::StandardButton result=QMessageBox::warning(NULL, "检测到USB热插拔","您可能插入或拔出了一台ADB设备\n"
                                                                                   "将对设备列表进行刷新\n"
                                                                                   "（⚠️这会中断当前正在执行的任务）");

        //msgBox->setStyleSheet("background-color:rgba(255,255,255,1);border:0px; border-radius:0px;");
        //QMessageBox::StandardButton result=QMessageBox::warning(this, "Title","text");
        //qDebug() << "result =" << result;
        if(result)
        {
            //这里要delete adbprocess
            on_refreshButton_clicked();
        }
        else
        {

        }
        //qDebug() << "DeviceChanged";
    }
}

void MainWindow::slot_refreshDevList()
{
    //qDebug() << "slot_refreshDevList";
    liangYi = true;
    refreshDevList();
}


void MainWindow::refreshDevListLater()
{

    qDebug() << ">>>>>>>>>>>>>>>>>>>>>>refreshDevListLater";
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_refreshDevList()));
    timer->setSingleShot(true);
    timer->start(1000);
    //timer->deleteLater();
}

void MainWindow::slot_update_monitor(float cpu_useage, float mem_useage)
{
    //qDebug() << "cpu_useage is " <<cpu_useage ;
    //qDebug() << "mem_useage" << mem_useage;

    int cpu_credit = (int)(cpu_useage*100);
    //qDebug() << "cpu_credit" << cpu_credit;
    ui->progressBar_CPU->setValue(cpu_credit);

    int mem_credit = (int)(mem_useage*100);
    //qDebug() << "mem_credit" << mem_credit;
    ui->progressBar_RAM->setValue(mem_credit);
}

void MainWindow::reset_monitorBars()
{
    //qDebug() << "reset";
    ui->progressBar_CPU->setValue(0);
    ui->progressBar_RAM->setValue(0);
}

void MainWindow::on_pluginBtn_clicked()
{
    magiskSaver = new QWidget();
    magiskSaver->setMaximumSize(500,300);
    magiskSaver->setWindowTitle("Magisk救砖");
    magiskSaver->setStyleSheet("background-color:rgba(255,255,255,1);");
    magiskSaver->setWindowIcon(QIcon(":/ico/image/ico/magisk.png"));
    //magiskSaver->setWindowIconText("test");

    QLabel * title = new QLabel(magiskSaver);
    title->setText("在开机前禁用所有 Magisk 模块");

    QWidget *saveWgt = new QWidget(magiskSaver);
    saveWgt->setStyleSheet("border-radius: 4px;border:1px solid #BDBDBD;");
    QVBoxLayout * saveLayout = new QVBoxLayout();
    QLabel * profile = new QLabel(magiskSaver);
    profile->setText("请按照以下步骤操作");
    profile->setStyleSheet("border-radius: 4px;border-bottom:1px solid #BDBDBD;");
    QLabel * step1 = new QLabel(magiskSaver);
    step1->setText("1. 断开所有设备的连接，将不断重启的手机关机，或等待它的下一次重启。");
    step1->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    step1->setWordWrap(true);
    QLabel * step2 = new QLabel(magiskSaver);
    step2->setText("2. 点按救砖按钮。（接下来您无需再对电脑进行操作）");
    step2->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    step2->setWordWrap(true);
    QLabel * step3 = new QLabel(magiskSaver);
    step3->setText("3. 将手机开机，尽量在开机进入第一屏时连接数据线。");
    step3->setStyleSheet("border-radius: 4px;border:0px solid #BDBDBD;");
    step3->setWordWrap(true);


    QPushButton * saveBtn = new QPushButton(magiskSaver);
    saveBtn->setText("");
    saveBtn->setCheckable(false);
    saveBtn->setIcon(QIcon(":/ico/image/ico/play-line.svg"));
    saveBtn->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;}QPushButton:hover{background-color:rgba(255,255,255,0.7);}QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");
    QVBoxLayout * mainLayout = new QVBoxLayout(magiskSaver);

    QGraphicsDropShadowEffect *shadowEffect_getInfoBtn = new QGraphicsDropShadowEffect(magiskSaver);
    shadowEffect_getInfoBtn->setOffset(0,0);
    shadowEffect_getInfoBtn->setColor(Qt::gray);
    shadowEffect_getInfoBtn->setBlurRadius(5);

    saveBtn->setGraphicsEffect(shadowEffect_getInfoBtn);

    magiskSaver->setLayout(mainLayout);
    mainLayout->addWidget(title);

    mainLayout->addWidget(saveWgt);

    saveWgt->setLayout(saveLayout);
    saveLayout->addWidget(profile);
    saveLayout->addWidget(step1);
    saveLayout->addWidget(step2);
    saveLayout->addWidget(step3);
    mainLayout->addWidget(saveBtn);

    connect(saveBtn,SIGNAL(clicked()),this,SLOT(slot_save_magisk()));
    magiskSaver->show();
}

void MainWindow::slot_save_magisk()
{
    qDebug() << "magisk救砖输出" << process->run("adb wait-for-device shell magisk --remove-modules");
}
