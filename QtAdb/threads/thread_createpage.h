#ifndef THREAD_CREATEPAGE_H
#define THREAD_CREATEPAGE_H

#include <QThread>
#include "../basepage.h"
#include "../pagemaker.h"
#include "../sonPages/sonpagemanager.h"
#include "../adbprocess.h"

class thread_createPage : public QThread
{
    Q_OBJECT
public:
    explicit thread_createPage(QObject *parent = nullptr);

    pageMaker *maker;

    basePage* bPage;

    sonPageManager *SPManager;
    QWidget *createSonPage(QWidget *parent, QString parentName, int key , device dev);
    QWidget *sPage;

public slots:
    QWidget* createBasePage(int key, QWidget *parent, device dev, QWidget* page);
signals:
    void basePageCreated();
    void sonPageCreated();

};

#endif // THREAD_CREATEPAGE_H
