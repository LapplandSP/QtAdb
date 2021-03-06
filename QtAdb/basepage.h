#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "pagelistitem.h"
#include "sonPages/sonpagemanager.h"

namespace Ui {
class basePage;
}

class basePage : public QWidget
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

private:
    Ui::basePage *ui;

    bool isEnable(int k);

    //QGraphicsOpacityEffect* exitOpacity;

public slots:
    void playExitAnimation();

private slots:
    void slot_createSonPage(int key);
    void slot_destroySonPage();
};

#endif // BASEPAGE_H
