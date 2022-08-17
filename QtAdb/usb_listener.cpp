#include "usb_listener.h"
#include <QApplication>
#include <QDebug>

#include <typeinfo>

bool usb_listener::nativeEventFilter(const QByteArray &eventType, void *message, long long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    //qDebug() << "msg = " << msg;
    unsigned int msgType = msg->message;
    //qDebug() << "msgType = " << msgType;
    //qDebug() << WM_DEVICECHANGE;
    if(msgType == WM_DEVICECHANGE) {
        emit DeviceChangeCbk();

        //qDebug() << "msgType = " << msgType;
        //qDebug() << "WM_DEVICECHANGE = " << WM_DEVICECHANGE;
        qDebug() << "wParam = " << msg->wParam;
        //qDebug() << "lParam = " << msg->lParam;
        //qDebug() << "WM_DEVICECHANGE = " << WM_DEVICECHANGE;
        qDebug() << "DBT_DEVICEARRIVAL = " << DBT_DEVICEARRIVAL;
        qDebug() << "DBT_DEVICEREMOVECOMPLETE = " << DBT_DEVICEREMOVECOMPLETE;
/*
        PDEV_BROADCAST_HDR lpdb = PDEV_BROADCAST_HDR(msg->lParam);
        qDebug() << "lpdb = " << msg->lParam;
        PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = PDEV_BROADCAST_DEVICEINTERFACE(lpdb);
        qDebug() << "pDevInf = " << pDevInf;
        qDebug() << "pDevInf->dbcc_name = " << pDevInf->dbcc_name;
        QString device_name = "插入设备(name)："+QString::fromWCharArray(pDevInf->dbcc_name,int(pDevInf->dbcc_size)).toUtf8();

        qDebug() << device_name;*/
        //bool dbg =  msg->lParam == WM_DEVICECHANGE;
        //qDebug() << "msg->lParam == WM_DEVICECHANGE = " <<dbg;*/
        //qDebug() << "WM_DEVICECHANGE type = " << typeid(WM_DEVICECHANGE).name();
        //qDebug() << "msg->lParam type = " << typeid(msg->lParam).name();
        //if(msg->wParam == DBT_DEVICEARRIVAL)
        emit DeviceChanged();
        //if(msg->lParam == WM_DEVICECHANGE)
        if(msg->wParam == DBT_DEVICEARRIVAL)
        {
            qDebug("usb in");
            emit DevicePlugIn();         //触发信号
        }
        if(msg->wParam == DBT_DEVICEREMOVECOMPLETE)
        {
            qDebug("usb out");
            emit DevicePlugOut();         //触发信号
        }
    }

    return QWidget::nativeEvent(eventType, message, result);
}

void usb_listener::EmitMySignal()
{
    emit DevicePlugIn();
}
/*
bool usb_listener::nativeEvent(const QByteArray &eventType, void *message, long long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);//第一层解算
    qDebug() << "msg = " << msg;
    UINT msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = PDEV_BROADCAST_HDR(msg->lParam);//第二层解算
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = PDEV_BROADCAST_DEVICEINTERFACE(lpdb);
                QString device_name = "插入设备(name)："+QString::fromWCharArray(pDevInf->dbcc_name,int(pDevInf->dbcc_size)).toUtf8();

                qDebug()<< device_name;
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = PDEV_BROADCAST_DEVICEINTERFACE(lpdb);
                QString device_name = "移除设备(name)："+QString::fromWCharArray(pDevInf->dbcc_name,int(pDevInf->dbcc_size)).toUtf8();

                qDebug()<< device_name;
            }
            break;
        }
    }
    return false;
}
*/
