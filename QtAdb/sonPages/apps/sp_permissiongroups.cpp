#include "sp_permissiongroups.h"
#include "ui_sp_permissiongroups.h"

sp_permissionGroups::sp_permissionGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_permissionGroups)
{
    ui->setupUi(this);
    setParent(parent);

    ui->progressBar->hide();
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    thread = new adbThread();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    connect(thread,SIGNAL(signal_output(QString)),this,SLOT(refresh_tableView(QString)));

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

sp_permissionGroups::~sp_permissionGroups()
{
    delete ui;
}

void sp_permissionGroups::on_refreshBtn_clicked()
{
    thread->initThread("adb shell pm list permission-groups",dev,"#PERMISSIONGROUPS#");
    ui->progressBar->setVisible(true);
    thread->start();
}

void sp_permissionGroups::refresh_tableView(QString s)
{
    QStandardItemModel* emptyModel = new QStandardItemModel(this);
    ui->listView->setModel(emptyModel);
    //thread->exit();
    //qDebug() << "before";
    QStringList permissionList = explainer->explainPermissionGroups(s);
    //qDebug() << "after";
    QStandardItemModel* model = new QStandardItemModel(this);
    if(!permissionList.isEmpty())
    {
        for(int i = 0; i < permissionList.count(); i++)
        {
            //qDebug() << "permissionList.count() = " << permissionList.count() <<"\nbefore index out of range: \n i = " << i << "\n permissionList[i] = "<< permissionList[i];
            model->setItem(i,0,new QStandardItem(permissionList[i]));
        }
        ui->listView->setModel(model);
        this->update();
    }
    ui->progressBar->setVisible(false);
    delete emptyModel;
}

void sp_permissionGroups::setDev(device device)
{
    dev = device;
    on_refreshBtn_clicked();
}
