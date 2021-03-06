#include "pagemaker.h"
/*
pageMaker::pageMaker()
{

}*/

pageMaker::pageMaker()
{
    process = new adbProcess();
    explainer = new textExplainer();
}

QWidget* pageMaker::createPageWithKey(int key, QWidget *parent, device dev)
{
    int k = key;
    switch(k)
    {
    case 0:
        if(dev.state == "[开机]")
        {
            return createPage_devInfo(parent , dev);
            break;
        }
        else
        {
            return createPage_devInfo_powerdown(parent, dev);
        }

    case 1:
        return createPage_acvitator(parent, dev);
        break;
    case 2:
        return createPage_apps(parent, dev);
        break;
    case 3:
        return createPage_devControl(parent, dev);
        break;
    case 4:
        return createPage_recovery(parent, dev);
        break;
    case 5:
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
    devInfo->whoYouAre("devInfo");
    int val[20] = {3};
    //qDebug() << "!!!!!!!!!!!!!!!!!!!" << *val;
    devInfo->setEnableValue(val);
    devInfo->setDev(dev);
    /**/

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
    devInfo->addItemsToList(cpu);
    /**/
    return devInfo;
}

basePage* pageMaker::createPage_devInfo_powerdown(QWidget *parent, device dev)
{
    /*
    CItemWidget* pItemWidget = new CItemWidget(this)；
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(350, 40));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, pItemWidget);*/

    basePage *devInfo = new basePage(parent);
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
    devInfo->addItemsToList(android_id);

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
    //activatorPage *activator = new activatorPage(parent);
    activator->whoYouAre("activator");
    int val[20] = {1,2,3,4,5,6,7,8,9};
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

    return activator;
}

basePage* pageMaker::createPage_apps(QWidget *parent, device dev)
{
    basePage *apps = new basePage(parent);
    //activatorPage *activator = new activatorPage(parent);
    apps->whoYouAre("apps");
    int val[20] = {1};
    apps->setEnableValue(val);
    apps->setDev(dev);

    pageListItem *installer = new pageListItem(apps);
    installer->setText("安装应用","adb install <filename>");
    installer->setPic(":/ico/image/ico/install-line.svg");
    installer->setSelectable();
    apps->addItemsToList(installer);

    return apps;
}

basePage* pageMaker::createPage_devControl(QWidget *parent, device dev)
{
    basePage *devControl = new basePage(parent);
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

basePage* pageMaker::createPage_recovery(QWidget *parent, device dev)
{
    basePage *recovery = new basePage(parent);
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

    /*
    pageListItem *btnEmulate = new pageListItem(recovery);
    btnEmulate->setText("按键模拟","adb shell input keyevent <key>");
    btnEmulate->setPic(":/ico/image/ico/refund-line.svg");
    btnEmulate->setSelectable();
    recovery->addItemsToList(btnEmulate);*/

    return recovery;
}

QWidget* pageMaker::createPage_about(QWidget *parent)
{
    about* abt = new about(parent);
    return abt;
}
