#include "thread_createpage.h"

thread_createPage::thread_createPage(QObject *parent)
    : QThread{parent}
{

}

QWidget* thread_createPage::createBasePage(int key, QWidget *parent, device dev, QWidget *page)
{
    //bPage = new basePage();
    //qDebug() << "thread_createPage : creating BasePage";
    page = maker->createPageWithKey(key,parent,dev);
    //qDebug() << "thread_createPage : BasePage created";
    emit basePageCreated();
    //qDebug() << "thread_createPage : emit SIGNAL 'basePageCreated'";
    return NULL;
}

QWidget * thread_createPage::createSonPage(QWidget *parent, QString parentName, int key, device dev)
{
    sPage =  SPManager->selector(parent,parentName,key,dev);
    emit sonPageCreated();
    return NULL;
}
