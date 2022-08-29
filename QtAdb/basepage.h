#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QScroller>
#include <QScrollBar>

#include "pagelistitem.h"
#include "sonPages/sonpagemanager.h"
#include "animationwidget.h"

namespace Ui {
class basePage;
}

class basePage : public animationWidget
{
    Q_OBJECT
signals:
    void creatingSonPage();

public:
    explicit basePage(QWidget *parent = nullptr);
    ~basePage();

    QWidget *parents;

    basePage *lastPage;
    QWidget *sonPage;
    QWidget *father;
    QString myName;
    sonPageManager *SPManager;
    int enableVal[20];
    //pageMaker *maker;
    device dev;


    void addItemsToList(pageListItem *itemWidget);
    void setFather(QWidget *parent);
    QString whoAmI();
    void whoYouAre(QString name);
    void setEnableValue(int val[20]);
    void setDev(device dev);



    void self_castrate();

private:
    Ui::basePage *ui;

    bool isEnable(int k);

    QTimer *listTimer;

    //QGraphicsOpacityEffect* exitOpacity;

public slots:
    //void playExitAnimation();

    //void refresh_listItem_effect();

private slots:
    void slot_createSonPage(int key);
    void slot_destroySonPage();
    void unlock();
    void slot_spgAnimationEnd();
};

#endif // BASEPAGE_H
