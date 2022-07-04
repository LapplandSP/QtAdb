#ifndef SP_DPICHANGER_H
#define SP_DPICHANGER_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

#include "adbprocess.h"
#include "textexplainer.h"

namespace Ui {
class sp_dpiChanger;
}

class sp_dpiChanger : public QWidget
{
    Q_OBJECT

public:
    explicit sp_dpiChanger(QWidget *parent = nullptr);
    ~sp_dpiChanger();

    adbProcess *process;
    textExplainer *explainer;
    device dev;

    void setDev(device device);

private slots:
    void on_runBtn_clicked();
    void on_refreshBtn_clicked();

private:
    Ui::sp_dpiChanger *ui;
    void setDpiInfo();
    void refresh();
};

#endif // SP_DPICHANGER_H
