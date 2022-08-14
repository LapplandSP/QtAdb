#ifndef SP_ACTIVATOR_H
#define SP_ACTIVATOR_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>
#include <QFile>
#include "adbprocess.h"
#include "../sonpagebase.h"
#include "../standardoutputpage.h"

namespace Ui {
class sp_activator;
}

class sp_activator : public QWidget
{
    Q_OBJECT

public:
    explicit sp_activator(QWidget *parent = nullptr);
    ~sp_activator();

    void setUp(QString qss, QString title, QString profile, QString command);
    QString command;
    device dev;
    standardOutputPage *page = NULL;
    QWidget *parents;

    void setDev(device device);

private slots:
    void on_runBtn_clicked();

    void on_showOutputBtn_clicked(bool checked);

private:
    Ui::sp_activator *ui;

    adbProcess *process;
};

#endif // SP_ACTIVATOR_H
