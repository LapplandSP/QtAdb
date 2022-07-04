#ifndef PAGEMAKER_H
#define PAGEMAKER_H
#include "basepage.h"
#include "pagelistitem.h"
#include "adbprocess.h"
#include "textexplainer.h"
#include "about.h"


class pageMaker
{
public:
    //pageMaker();
    pageMaker();

    adbProcess *process;
    textExplainer *explainer;

    QWidget *createPageWithKey(int key, QWidget *parent, device dev);


    basePage *createPage_devInfo(QWidget *parent, device dev);
    basePage *createPage_devInfo_powerdown(QWidget *parent, device dev);

    basePage *createPage_acvitator(QWidget *parent, device dev);
    basePage *createPage_apps(QWidget *parent,device dev);

    basePage *createPage_devControl(QWidget *parent,device dev);

    basePage *createPage_recovery(QWidget *parent, device dev);

    QWidget *createPage_about(QWidget *parent);


    //activatorPage *createSonPage_activator(QWidget *parent, device dev);
private:
    /*youtPhone*/




};

#endif // PAGEMAKER_H
