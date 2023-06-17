#ifndef INDEXLISTITEM_H
#define INDEXLISTITEM_H

#include <QWidget>

namespace Ui {
class indexListItem;
}

class indexListItem : public QWidget
{
    Q_OBJECT

public:
    explicit indexListItem(QWidget *parent = nullptr);
    ~indexListItem();

    void setText(QString text);
    void setPic(QString qss);

private:
    Ui::indexListItem *ui;
};

#endif // INDEXLISTITEM_H
