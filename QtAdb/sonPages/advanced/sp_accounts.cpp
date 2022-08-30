#include "sp_accounts.h"
#include "ui_sp_accounts.h"

sp_accounts::sp_accounts(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_accounts)
{
    ui->setupUi(this);
    setParent(parent);

    ui->progressBar->hide();
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    thread = new adbThread();
    process = new adbProcess();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    connect(thread,SIGNAL(signal_output(QString)),this,SLOT(refresh_tableView(QString)));

    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_deleteBtn = new QGraphicsDropShadowEffect(this);

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);

    shadowEffect_deleteBtn->setOffset(0,0);
    shadowEffect_deleteBtn->setColor(Qt::gray);
    shadowEffect_deleteBtn->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);
    ui->pushButton->setGraphicsEffect(shadowEffect_deleteBtn);

    QFile file("://qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listView->verticalScrollBar()->setStyleSheet(file.readAll());
    //on_refreshBtn_clicked();
}

sp_accounts::~sp_accounts()
{
    delete ui;
}

void sp_accounts::on_refreshBtn_clicked()
{
    thread->initThread("adb shell dumpsys account",dev,"#PERMISSIONGROUPS#");
    ui->progressBar->setVisible(true);
    thread->start();
}

void sp_accounts::refresh_tableView(QString s)
{
    QStandardItemModel* emptyModel = new QStandardItemModel(this);
    ui->listView->setModel(emptyModel);
    //thread->exit();
    //qDebug() << "before";
    QStringList accountsList = explainer->explainAccounts(s);
    //qDebug() << "after";
    QStandardItemModel* model = new QStandardItemModel(this);
    if(!accountsList.isEmpty())
    {
        for(int i = 0; i < accountsList.count(); i++)
        {
            //qDebug() << "permissionList.count() = " << permissionList.count() <<"\nbefore index out of range: \n i = " << i << "\n permissionList[i] = "<< permissionList[i];
            if(accountsList[i] != "")
            {
                model->setItem(i,0,new QStandardItem(accountsList[i].simplified()));
            }
        }
        ui->listView->setModel(model);
        this->update();
    }
    ui->progressBar->setVisible(false);
    delete emptyModel;
}

void sp_accounts::setDev(device device)
{
    dev = device;
    on_refreshBtn_clicked();
}

void sp_accounts::on_pushButton_clicked()
{
    /*
    QString user_id = explainer->get_words_before(explainer->get_words_after(ui->listView->model()->data(ui->listView->currentIndex()).toString(), "{"), ":");
    QMessageBox::StandardButton result=QMessageBox::question(NULL, "删除用户","您确定要删除用户吗？");
    qDebug() << "result =" << result;
    if(result == QMessageBox::Yes)
    {
        if(user_id == "Users")
        {
            QMessageBox::information(NULL, "选择错误","请选择一个用户，而不是标题");
        }
        else
        {
            process->run("adb shell pm remove-user " + user_id ,dev);
            qDebug() << "user_id:" << user_id;
        }
    }*/
    //qDebug() << "clicked";
}
