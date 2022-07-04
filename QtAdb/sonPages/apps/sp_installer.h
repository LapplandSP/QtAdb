#ifndef SP_INSTALLER_H
#define SP_INSTALLER_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "adbprocess.h"
#include <QFileDialog>

namespace Ui {
class sp_installer;
}

class sp_installer : public QWidget
{
    Q_OBJECT

public:
    explicit sp_installer(QWidget *parent = nullptr);
    ~sp_installer();

    device dev;

    void setDev(device dev);

    adbProcess *process;

    QString labelDisplay;

private slots:
    void on_runBtn_clicked();

    void on_selectBtn_clicked();

private:
    Ui::sp_installer *ui;

    QString apkPath;
};

#endif // SP_INSTALLER_H
