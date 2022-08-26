#include "pagemaker.h"

pageMaker::pageMaker()
{
    process = new adbProcess();
    explainer = new textExplainer();
}

pageMaker::~pageMaker()
{
    //delete process;
    //delete explainer;
}

basePage* pageMaker::createPageWithKey(int key, QWidget *parent, device dev)
{
    //qDebug() << "key in createPageWithKey() is " << key ;
    int k = key;
    if(dev.addr.toInt() == -1)
    {
        k = 6;
    }

    /*
    if(dev.state == "[未响应]" || dev.state == "[REC]" || dev.state == "[侧载]" || dev.state == "[未知]")
    {

    }
    */

    switch(k)
    {
    case 0:
        if(dev.state == "[开机]")
        {
            return createPage_devInfo(parent , dev);
            //break;
        }
        else if(dev.state == "[REC]")
        {
            return createPage_devInfo_rec(parent, dev);
            //break;
        }
        else
        {
            return createPage_disabled(parent);
            //break;
        }
        break;

    case 1:
        if(dev.state == "[未响应]" || dev.state == "[REC]" || dev.state == "[侧载]" || dev.state == "[未知]")
        {
            return createPage_disabled(parent);
        }
        else
        {
            return createPage_acvitator(parent, dev);
        }
        break;

    case 2:
        if(dev.state == "[未响应]" || dev.state == "[REC]" || dev.state == "[侧载]" || dev.state == "[未知]")
        {
            return createPage_disabled(parent);
        }
        else
        {
            return createPage_apps(parent, dev);
        }
        break;

    case 3:
        return createPage_devControl(parent, dev);
        break;
    case 4:
        return createPage_recovery(parent, dev);
        break;
    case 5:
        if(dev.state == "[未响应]" || dev.state == "[REC]" || dev.state == "[侧载]" || dev.state == "[未知]")
        {
            return createPage_disabled(parent);
        }
        else
        {
            return createPage_advanced(parent,dev);
        }
        break;

    case 6:
        return createPage_about(parent);
        break;
    }
    return NULL;
}

basePage* pageMaker::createPage_devInfo(QWidget *parent, device dev)
{
    /*
    CItemWidget* pItemWidget = new CItemWidget(this)；
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(350, 40));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, pItemWidget);*/

    basePage *devInfo = new basePage(parent);
    devInfo->isBasePage = true;
    devInfo->whoYouAre("devInfo");
    int val[20] = {2,3};
    //qDebug() << "!!!!!!!!!!!!!!!!!!!" << *val;
    devInfo->setEnableValue(val);
    devInfo->setDev(dev);
    /***********************************/

    pageListItemStruct *productModel = initStruct(devInfo);
    productModel->item->setText_title("设备型号 | DeviceModel");
    productModel->item->setPic(":/ico/image/ico/profile-line.svg");
    productModel->thread->initThread("adb shell getprop ro.product.model", dev);
    QEventLoop::connect(productModel->thread,SIGNAL(signal_output(QString)),productModel->item,SLOT(slot_setText_profile(QString)));
    //QEventLoop::connect(devInfo,SIGNAL(animationEnd()),productModel->item,SLOT(slot_setStyles()));
    productModel->thread->start();
    devInfo->addItemsToList(productModel->item);
    //qDebug() << "item is in thread" << productModel->item->thread();

    pageListItemStruct *screen_resolution = initStruct(devInfo);
    screen_resolution->item->setText_title("屏幕分辨率");
    screen_resolution->item->setPic(":/ico/image/ico/fullscreen-line.svg");
    screen_resolution->thread->initThread("adb shell wm size", dev, ": ");
    QEventLoop::connect(screen_resolution->thread,SIGNAL(signal_output(QString)),screen_resolution->item,SLOT(slot_setText_profile(QString)));
    screen_resolution->thread->start();
    screen_resolution->item->setSelectable();
    devInfo->addItemsToList(screen_resolution->item);

    //adb shell wm density
    pageListItemStruct *dpi = initStruct(devInfo);
    dpi->item->setText_title("屏幕密度 | DPI");
    dpi->item->setPic(":/ico/image/ico/grid-line.svg");
    dpi->thread->initThread("adb shell wm density", dev);
    QEventLoop::connect(dpi->thread,SIGNAL(signal_output(QString)),dpi->item,SLOT(slot_setText_profile(QString)));
    dpi->thread->start();
    dpi->item->setSelectable();
    devInfo->addItemsToList(dpi->item);

    //adb shell settings get secure android_id
    pageListItemStruct *android_id = initStruct(devInfo);
    android_id->item->setText_title("Android Id");
    android_id->item->setPic(":/ico/image/ico/barcode-line.svg");
    android_id->thread->initThread("adb shell settings get secure android_id", dev);
    QEventLoop::connect(android_id->thread,SIGNAL(signal_output(QString)),android_id->item,SLOT(slot_setText_profile(QString)));
    android_id->thread->start();
    devInfo->addItemsToList(android_id->item);

    //adb shell getprop ro.build.version.release
    pageListItemStruct *android_version = initStruct(devInfo);
    android_version->item->setText_title("安卓版本");
    android_version->item->setPic(":/ico/image/ico/android-line.svg");
    android_version->thread->initThread("adb shell getprop ro.build.version.release", dev);
    QEventLoop::connect(android_version->thread,SIGNAL(signal_output(QString)),android_version->item,SLOT(slot_setText_profile(QString)));
    android_version->thread->start();
    devInfo->addItemsToList(android_version->item);

    pageListItemStruct *cpu = initStruct(devInfo);
    cpu->item->setText_title("处理器 | CPU");
    cpu->item->setPic(":/ico/image/ico/cpu-line.svg");
    cpu->thread->initThread("adb shell cat /proc/cpuinfo", dev, "#CPU#");
    QEventLoop::connect(cpu->thread,SIGNAL(signal_output(QString)),cpu->item,SLOT(slot_setText_profile(QString)));
    cpu->thread->start();
    devInfo->addItemsToList(cpu->item);

    /**************别删**********************/
    /*
    pageListItem *productModel = new pageListItem(devInfo);
    //qDebug() << "dev of pageMaker" << dev.addr;
    productModel->setText("设备型号 | DeviceModel",process->run("adb shell getprop ro.product.model", dev).simplified());
    productModel->setPic(":/ico/image/ico/profile-line.svg");
    devInfo->addItemsToList(productModel);


    pageListItem *screen_resolution = new pageListItem(devInfo);
    screen_resolution->setText("屏幕分辨率",explainer->get_words_after(process->run("adb shell wm size", dev), ": "));
    screen_resolution->setPic(":/ico/image/ico/fullscreen-line.svg");
    devInfo->addItemsToList(screen_resolution);

    //adb shell wm density  *****************
    pageListItem *dpi = new pageListItem(devInfo);
    dpi->setText("屏幕密度 | DPI",process->run("adb shell wm density", dev).replace("Physical density", "默认").replace("Override density","当前").simplified());
    dpi->setPic(":/ico/image/ico/grid-line.svg");
    dpi->setSelectable();
    devInfo->addItemsToList(dpi);

    //adb shell settings get secure android_id
    pageListItem *android_id = new pageListItem(devInfo);
    android_id->setText("Android Id",process->run("adb shell settings get secure android_id", dev).simplified());
    android_id->setPic(":/ico/image/ico/barcode-line.svg");
    devInfo->addItemsToList(android_id);

    //adb shell getprop ro.build.version.release
    pageListItem *android_version = new pageListItem(devInfo);
    android_version->setText("安卓版本",process->run("adb shell getprop ro.build.version.release", dev).simplified());
    android_version->setPic(":/ico/image/ico/android-line.svg");
    devInfo->addItemsToList(android_version);

    pageListItem *cpu = new pageListItem(devInfo);
    cpu->setText("处理器 | CPU",explainer->explain_cpu_output(process->run("adb shell cat /proc/cpuinfo", dev)));
    cpu->setPic(":/ico/image/ico/cpu-line.svg");
    devInfo->addItemsToList(cpu);*/
    /****************别删***************/
    return devInfo;
}

basePage* pageMaker::createPage_devInfo_rec(QWidget *parent, device dev)
{
    /*
    CItemWidget* pItemWidget = new CItemWidget(this)；
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(350, 40));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, pItemWidget);*/

    basePage *devInfo = new basePage(parent);
    devInfo->isBasePage = true;
    devInfo->whoYouAre("devInfo");
    int val[20] = {};
    //qDebug() << "!!!!!!!!!!!!!!!!!!!" << *val;
    devInfo->setEnableValue(val);
    devInfo->setDev(dev);
    /**/

    pageListItem *productModel = new pageListItem(devInfo);
    //qDebug() << "dev of pageMaker" << dev.addr;
    productModel->setText("设备型号 | DeviceModel",process->run("adb shell getprop ro.product.model", dev).simplified());
    productModel->setPic(":/ico/image/ico/profile-line.svg");
    devInfo->addItemsToList(productModel);

/*
    pageListItem *screen_resolution = new pageListItem(devInfo);
    screen_resolution->setText("屏幕分辨率","当前状态无法获取");
    screen_resolution->setPic(":/ico/image/ico/fullscreen-line.svg");
    devInfo->addItemsToList(screen_resolution);


    //adb shell wm density  *****************
    pageListItem *dpi = new pageListItem(devInfo);
    dpi->setText("屏幕密度 | DPI","当前状态无法获取");
    dpi->setPic(":/ico/image/ico/grid-line.svg");
    //dpi->setSelectable();
    devInfo->addItemsToList(dpi);

    //adb shell settings get secure android_id

    pageListItem *android_id = new pageListItem(devInfo);
    android_id->setText("Android Id","当前状态无法获取");
    android_id->setPic(":/ico/image/ico/barcode-line.svg");
    devInfo->addItemsToList(android_id);*/

    //adb shell getprop ro.build.version.release
    pageListItem *android_version = new pageListItem(devInfo);
    android_version->setText("Recovery 版本",process->run("adb shell getprop ro.build.version.release", dev).simplified());
    android_version->setPic(":/ico/image/ico/android-line.svg");
    devInfo->addItemsToList(android_version);

    pageListItem *cpu = new pageListItem(devInfo);
    cpu->setText("处理器 | CPU",explainer->explain_cpu_output(process->run("adb shell cat /proc/cpuinfo", dev)));
    cpu->setPic(":/ico/image/ico/cpu-line.svg");
    devInfo->addItemsToList(cpu);
    /**/
    return devInfo;
}

basePage* pageMaker::createPage_acvitator(QWidget *parent, device dev)
{
    basePage *activator = new basePage(parent);
    activator->isBasePage = true;
    //activatorPage *activator = new activatorPage(parent);
    activator->whoYouAre("activator");
    int val[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    activator->setEnableValue(val);
    activator->setDev(dev);

    pageListItem *Brevent = new pageListItem(activator);
    Brevent->setText("黑阈","adb -d shell sh /data/data/me.piebridge.brevent/brevent.sh");
    Brevent->setPic(":/activatorApps/image/activatorApps/brevent.png");
    Brevent->setSelectable();
    activator->addItemsToList(Brevent);

    pageListItem *IceBox_dpm = new pageListItem(activator);
    IceBox_dpm->setText("冰箱 - 设备管理员","adb shell dpm set-device-owner com.catchingnow.icebox/.receiver.DPMReceiver");
    IceBox_dpm->setPic(":/activatorApps/image/activatorApps/icebox.png");
    IceBox_dpm->setSelectable();
    activator->addItemsToList(IceBox_dpm);

    pageListItem *IceBox = new pageListItem(activator);
    IceBox->setText("冰箱 - 普通模式","adb shell sh /sdcard/Android/data/com.catchingnow.icebox/files/start.sh");
    IceBox->setPic(":/activatorApps/image/activatorApps/icebox.png");
    IceBox->setSelectable();
    activator->addItemsToList(IceBox);

    pageListItem *StopApp = new pageListItem(activator);
    StopApp->setText("小黑屋 - 设备管理员","adb shell dpm set-device-owner web1n.stopapp/.receiver.AdminReceiver");
    StopApp->setPic(":/activatorApps/image/activatorApps/blackroom.png");
    StopApp->setSelectable();
    activator->addItemsToList(StopApp);

    pageListItem *StopApp_Maxwell = new pageListItem(activator);
    StopApp_Maxwell->setText("小黑屋 - 麦克斯韦妖","adb shell sh /storage/emulated/0/Android/data/web1n.stopapp/files/starter.sh");
    StopApp_Maxwell->setPic(":/activatorApps/image/activatorApps/blackroom.png");
    StopApp_Maxwell->setSelectable();
    activator->addItemsToList(StopApp_Maxwell);

    pageListItem *shizuku = new pageListItem(activator);
    shizuku->setText("Shizuku","adb shell sh /sdcard/Android/data/moe.shizuku.privileged.api/start.sh");
    shizuku->setPic(":/activatorApps/image/activatorApps/shizuku.png");
    shizuku->setSelectable();
    activator->addItemsToList(shizuku);

    pageListItem *BlackHole = new pageListItem(activator);
    BlackHole->setText("黑洞","adb shell dpm set-device-owner com.hld.apurikakusu/.receiver.DPMReceiver");
    BlackHole->setPic(":/activatorApps/image/activatorApps/blackhole.png");
    BlackHole->setSelectable();
    activator->addItemsToList(BlackHole);

    pageListItem *TaiChi = new pageListItem(activator);
    TaiChi->setText("太极","adb shell dpm set-device-owner me.weishu.exp/.DeviceAdmin");
    TaiChi->setPic(":/activatorApps/image/activatorApps/taichi.png");
    TaiChi->setSelectable();
    activator->addItemsToList(TaiChi);

    pageListItem *Island = new pageListItem(activator);
    Island->setText("Island","adb -d shell dpm set-device-owner com.oasisfeng.island/.IslandDeviceAdminReceiver");
    Island->setPic(":/activatorApps/image/activatorApps/island.png");
    Island->setSelectable();
    activator->addItemsToList(Island);

    pageListItem *scene = new pageListItem(activator);
    scene->setText("Scene","adb shell sh /data/user/0/com.omarea.vtools/files/up.sh");
    scene->setPic(":/activatorApps/image/activatorApps/scene5.png");
    scene->setSelectable();
    activator->addItemsToList(scene);

    pageListItem *watchfps = new pageListItem(activator);
    watchfps->setText("看帧数+","adb shell sh /sdcard/Download/watchfps/watchfps.sh");
    watchfps->setPic(":/activatorApps/image/activatorApps/watchfps.png");
    watchfps->setSelectable();
    activator->addItemsToList(watchfps);

    pageListItem *permissiondog = new pageListItem(activator);
    permissiondog->setText("权限狗","adb shell sh /storage/emulated/0/Android/data/com.web1n.permissiondog/files/starter.sh");
    permissiondog->setPic(":/activatorApps/image/activatorApps/permissiondog.png");
    permissiondog->setSelectable();
    activator->addItemsToList(permissiondog);

    pageListItem *hail = new pageListItem(activator);
    hail->setText("雹","adb shell dpm set-device-owner com.aistra.hail/.receiver.DeviceAdminReceiver");
    hail->setPic(":/activatorApps/image/activatorApps/hail.png");
    hail->setSelectable();
    activator->addItemsToList(hail);

    pageListItem *bg_useage = new pageListItem(activator);
    bg_useage->setText("BatteryGuru - 使用情况访问权限","adb shell pm grant com.paget96.batteryguru android.permission.PACKAGE_USAGE_STATS");
    bg_useage->setPic(":/activatorApps/image/activatorApps/bg.png");
    bg_useage->setSelectable();
    activator->addItemsToList(bg_useage);

    pageListItem *bg_secure = new pageListItem(activator);   //15
    bg_secure->setText("BatteryGuru - 修改安全系统设置","adb shell pm grant com.paget96.batteryguru android.permission.WRITE_SECURE_SETTINGS");
    bg_secure->setPic(":/activatorApps/image/activatorApps/bg.png");
    bg_secure->setSelectable();
    activator->addItemsToList(bg_secure);

    pageListItem *bg_dump = new pageListItem(activator);
    bg_dump->setText("BatteryGuru - 读取 DUMP","adb shell pm grant com.paget96.batteryguru android.permission.DUMP");
    bg_dump->setPic(":/activatorApps/image/activatorApps/bg.png");
    bg_dump->setSelectable();
    activator->addItemsToList(bg_dump);

    pageListItem *apkInstaller = new pageListItem(activator);
    apkInstaller->setText("安装狮","adb shell dpm set-device-owner com.modosa.apkinstaller/.receiver.AdminReceiver");
    apkInstaller->setPic(":/activatorApps/image/activatorApps/apkinstaller.png");
    apkInstaller->setSelectable();
    activator->addItemsToList(apkInstaller);


    return activator;
}

basePage* pageMaker::createPage_apps(QWidget *parent, device dev)
{
    basePage *apps = new basePage(parent);
    apps->isBasePage = true;
    //activatorPage *activator = new activatorPage(parent);
    apps->whoYouAre("apps");
    int val[20] = {1,2,3,4,5,6,7};
    apps->setEnableValue(val);
    apps->setDev(dev);

    pageListItem *installer = new pageListItem(apps);
    installer->setText("安装应用","adb install <filename>");
    installer->setPic(":/ico/image/ico/install-line.svg");
    installer->setSelectable();
    apps->addItemsToList(installer);

    pageListItem *permissionGroups = new pageListItem(apps);
    permissionGroups->setText("已知权限组","adb shell pm list permission-groups");
    permissionGroups->setPic(":/ico/image/ico/about/information-line.svg");
    permissionGroups->setSelectable();
    apps->addItemsToList(permissionGroups);

    pageListItem *permissions = new pageListItem(apps);
    permissions->setText("已知权限","adb shell pm list permissions");
    permissions->setPic(":/ico/image/ico/about/information-line.svg");
    permissions->setSelectable();
    apps->addItemsToList(permissions);

    pageListItem *packages = new pageListItem(apps);
    packages->setText("软件包","adb shell pm list packages");
    packages->setPic(":/ico/image/ico/android-line.svg");
    packages->setSelectable();
    apps->addItemsToList(packages);

    pageListItem *features = new pageListItem(apps);
    features->setText("系统功能","adb shell pm list features");
    features->setPic(":/ico/image/ico/tools-line.svg");
    features->setSelectable();
    apps->addItemsToList(features);

    pageListItem *libraries = new pageListItem(apps);
    libraries->setText("库","adb shell pm list libraries");
    libraries->setPic(":/ico/image/ico/stack-line.svg");
    libraries->setSelectable();
    apps->addItemsToList(libraries);

    pageListItem *users = new pageListItem(apps);
    users->setText("用户","adb shell pm list users");
    users->setPic(":/ico/image/ico/user-line.svg");
    users->setSelectable();
    apps->addItemsToList(users);

    return apps;
}

basePage* pageMaker::createPage_devControl(QWidget *parent, device dev)
{
    if(dev.state == "[未响应]" || dev.state == "[REC]" || dev.state == "[侧载]" || dev.state == "[未知]")
    {
        basePage *devControl = new basePage(parent);
        devControl->isBasePage = true;
        //activatorPage *activator = new activatorPage(parent);
        devControl->whoYouAre("devControl");
        int val[20] = {1};
        devControl->setEnableValue(val);
        devControl->setDev(dev);

        pageListItem *power = new pageListItem(devControl);
        power->setText("电源","adb reboot <n>");
        power->setPic(":/ico/image/ico/shut-down-line.svg");
        power->setSelectable();
        devControl->addItemsToList(power);

        return devControl;
    }
    else
    {
        basePage *devControl = new basePage(parent);
        devControl->isBasePage = true;
        //activatorPage *activator = new activatorPage(parent);
        devControl->whoYouAre("devControl");
        int val[20] = {1,2};
        devControl->setEnableValue(val);
        devControl->setDev(dev);

        pageListItem *power = new pageListItem(devControl);
        power->setText("电源","adb reboot <n>");
        power->setPic(":/ico/image/ico/shut-down-line.svg");
        power->setSelectable();
        devControl->addItemsToList(power);

        pageListItem *btnEmulate = new pageListItem(devControl);
        btnEmulate->setText("按键模拟","adb shell input keyevent <key>");
        btnEmulate->setPic(":/ico/image/ico/drag-move-line.svg");
        btnEmulate->setSelectable();
        devControl->addItemsToList(btnEmulate);

        return devControl;
    }
}


basePage* pageMaker::createPage_recovery(QWidget *parent, device dev)
{
    basePage *recovery = new basePage(parent);
    recovery->isBasePage = true;
    //activatorPage *activator = new activatorPage(parent);
    recovery->whoYouAre("recovery");
    int val[20] = {1};
    recovery->setEnableValue(val);
    recovery->setDev(dev);

    pageListItem *power = new pageListItem(recovery);
    power->setText("侧载","adb sideload <filename>");
    power->setPic(":/ico/image/ico/refund-line.svg");
    power->setSelectable();
    recovery->addItemsToList(power);

    return recovery;
}

basePage* pageMaker::createPage_advanced(QWidget *parent, device dev)
{
    basePage *advanced = new basePage(parent);
    advanced->isBasePage = true;
    //activatorPage *activator = new activatorPage(parent);
    advanced->whoYouAre("advanced");
    int val[20] = {1,2,3,4,5};
    advanced->setEnableValue(val);
    advanced->setDev(dev);

    pageListItem *customize_command = new pageListItem(advanced);
    customize_command->setText("运行自定义命令","<customize command>");
    customize_command->setPic(":/ico/image/ico/code-s-slash-line.svg");
    customize_command->setSelectable();
    advanced->addItemsToList(customize_command);

    pageListItem *accounts = new pageListItem(advanced);
    accounts->setText("账户","adb shell dumpsys account");
    accounts->setPic(":/ico/image/ico/user-settings-line.svg");
    accounts->setSelectable();
    advanced->addItemsToList(accounts);

    pageListItem *captive_portal = new pageListItem(advanced);
    captive_portal->setText("去除叹号","adb shell settings put global captive_portal_http_url <server avilable>");
    captive_portal->setPic(":/ico/image/ico/signal-wifi-error-line.svg");
    captive_portal->setSelectable();
    advanced->addItemsToList(captive_portal);

    pageListItem *scales = new pageListItem(advanced);
    scales->setText("过渡动画","adb shell settings put global <animation type>");
    scales->setPic(":/ico/image/ico/donut-chart-line.svg");
    scales->setSelectable();
    advanced->addItemsToList(scales);

    pageListItem *status_bar = new pageListItem(advanced);
    status_bar->setText("状态栏与导航栏","adb shell settings put secure icon_blacklist <icon name>");
    status_bar->setPic(":/ico/image/ico/layout-top-2-line.svg");
    status_bar->setSelectable();
    advanced->addItemsToList(status_bar);

    //:/ico/image/ico/layout-top-2-line.svg
    /*
    pageListItem *btnEmulate = new pageListItem(recovery);
    btnEmulate->setText("按键模拟","adb shell input keyevent <key>");
    btnEmulate->setPic(":/ico/image/ico/refund-line.svg");
    btnEmulate->setSelectable();
    recovery->addItemsToList(btnEmulate);*/

    return advanced;
}

basePage* pageMaker::createPage_about(QWidget *parent)
{
    about* abt = new about(parent);
    return abt;
}

basePage* pageMaker::createPage_disabled(QWidget *parent)
{
    basePage *disabled = new basePage(parent);
    disabled->isBasePage = true;
    disabled->whoYouAre("disabled");
    int val[20] = {};
    //qDebug() << "!!!!!!!!!!!!!!!!!!!" << *val;
    disabled->setEnableValue(val);
    /**/

    pageListItem *productModel = new pageListItem(disabled);
    //qDebug() << "dev of pageMaker" << dev.addr;
    productModel->setText("设备未开机","功能暂不可用");
    productModel->setPic(":/ico/image/ico/close-circle-line.svg");
    disabled->addItemsToList(productModel);

    return disabled;
}

pageMaker::pageListItemStruct* pageMaker::initStruct(QWidget* parent)
{
    pageListItemStruct *itemStruct = new pageListItemStruct();
    itemStruct->explainer = new textExplainer();
    itemStruct->item = new pageListItem();
    itemStruct->item->setParent(parent);
    itemStruct->process = new adbProcess();
    itemStruct->thread = new adbThread();
    return itemStruct;
}
