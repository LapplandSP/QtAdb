#ifndef LINKS_H
#define LINKS_H

#include <QWidget>
#include <QFile>

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
};

#endif // LINKS_H
