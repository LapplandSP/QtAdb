#include "sp_permissions.h"
#include "ui_sp_permissions.h"

sp_permissions::sp_permissions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sp_permissions)
{
    ui->setupUi(this);
    pa = parent;

    ui->progressBar->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    thread = new adbThread();
    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));


    connect(thread,SIGNAL(signal_output(QString)),this,SLOT(refresh_tableView(QString)));

    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_settingsBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_openBtn = new QGraphicsDropShadowEffect(this);

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);

    shadowEffect_settingsBtn->setOffset(0,0);
    shadowEffect_settingsBtn->setColor(Qt::green);
    shadowEffect_settingsBtn->setBlurRadius(5);

    shadowEffect_openBtn->setOffset(0,0);
    shadowEffect_openBtn->setColor(Qt::gray);
    shadowEffect_openBtn->setBlurRadius(5);


    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);
    ui->back_to_basePage_2->setGraphicsEffect(shadowEffect_settingsBtn);
    ui->open_another_window->setGraphicsEffect(shadowEffect_openBtn);

}

sp_permissions::~sp_permissions()
{
    delete ui;
}

void sp_permissions::on_back_to_basePage_2_clicked()
{
    arg = "";
    arg_g = false;
    arg_f = false;
    arg_s = false;
    arg_d = false;
    arg_u = false;
    settings = new QDialog();
    group = new QButtonGroup(settings);

    btn_g = new QRadioButton();
    btn_f = new QRadioButton();
    btn_s = new QRadioButton();
    btn_d = new QRadioButton();
    btn_u = new QRadioButton();
    closeBtn = new QPushButton();

    btn_g->setText("【高级】按组进行整理");
    btn_f->setText("【高级】输出所有信息");
    btn_s->setText("简短摘要（推荐）");
    btn_d->setText("仅列出危险权限");
    btn_u->setText("仅列出用户将看到的权限");
    closeBtn->setText("确定");

    btn_g->autoExclusive();
    btn_f->autoExclusive();
    btn_s->autoExclusive();
    btn_d->autoExclusive();
    btn_u->autoExclusive();

    QVBoxLayout *layout = new QVBoxLayout();

    settings->setLayout(layout);
    group->addButton(btn_g);
    group->addButton(btn_f);
    group->addButton(btn_s);
    group->addButton(btn_d);
    group->addButton(btn_u);
    layout->addWidget(btn_g);
    layout->addWidget(btn_f);
    layout->addWidget(btn_s);
    layout->addWidget(btn_d);
    layout->addWidget(btn_u);
    layout->addWidget(closeBtn);
    settings->setStyleSheet("background-color:white;border:0px solid white;border-radius:4px;");

    connect(btn_g, SIGNAL(clicked()), this,SLOT(setArg()));
    connect(btn_f, SIGNAL(clicked()), this,SLOT(setArg()));
    connect(btn_s, SIGNAL(clicked()), this,SLOT(setArg()));
    connect(btn_d, SIGNAL(clicked()), this,SLOT(setArg()));
    connect(btn_u, SIGNAL(clicked()), this,SLOT(setArg()));

    connect(closeBtn, SIGNAL(clicked()), this,SLOT(setArg()));
    connect(closeBtn, SIGNAL(clicked()), settings,SLOT(close()));
    connect(closeBtn, SIGNAL(clicked()), this,SLOT(on_refreshBtn_clicked()));

    settings->setWindowTitle("选项");
    settings->move(ui->back_to_basePage_2->geometry().x(),ui->back_to_basePage_2->geometry().y());
    settings->exec();
}

void sp_permissions::setArg()
{
    //qDebug() << "\narg_g = " << arg_g << "arg_f = " << arg_f << "arg_s = " << arg_s << "arg_d = " << arg_d << "arg_u = " << arg_u;
    if(btn_g->isChecked())
    {
        //qDebug() << "g";
        arg = "-g";
        arg_g = true;
        arg_f = false;
        arg_s = false;
        arg_d = false;
        arg_u = false;
    }
    else if(btn_f->isChecked())
    {
        //qDebug() << "f";
        arg = "-f";
        arg_g = false;
        arg_f = true;
        arg_s = false;
        arg_d = false;
        arg_u = false;
    }
    else if(btn_s->isChecked())
    {
        //qDebug() << "s";
        arg = "-s";
        arg_g = false;
        arg_f = false;
        arg_s = true;
        arg_d = false;
        arg_u = false;
    }
    else if(btn_d->isChecked())
    {
        //qDebug() << "d";
        arg = "-d";
        arg_g = false;
        arg_f = false;
        arg_s = false;
        arg_d = true;
        arg_u = false;
    }
    else if(btn_u->isChecked())
    {
        //qDebug() << "u";
        arg = "-u";
        arg_g = false;
        arg_f = false;
        arg_s = false;
        arg_d = false;
        arg_u = true;
    }
    else
    {
        //qDebug() << "g";
        arg = "";
        arg_g = false;
        arg_f = false;
        arg_s = false;
        arg_d = false;
        arg_u = false;
    }

    //qDebug() << "clicked,arg = " << arg;
}

void sp_permissions::setDev(device device)
{
    dev = device;
    on_refreshBtn_clicked();
}

void sp_permissions::on_refreshBtn_clicked()
{
    QString cmd = "adb shell pm list permissions";
    thread->initThread(cmd.append(" ").append(arg) , dev, "#PERMISSIONGROUPS#");
    ui->progressBar->setVisible(true);
    thread->start();
}

void sp_permissions::refresh_tableView(QString s)
{
    if(arg_g)
    {
        //arg = "-g";
        //qDebug() << "**************#01# formating data*****************";
        //qDebug() << "arg = " << arg;
        //qDebug() << "###################### s = \n" << s;
        QStandardItemModel* emptyModel = new QStandardItemModel(this);
        ui->tableView->setModel(emptyModel);
        QStringList groupList = s.split("group:");
        //qDebug() << "###################### groupList = \n" << groupList;
        QList<QStringList> groups;



        //qDebug() << "###################### split####################";
        for(int i = 0 , j = i; i < groupList.count(); i++)
        {
            QStringList tmpList;
            tmpList = groupList[i].split("\n");
            groups.append(tmpList);
            j++;
        }

        //qDebug() << "###################### groups = \n" << groups;

        //qDebug() << "**************#02# adding title*****************";
        QStandardItemModel* model = new QStandardItemModel(this);

        if(!groupList.isEmpty())
        {
            for(int i = 1; i < groups.count();i++)
            {
                //qDebug() << "**************header data***************** =" << groups[i][0];
                model->setColumnCount(groups.count());
                model->setHeaderData(i-1,Qt::Horizontal, groups[i][0]);

                for(int j = 1; j< groups[i].count();j++)
                {
                    model->setItem(j-1,i-1,new QStandardItem(groups[i][j].simplified().simplified()));
                }
            }

            ui->tableView->horizontalHeader()->setDefaultSectionSize(150);
            ui->tableView->setModel(model);
            current_model = model;

            this->update();
        }

        ui->progressBar->setVisible(false);
        delete emptyModel;
    }
    else if(arg_f)
    {
        //arg = "-g";
        //qDebug() << "**************#01# formating data*****************";
        //qDebug() << "arg = " << arg;
        //qDebug() << "###################### s = \n" << s;
        QStandardItemModel* emptyModel = new QStandardItemModel(this);
        ui->tableView->setModel(emptyModel);
        QStringList groupList = s.split("+");
        //qDebug() << "###################### groupList = \n" << groupList;
        QList<QStringList> groups;



        //qDebug() << "###################### split####################";
        for(int i = 0 , j = i; i < groupList.count(); i++)
        {
            QStringList tmpList;
            tmpList = groupList[i].split("\n");
            groups.append(tmpList);
            j++;
        }

        //qDebug() << "###################### groups = \n" << groups;

        //qDebug() << "**************#02# adding title*****************";
        QStandardItemModel* model = new QStandardItemModel(this);

        if(!groupList.isEmpty())
        {
            model->setColumnCount(5);
            model->setHeaderData(0,Qt::Horizontal, "permission");
            model->setHeaderData(1,Qt::Horizontal, "package");
            model->setHeaderData(2,Qt::Horizontal, "label");
            model->setHeaderData(3,Qt::Horizontal, "description");
            model->setHeaderData(4,Qt::Horizontal, "protectionLevel");

            for(int i = 1; i < groups.count();i++)
            {
                //qDebug() << "**************header data***************** =" << groups[i][0];

                for(int j = 0; j< groups[i].count() && j <= 5;j++)
                {
                    QStringList tempList;
                    tempList = groups[i][j].simplified().simplified().split(":");
                    //qDebug() << "********************" << tempList << tempList.count();;

                    if(tempList.count() >= 2)
                    {
                        //qDebug() << "来做死";
                        model->setItem(i-1,j,new QStandardItem(tempList[1]));
                    }
                }
            }

            ui->tableView->horizontalHeader()->setDefaultSectionSize(150);
            ui->tableView->setModel(model);
            current_model = model;

            this->update();
        }

        ui->progressBar->setVisible(false);
        delete emptyModel;
        //arg = "-f";
    }
    else if(arg_s)
    {
        //arg = "-s";
        generalMode(s);
    }
    else if(arg_d)
    {
        generalMode(s);
    }
    else if(arg_u)
    {
        //arg = "-u";
        generalMode(s);
    }
    else
    {
        //arg = "";
        generalMode(s);
    }
}

void sp_permissions::on_open_another_window_clicked()
{
    QWidget *wgt = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    QTableView *view = new QTableView();
    view->setModel(current_model);
    wgt->setLayout(layout);
    layout->addWidget(view);
    wgt ->showMaximized();
}

void sp_permissions::generalMode(QString s)
{
    QStandardItemModel* emptyModel = new QStandardItemModel(this);
    ui->tableView->setModel(emptyModel);
    QStringList permissionList = s.split("\n");
    QStandardItemModel* model = new QStandardItemModel(this);

    if(!permissionList.isEmpty())
    {
        model->setHeaderData(0,Qt::Horizontal, permissionList[0]);
        for(int i = 2,j = i; i < permissionList.count();i++)
        {
            //qDebug() << "IT IS:" << permissionList[i];
            if(permissionList[i] == "" || permissionList[i] == "\r")
            {
                //qDebug() << "1";
            }
            else
            {
                //qDebug() << "2";
                model->setItem(j-2,0,new QStandardItem(permissionList[i].simplified().simplified()));
                j++;
            }
        }
        ui->tableView->horizontalHeader()->setDefaultSectionSize(pa->geometry().width() - 200);
        ui->tableView->setModel(model);
        current_model = model;
        this->update();
    }

    ui->progressBar->setVisible(false);
    delete emptyModel;
}
