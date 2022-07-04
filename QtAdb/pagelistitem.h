#ifndef PAGELISTITEM_H
#define PAGELISTITEM_H

#include <QWidget>

#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>
#include <QClipboard>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

namespace Ui {
class pageListItem;
}

class pageListItem : public QWidget
{
    Q_OBJECT

public:
    explicit pageListItem(QWidget *parent = nullptr);
    ~pageListItem();

    void setText(QString title, QString profile);
    void setPic(QString qss);
    void setSelectable();

private slots:
    void on_copyButton_clicked();

private:
    Ui::pageListItem *ui;
};

#endif // PAGELISTITEM_H
