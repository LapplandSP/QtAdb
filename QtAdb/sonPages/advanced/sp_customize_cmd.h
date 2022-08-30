#ifndef SP_CUSTOMIZE_CMD_H
#define SP_CUSTOMIZE_CMD_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "../../adbprocess.h"
#include "../../animationwidget.h"

namespace Ui {
class sp_customize_cmd;
}

class sp_customize_cmd : public animationWidget
{
    Q_OBJECT

public:
    explicit sp_customize_cmd(QWidget *parent = nullptr);
    ~sp_customize_cmd();

private slots:
    void on_runBtn_clicked();

private:
    Ui::sp_customize_cmd *ui;
    adbProcess *process;
};

#endif // SP_CUSTOMIZE_CMD_H
