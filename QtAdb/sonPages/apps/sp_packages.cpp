#include "sp_packages.h"
#include "ui_sp_packages.h"

sp_packages::sp_packages(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_packages)
{
    ui->setupUi(this);

    pa = parent;

    ui->progressBar->hide();
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    thread = new adbThread();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));


    connect(thread,SIGNAL(signal_output(QString)),this,SLOT(refresh_tableView(QString)));
    connect(ui->checkBox_d,SIGNAL(clicked()),this,SLOT(setArgs()));
    connect(ui->checkBox_e,SIGNAL(clicked()),this,SLOT(setArgs()));
    connect(ui->checkBox_s,SIGNAL(clicked()),this,SLOT(setArgs()));
    connect(ui->checkBox_3,SIGNAL(clicked()),this,SLOT(setArgs()));

    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);

    QFile file("://qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listView->verticalScrollBar()->setStyleSheet(file.readAll());

}

sp_packages::~sp_packages()
{
    delete ui;
}

void sp_packages::setDev(device device)
{
    dev = device;
    on_refreshBtn_clicked();
}

void sp_packages::on_refreshBtn_clicked()
{
    QString cmd = "adb shell pm list packages";
    //setArgs();
    thread->initThread(cmd.append(arg) , dev, "#PERMISSIONGROUPS#");
    ui->progressBar->setVisible(true);
    thread->start();
    arg.clear();
}

void sp_packages::refresh_tableView(QString s)
{
    QStandardItemModel* emptyModel = new QStandardItemModel(this);
    ui->listView->setModel(emptyModel);
    //thread->exit();
    //qDebug() << "before";
    QStringList packagesList = explainer->explainPermissionGroups(s);
    //qDebug() << "after";
    QStandardItemModel* model = new QStandardItemModel(this);

    if(!packagesList.isEmpty())
    {
        for(int i = 0; i < packagesList.count(); i++)
        {
            //qDebug() << "permissionList.count() = " << packagesList.count() <<"\nbefore index out of range: \n i = " << i << "\n permissionList[i] = "<< packagesList[i];
            QStringList tempList;
            tempList = packagesList[i].simplified().split(":");

            if(tempList.count() >= 2)
            {
                model->setItem(i,0,new QStandardItem(tempList[1]));
            }
        }
        ui->listView->setStyleSheet("QListView::item{height:24px;}");
        model->sort(Qt::AscendingOrder);
        ui->listView->setModel(model);
        this->update();
    }

    ui->progressBar->setVisible(false);
    delete emptyModel;

}

void sp_packages::on_listView_clicked(const QModelIndex &index)
{
    QString name = ui->listView->model()->data(index).toString();
    tp_packageProfile * profilePage = new tp_packageProfile(NULL,name);
    profilePage->setDevice(dev);
    connect(profilePage,SIGNAL(packageChanged()),this,SLOT(on_refreshBtn_clicked()));
    profilePage->show();
}

void sp_packages::setArgs()
{
    if(ui->checkBox_e->isChecked())
    {
        arg.append(" -e");
    }

    if(ui->checkBox_d->isChecked())
    {
        arg.append(" -d");
    }

    if(ui->checkBox_s->isChecked())
    {
        arg.append(" -s");
    }

    if(ui->checkBox_3->isChecked())
    {
        arg.append(" -3");
    }
    on_refreshBtn_clicked();
}
