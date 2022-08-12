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
    void setText_title(QString title);
    void setText_profile(QString profile);
    void setPic(QString qss);
    void setSelectable();

    void setStyles();

    //void emitSignal();

private slots:
    void on_copyButton_clicked();

private:
    Ui::pageListItem *ui;

    QGraphicsDropShadowEffect *shadowEffect_icon;

public slots:
    void slot_setText(QString t, QString p);
    void slot_setText_title(QString t);
    void slot_setText_profile(QString p);
    void slot_setStyles();

signals:
    //void
};

#endif // PAGELISTITEM_H
