#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>

namespace Ui {
class welcomePage;
}

class welcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit welcomePage(QWidget *parent = nullptr);
    ~welcomePage();

private:
    Ui::welcomePage *ui;
};

#endif // WELCOMEPAGE_H
