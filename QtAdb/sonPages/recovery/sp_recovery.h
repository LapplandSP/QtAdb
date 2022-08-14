#ifndef SP_RECOVERY_H
#define SP_RECOVERY_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include "adbprocess.h"
#include "../standardoutputpage.h"
#include "../../threads/adbthread.h"
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
    adbThread * thread;

    QString labelDisplay;

private slots:
    void on_runBtn_clicked();

    void on_selectBtn_clicked();

    void on_showOutputBtn_clicked(bool checked);

    void updateProgress(QString);

private:
    Ui::sp_recovery *ui;

    QString zipPath;

    standardOutputPage *page = NULL;

    QGraphicsDropShadowEffect *shadowEffect_runBtn;
    QGraphicsDropShadowEffect *shadowEffect_showOutputBtn;
    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage;
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn;
    QGraphicsDropShadowEffect *shadowEffect_selectBtn;
    QGraphicsDropShadowEffect *shadowEffect_output;
    QGraphicsDropShadowEffect *shadowEffect_tips;
};

#endif // SP_RECOVERY_H
