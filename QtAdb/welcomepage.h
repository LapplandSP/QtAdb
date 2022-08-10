#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include "animationwidget.h"

namespace Ui {
class welcomePage;
}

class welcomePage : public animationWidget
{
    Q_OBJECT

public:
    explicit welcomePage(QWidget *parent = nullptr);
    ~welcomePage();

private:
    Ui::welcomePage *ui;
};

#endif // WELCOMEPAGE_H
