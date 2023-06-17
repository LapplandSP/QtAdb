#ifndef SP_WMSIZE_H
#define SP_WMSIZE_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

#include "adbprocess.h"
#include "textexplainer.h"
#include "../../animationwidget.h"

namespace Ui {
class sp_wmsize;
}

class sp_wmsize : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_wmsize(QWidget *parent = nullptr);
    ~sp_wmsize();

    adbProcess *process;
    textExplainer *explainer;
    device dev;

    void setDev(device device);

private slots:
    void on_runBtn_clicked();
    void on_refreshBtn_clicked();

private:
    Ui::sp_wmsize *ui;
    void setWmInfo();
    void refresh();

};

#endif // SP_WMSIZE_H
