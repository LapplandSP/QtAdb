#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>

namespace Ui {
class monitor;
}

class monitor : public QWidget
{
    Q_OBJECT

public:
    explicit monitor(QWidget *parent = nullptr);
    ~monitor();

private:
    Ui::monitor *ui;
};

#endif // MONITOR_H
