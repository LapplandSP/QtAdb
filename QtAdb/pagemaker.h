#ifndef PAGEMAKER_H
#define PAGEMAKER_H

#include <QThread>
#include "basepage.h"
#include "pagelistitem.h"
#include "adbprocess.h"
#include "textexplainer.h"
#include "about.h"

#include "threads/adbthread.h"
#include "animationwidget.h"

class pageMaker
{
public:
    //pageMaker();
    pageMaker();

    adbProcess *process;
    textExplainer *explainer;

    basePage *createPageWithKey(int key, QWidget *parent, device dev);


    basePage *createPage_devInfo(QWidget *parent, device dev);
    basePage *createPage_devInfo_powerdown(QWidget *parent, device dev);

    basePage *createPage_acvitator(QWidget *parent, device dev);
    basePage *createPage_apps(QWidget *parent,device dev);

    basePage *createPage_devControl(QWidget *parent,device dev);

    basePage *createPage_recovery(QWidget *parent, device dev);

    basePage *createPage_advanced(QWidget *parent, device dev);

    basePage *createPage_about(QWidget *parent);


    //activatorPage *createSonPage_activator(QWidget *parent, device dev);
    typedef struct{
        QWidget* parent;
        pageListItem* item;
        adbProcess *process;
        textExplainer *explainer;
        adbThread *thread;
    }pageListItemStruct;
private:
    /*youtPhone*/
    pageListItemStruct *initStruct(QWidget* parent);



};

#endif // PAGEMAKER_H
