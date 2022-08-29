#ifndef LINKS_H
#define LINKS_H

#include <QWidget>
#include <QFile>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class links;
}

class links : public QWidget
{
    Q_OBJECT

public:
    explicit links(QWidget *parent = nullptr);
    ~links();

private:
    Ui::links *ui;

    void setShadow(QWidget* wgt);
};

#endif // LINKS_H
