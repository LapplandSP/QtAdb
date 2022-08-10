#include "sonpagemanager.h"

sonPageManager::sonPageManager()
{
    process = new adbProcess();
    explainer = new textExplainer();
}

QWidget* sonPageManager::selector(QWidget *parent , QString parentName, int key, device dev)
{
    if(parentName == "devInfo")
    {
        //qDebug() << "dev.addr=" << dev.addr;
        return createSonPageFor_devInfo(parent, key , dev);
        //return createSonPageFor_activator(parent);
    }
    else if(parentName == "activator")
    {
        return createSonPageFor_activator(parent, key , dev);
    }
    else if(parentName == "apps")
    {
        return createSonPageFor_apps(parent, key , dev);
    }
    else if(parentName == "devControl")
    {
        return createSonPageFor_devControl(parent, key , dev);
    }
    else if(parentName == "recovery")
    {
        return createSonPageFor_recovery(parent, key , dev);
    }
    else if(parentName == "advanced")
    {
        return createSonPageFor_advanced(parent, key , dev);
    }

    throw "failed to create sonPage!";
    return NULL;
}

sp_dpiChanger* sonPageManager::createSonPageFor_devInfo(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 3:
    {
        sp_dpiChanger *page = new sp_dpiChanger(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

sp_activator* sonPageManager::createSonPageFor_activator(QWidget *parent, int key, device dev)
{
    //sp_activator *page = new sp_activator(parent);
    //return page;
    switch(key + 1)
    {
    case 1 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/brevent.png);",
                    "激活 黑阈",
                    "黑阈™不需要 root 也不需要解锁，能有效防止恶意应用在后台运行，从而让手机流畅省电。\n"
                    "黑阈主要采取以下手段来限制应用后台：\n"
                    "1. 停用状态。应用处于停用状态时，不会收到 Android 系统及 GMS 发送的广播，从而避免“被动运行”。\n"
                    "2. 待机。待机以后，应用无法访问网络，执行任务与同步等。这减少Android 系统被动运行该应用，同时即使运行也减少其网络活动。\n",
                    "adb -d shell sh /data/data/me.piebridge.brevent/brevent.sh");
        return page;
        break;
    }
    case 2  :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/icebox.png);",
                    "激活 冰箱 - 设备管理员",
                    "使用**设备管理器**模式激活冰箱前，请按下列步骤操作：\n"
                    "1. 确保手机上已安装冰箱，删除屏幕锁，索尼手机取出 SIM 卡，MIUI 开启「USB 调试（安全设置）」并关闭「MIUI 优化」\n"
                    "2. 在系统设置中，**注销所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再登录回来。\n",
                    "adb shell dpm set-device-owner com.catchingnow.icebox/.receiver.DPMReceiver");
        return page;
        break;
    }
    case 3 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/icebox.png);",
                    "激活 冰箱 - 普通模式",
                    "如果您未能成功配置设备管理员模式的冰箱，则可以考虑使用普通 ADB 模式。\n"
                    "- 优点：无需删除帐号等复杂步骤，直接使用\n"
                    "- 缺点：每次重启手机后必须要重新激活，否则无法冻结解冻 App\n"
                    "- 激活后需保持 USB 调试始终打开，设置 USB 连接设置为「仅充电」（MIUI 需开启「USB 调试（安全设置）」）\n",
                    "adb shell sh /sdcard/Android/data/com.catchingnow.icebox/files/start.sh");
        return page;
        break;
    }
    case 4 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackroom.png);", "激活 小黑屋 - 设备管理员",
                    "使用**设备管理器**模式激活小黑屋前，注意以下事项：\n"
                    "1. 打开手机开发者选项与 USB 调试，将 USB 连接设置为「仅充电」（小米手机需开启开发者选项「USB 调试（安全设置）」）。\n"
                    "2. 进入手机「设置 - 帐号」，删除所有的帐号，包括你的 Google 帐号、小米账号、华为账号等（激活后可以再登录回来）。\n"
                    "3. 如果您之前设置过访客模式、应用双开或是多用户设置等，也需要一并关闭或删除（激活后可以打开）。\n",
                    "adb shell dpm set-device-owner web1n.stopapp/.receiver.AdminReceiver");
        return page;
        break;
    }
    case 5 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackroom.png);",
                    "激活 小黑屋 - 麦克斯韦妖",
                    "麦克斯韦妖是小黑屋的一款冻结模式。借助它，小黑屋可以免 Root 权限冻结应用程序。  \n"
                    "麦克斯韦妖引擎与 ROM 的兼容性很好，不会出现设备管理员模式与 ROM 之间的一些兼容性问题。  \n"
                    "**麦克斯韦妖优点**  \n"
                    "- 无需移除账号与用户等操作，激活成功率极高。  \n"
                    "- 冻结速度快，点击即冻结。  \n\n"
                    "**麦克斯韦妖缺点**  \n"
                    "- 关机后即失效，因此每次开机需要重新激活。若不重新激活将无法打开已冻结 app。  \n",
                    "adb shell sh /storage/emulated/0/Android/data/web1n.stopapp/files/starter.sh");
        return page;
        break;
    }
    case 6 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/shizuku.png);", "激活 Shizuku",
                    "Android 11 及以上支持无线调试，您可以直接在设备上启动 Shizuku。  \n"
                    "对于未 root 设备，则需要借助 adb 启动。  \n"
                    "**请注意**  \n"
                    "- 设备重新启动后需要再次连接电脑。  \n"
                    "在一些定制系统上 Shizuku 可能会随机停止，此时:  \n\n"
                    "- 不要关闭“USB 调试”及“开发者选项”  \n"
                    "- 保证在连接电脑期间 USB 使用模式不变。通常的做法是在“开发者选项”中将 USB 使用模式改为“仅充电”  \n"
                    "- 连接 USB 后，若弹出类似“是否允许访问文件”的对话框，请不要点击它，因为点击后 USB 使用模式会发生变化。  \n"
                    "- Sony 设备不要点击连接 USB 后弹出的对话框。  \n",
                    "adb shell sh /sdcard/Android/data/moe.shizuku.privileged.api/start.sh");
        return page;
        break;
    }
    case 7 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackhole.png);", "激活 黑洞",
                    "**黑洞**已在各大平台下架且无法找到帮助文档。  \n"
                    "但您仍可通过 QtAdb 激活它的设备管理员模式。",
                    "adb shell dpm set-device-owner com.hld.apurikakusu/.receiver.DPMReceiver");
        return page;
        break;
    }
    case 8 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/taichi.png);", "激活 太极",
                    "**阴阳之门的用途**  \n"
                    "1. 可以大幅优化 太极 创建应用和升级应用的流程；不再需要手动确认，整个流程可以一气呵成。  \n"
                    "2. 额外提供类似冰箱的冻结功能；可以冻结和隐藏应用。  \n\n"
                    "**注意事项**  \n"
                    "1. 首先确保您已安装太极。  \n"
                    "2. 进入手机「设置 - 帐户」，删除 所有 的帐户，包括你的 Google 帐户（之后可以再登录回来）。  \n"
                    "3. 如果您之前设置过多用户或手机自带访客模式、应用双开等，也需要一并关闭或删除（之后可以打开）。  \n",
                    "adb shell dpm set-device-owner me.weishu.exp/.DeviceAdmin");
        return page;
        break;
    }
    case 9 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/island.png);", "激活 炼妖壶Island - 上帝模式",
                    "激活 Island 『上帝模式』：（可冻结任何应用，而不仅限于 Island 空间内的应用）  \n"
                    "由于 Android 系统的限制，首先需要在系统设置 - 账户 中移除所有已登录的账户 及 除了主用户外的其它用户（包括曾使用过的『访客』用户）。  \n"
                    "账户移除后，对应的应用可能需要重新登录，但大部分国内应用并不影响登录（因为它们使用账户机制是别的目的）。  \n"
                    "其次，如果你已经创建了 Island 空间（Work profile），也必须先在 Island - Settings - Setup 中移除。在激活『上帝模式』后，你可以再重新创建 Island 空间。  \n",
                    "adb -d shell dpm set-device-owner com.oasisfeng.island/.IslandDeviceAdminReceiver");
        return page;
        break;
    }

    break;
    }
    return NULL;
}

sp_installer* sonPageManager::createSonPageFor_apps(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_installer *page = new sp_installer(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

QWidget* sonPageManager::createSonPageFor_devControl(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_devControl_power *page = new sp_devControl_power(parent);
        page->setDev(dev);
        return page;
    }
    case 2:
    {
        btnEmulator *page = new btnEmulator(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

QWidget* sonPageManager::createSonPageFor_recovery(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_recovery *page = new sp_recovery(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

QWidget* sonPageManager::createSonPageFor_advanced(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_customize_cmd *page = new sp_customize_cmd(parent);
        //page->setDev(dev);
        return page;
    }
    case 2:
    {
        //QString envPath = qgetenv("PATH");      //获取当前环境变量
        QString appDirPath = QApplication::applicationDirPath();    //获取程序所在位置
        QString batPath = appDirPath + "/platform-tools/open-cmd-here.bat";
        //qDebug()<<"batPath = " << batPath;
        QProcess batProcess;
        batProcess.start(batPath);
        batProcess.waitForFinished();
        return NULL;
    }
        break;
    }
    return NULL;
}
