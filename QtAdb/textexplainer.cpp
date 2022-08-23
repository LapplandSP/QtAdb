#include "textexplainer.h"

textExplainer::textExplainer()
{

}

QList<device> textExplainer::getDevList(QString tmpStr)
{

    QStringList tmpList;
    QList<device> devList;

    tmpList = tmpStr.split("\n");

    //qDebug() << "tmplist:  " <<  tmpList << "\n";
    //qDebug() << tmpList.size() << "\n";

    for(int i = 1; i < tmpList.size() ; i++)
    {
        qDebug() << "fuckQt1";
        //qDebug() << "tmplist[" <<  i << "]\n";
        tmpList[i] = tmpList[i].simplified();

        if (tmpList[i] == "")
        {
            continue;
        }

        QStringList tmp = tmpList[i].split("device product:");
        QString tmpInfo = tmp[1];
        QStringList finalInfo = tmpInfo.split(" ");

        for (int i = 1; i <= 3; i++ )
        {
            QStringList infoSimplier = finalInfo[i].split(":");
            finalInfo[i] = infoSimplier[1];
        }
        finalInfo.prepend(tmp[0]);
        //qDebug() << "finalDevInfo NO." << i << ":" << finalInfo;
        device dev;
        //qDebug() << i;
        dev.addr = finalInfo[0].simplified();
        //qDebug() << "dev.addr:" << dev.addr;
        dev.device_product = finalInfo[1];
        //qDebug() << "device_product:" << dev.device_product;
        dev.model = finalInfo[2];
        //qDebug() << "model:" << dev.model;
        dev.device_debug = finalInfo[3];
        //qDebug() << "device_debug:" << dev.device_debug;
        dev.transport_id = finalInfo[4];
        //qDebug() << "transport_id:" << dev.transport_id;
        devList.append(dev);
        //qDebug() << dev.addr;
    }

    return devList;
}

QList<device> textExplainer::getDevList_windows(QString tmpStr)
{

    QStringList tmpList;
    QList<device> devList;

    tmpList = tmpStr.split("\n");

    //qDebug() << "tmplist:  " <<  tmpList << "\n";
    //qDebug() << tmpList.size() << "\n";

    for(int i = 1; i < tmpList.size() ; i++)
    {
        tmpList[i] = tmpList[i].simplified();

        //qDebug() << "tmplist[" << i << "] =" <<  tmpList[i];
        if (tmpList[i] == "" || tmpList[i] == "\r")
        {
            continue;
        }

        QStringList tmp = tmpList[i].split(" ");

        device dev;

        dev.addr = tmp[0];
        dev.state = setState(tmp[1]);
        //qDebug() << dev.state;
        //qDebug() << "*tmplist[" << i << "] =" <<  tmpList[i];
        if(dev.state == "[未响应]")
        {
            dev.transport_id = tmp[2];
            devList.append(dev);
            continue;
        }
        else
        {
            dev.device_product = tmp[2];
            dev.model = tmp[3];
            dev.device_debug = tmp[4];
            dev.transport_id = tmp[5];
            devList.append(dev);
        }
        //qDebug() << "**tmplist[" << i << "] =" <<  tmpList[i];
    }
    return devList;
    //qDebug() << "get dev list success!";
}

QString textExplainer::get_words_after(QString str , QString key)
{
    QString text = str;
    //qDebug() << "text is:" << text << "\n";
    int index = str.lastIndexOf(key);
    //qDebug() << "index =" << index << "\n";
    text = text.right(text.size()-index-key.size());
    //qDebug() << "key.size =" << key.size() << "\n";
    text = text.simplified();
    return text;
}

QString textExplainer::get_words_before(QString str , QString key)
{
    QString text = str;
    //qDebug() << "text is:" << text << "\n";
    int index = str.indexOf(key);
    //qDebug() << "index =" << index << "\n";
    text = text.left(index);
    //qDebug() << "key.size =" << key.size() << "\n";
    text = text.simplified();
    return text;
}

QString textExplainer::explain_cpu_output(QString str)
{
    QString text = str;
    QStringList tmpList = text.split("\n");
    QString tmpInfo = tmpList[tmpList.count()-2];
    //qDebug() << tmpList;
    tmpInfo = tmpInfo.simplified();
    //qDebug() << "tmpInfo =" << tmpInfo << "\n";

    return get_words_after(tmpInfo, ":");
}

bool textExplainer::explainError(QString err)
{
    qDebug() << "err = " << err;
    err = err.simplified();

    /*普通*/
    if(err.contains("No such file or directory"))
    {
        qDebug() << "into if";
        showMsgBox("失败"," · 应用未安装 \n · 应用安装后未首次运行");
    }
    else if(err.contains("Permission denied"))
    {
        showMsgBox("失败"," · 请先运行应用");
    }
    /*启动*/
    else if(err.contains("daemon not running")){}
    else if(err.contains("daemon started successfully")){}
    else if(err.contains("doesn't match this client")){}
    /*软件包*/
    else if(err.contains("install requires an argument"))
    {
        showMsgBox("提示"," · 请先选择安装包");
    }
    else if(err.contains("failed to install") && err.contains("cmd: not found"))
    {
        showMsgBox("错误"," · 当前设备状态无法安装应用");
    }
    else if(err.contains("Shell cannot change component state for") && err.contains("cmd: not found"))
    {
        showMsgBox("错误"," · 无法执行该指令");
    }
    /*用户*/
    else if(err.contains("couldn't remove user id 0"))
    {
        showMsgBox("无法操作"," · 无法删除默认用户");
    }
    else if(err.contains("no user id specified"))
    {
        showMsgBox("未选择"," · 请先选择一个用户");
    }
    /* 设备管理员 */
    else if(err.contains("Not allowed to set the device owner because there are already several users on the device"))
    {
        showMsgBox("失败"," · 请先清除所有用户并关闭多用户模式  \n · 可在「软件包管理器」-「用户」中查看并删除用户  \n");
    }
    else if(err.contains("Unknown admin"))
    {
        showMsgBox("失败"," · 设备管理员应用未安装");
    }
    else if(err.contains("Not allowed to set the device owner because there are already some accounts on the device"))
    {
        showMsgBox("失败"," · 请先退出所有账户  \n · 可在「其它」-「账户」中查看设备中的账户  \n · 或在设备设置中查看并退出账户  \n");
    }
    else if(err.contains("Trying to set the device owner, but device owner is already set."))
    {
        showMsgBox("失败"," · 存在冲突的设备管理员应用");
    }
    /*无线调试*/
    //No pairing code provided
    else if(err.contains("No pairing code provided"))
    {
        showMsgBox("失败"," · 请输入配对码");
    }
    /*recovery*/
    else if(err.contains("cmd: not found"))
    {
        showMsgBox("错误"," · 当前设备状态无法执行该命令\n · 请确认当前设备状态（开机、REC等）能否执行该操作");
    }
    else if(err.contains("dpm: not found"))
    {
        showMsgBox("错误"," · 当前设备状态无法执行该命令\n · 请确认当前设备状态（开机、REC等）能否执行该操作");
    }
    else if(err.contains("am: not found"))
    {
        showMsgBox("错误"," · 当前设备状态无法执行该命令\n · 请确认当前设备状态（开机、REC等）能否执行该操作");
    }
    else if(err.contains("input: not found"))
    {
        showMsgBox("错误"," · 当前设备状态无法执行该命令\n · 请确认当前设备状态（开机、REC等）能否执行该操作");
    }
    /*其他情况*/
    else if(err.contains("could not start server"))
    {
        showMsgBox("提示"," · 程序上次运行时异常退出，您可以反馈此问题");
    }
    else if(err.contains("Done"))
    {
        showMsgBox("完成"," · 成功\n · 你之所以会看到这条提示，是因为ADB本身将成功的消息以错误输出方式输出\n · 您无需关注此错误");
    }
    else if(err.contains("Bad arguments"))
    {
        showMsgBox("错误"," · 参数有误");
    }
    else
    {
        showMsgBox("错误"," · 未知错误！\n" + err +"\n · 若此处出现并不完整的报错或一大串包含 '.android.os'、'java' 等字样的错误，您可以视情况忽忽视它，并查阅另一条报错\n");
    }

    qDebug() << "<<<<<<<<<<<<<<<<ERROR>>>>>>>>>>>>>>>>" << "\n" << err;
    return true;
}

bool textExplainer::explainOutput(QString op, bool thread)
{
    //qDebug() << "output = " << op;
    op = op.simplified();

    /*普通*/
    if(op.contains("No such file or directory") && thread == false)
    {
        showMsgBox("失败"," · 应用未安装 \n · 应用安装后未首次运行");
    }
    //qDebug() << "+++++++++++++++++Output+++++++++++++++++" << "\n" << op;
    return true;
}

void textExplainer::showMsgBox(QString title, QString msg)
{
    if(!thread)
    {
        msgBox = new QMessageBox;
        msgBox->setWindowIcon(QIcon(":/ico/image/ico/link.svg"));
        msgBox->setStyleSheet("background-color:rgba(255,255,255,1);border:0px; border-radius:0px;");
        msgBox->setWindowTitle(title);
        msgBox->setText(msg);
        msgBox->addButton(" ✓ ", QMessageBox::AcceptRole);
        msgBox->show();
    }
}

QString textExplainer::setState(QString state)
{
    if(state == "offline")
    {
        return "[未响应]";
    }
    else if(state == "device")
    {
        return "[开机]";
    }
    else if(state == "recovery")
    {
        return "[REC]";
    }
    else if(state == "sideload")
    {
        return "[侧载]";
    }
    return "[未知]";
}
/*
void textExplainer::slot_get_words_after(QString s, QString k)
{
    QString str = get_words_after(s, k);
    emit textExplained(str);
}

void textExplainer::slot_explain_cpu_output(QString s)
{
    QString str = explain_cpu_output(s);
    emit textExplained(str);
}
*/

QStringList textExplainer::explainPermissionGroups(QString s)
{
    QStringList list;
    list = s.split("\n");

    return list;
}

QStringList textExplainer::explainAccounts(QString s)
{
    QStringList final;
    QStringList classific_as_users;
    classific_as_users = s.split("}:");

    for(int i = 1; i<classific_as_users.count(); i++)
    {
        qDebug() << "/+*********\n classific_as_users.count() = " << classific_as_users.count() <<"\n before index out of range: \n i = " << i << "\n list[i] = "<< classific_as_users[i] << "\n ***************+/";
        QStringList tmpList;
        tmpList = get_words_before(classific_as_users[i],"AccountId,").split("Account ");
        if(!tmpList.isEmpty())
        {
            QString num = QString::number(i-1);
            tmpList[0] = tmpList[0].replace("Accounts:", "属于用户" + num + "的账户数量为：");
        }

        qDebug() << "tmpList =" << tmpList;
        final.append(tmpList);
        //classific_as_users[i] = tmpStr;
    }
    return final;
}
