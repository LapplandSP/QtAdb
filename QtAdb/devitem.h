#ifndef DEVITEM_H
#define DEVITEM_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
//#include "abstract/comboboxlistwidget.h"
#include "textexplainer.h"

namespace Ui {
class devItem;
}

class devItem : public QWidget
{
    Q_OBJECT

public:
    explicit devItem(QWidget *parent = nullptr);
    ~devItem();

    void setAddr(QString);
    void setDevModel(QString);
    void setDevice(QString);
    void setName(QString);
    void setStat(QString);

    textExplainer *explainer;

private slots:
    void on_lineEdit_editingFinished();

private:
    Ui::devItem *ui;

signals:
    void addName(QString,QString);
};

#endif // DEVITEM_H
