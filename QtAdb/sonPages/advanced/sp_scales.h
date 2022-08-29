#ifndef SP_SCALES_H
#define SP_SCALES_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpressionValidator>
//#include <QRegularExpressionValidator>
#include "../../adbprocess.h"
#include "../../threads/adbthread.h"

namespace Ui {
class sp_scales;
}

class sp_scales : public QWidget
{
    Q_OBJECT

public:
    explicit sp_scales(QWidget *parent = nullptr);
    ~sp_scales();

    device dev;
    void setDev(device dev);

private slots:
    void on_pushButton_animation_clicked();

    void on_pushButton_transition_clicked();

    void on_pushButton_window_clicked();

private:
    Ui::sp_scales *ui;

    adbProcess *process;
    textExplainer *explainer;

    void setShadow(QWidget* wgt);
    void refresh();

private slots:
    void setText_animator(QString);
    void setText_transition(QString);
    void setText_window(QString);

};

#endif // SP_SCALES_H
