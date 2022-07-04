#ifndef STANDARDOUTPUTPAGE_H
#define STANDARDOUTPUTPAGE_H

#include <QWidget>
#include <QTimer>
#include <QClipboard>
#include "adbprocess.h"

namespace Ui {
class standardOutputPage;
}

class standardOutputPage : public QWidget
{
    Q_OBJECT

public:
    explicit standardOutputPage(QWidget *parent = nullptr , adbProcess *cess = NULL);
    ~standardOutputPage();
    adbProcess *process;

private:
    Ui::standardOutputPage *ui;

public slots:
    void update();
private slots:
    void on_refreshBtn_clicked();
    void on_clearBtn_clicked();
    void on_copyBtn_clicked();
};

#endif // STANDARDOUTPUTPAGE_H
