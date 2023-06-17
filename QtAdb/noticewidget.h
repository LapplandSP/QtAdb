#ifndef NOTICEWIDGET_H
#define NOTICEWIDGET_H

#include "qpropertyanimation.h"
#include "qtimer.h"
#include <QPainter>
#include <QWidget>

namespace Ui {
class noticeWidget;
}

class noticeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit noticeWidget(QWidget *parent = nullptr);
    ~noticeWidget();

    QPropertyAnimation *animation;

    void popUp(QString);
    QTimer *timer;




private:
    Ui::noticeWidget *ui;

private slots:
    void timeUp();
};

#endif // NOTICEWIDGET_H
