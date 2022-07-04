#ifndef SP_RECOVERY_H
#define SP_RECOVERY_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "adbprocess.h"
#include <QFileDialog>

namespace Ui {
class sp_recovery;
}

class sp_recovery : public QWidget
{
    Q_OBJECT

public:
    explicit sp_recovery(QWidget *parent = nullptr);
    ~sp_recovery();

    device dev;

    void setDev(device dev);

    adbProcess *process;

    QString labelDisplay;

private slots:
    void on_runBtn_clicked();

    void on_selectBtn_clicked();

private:
    Ui::sp_recovery *ui;

     QString zipPath;
};

#endif // SP_RECOVERY_H
