#ifndef SP_FEATURES_H
#define SP_FEATURES_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>
//#include <QAbstractItemView>
#include "../../threads/adbthread.h"

namespace Ui {
class sp_features;
}

class sp_features : public QWidget
{
    Q_OBJECT

public:
    explicit sp_features(QWidget *parent = nullptr);
    ~sp_features();

    device dev;
    void setDev(device dev);

private slots:
    void on_refreshBtn_clicked();

public slots:
    void refresh_tableView(QString);

private:
    Ui::sp_features *ui;
    adbThread *thread;
    textExplainer *explainer;
};

#endif // SP_FEATURES_H
