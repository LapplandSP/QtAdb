#ifndef SONPAGEBASE_H
#define SONPAGEBASE_H

#include <QWidget>

namespace Ui {
class sonPageBase;
}

class sonPageBase : public QWidget
{
    Q_OBJECT

public:
    explicit sonPageBase(QWidget *parent = nullptr);
    ~sonPageBase();

    QWidget *parents;
    void setTitle(QString title);

private:
    Ui::sonPageBase *ui;
};

#endif // SONPAGEBASE_H
