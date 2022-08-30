#ifndef SP_LIBRARIES_H
#define SP_LIBRARIES_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"
#include <QScrollBar>
#include <QFile>
#include "../../animationwidget.h"

namespace Ui {
class sp_libraries;
}

class sp_libraries : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_libraries(QWidget *parent = nullptr);
    ~sp_libraries();

    device dev;
    void setDev(device dev);

private slots:
    void on_refreshBtn_clicked();

public slots:
    void refresh_tableView(QString);


private:
    Ui::sp_libraries *ui;
    adbThread *thread;
    textExplainer *explainer;

};

#endif // SP_LIBRARIES_H
