#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>
#include "sonPages/pay.h"

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private slots:
    void on_btn_website_clicked();

    void on_btn_coolapk_clicked();

    void on_btn_github_clicked();

    void on_btn_money_2_clicked();

private:
    Ui::about *ui;
};

#endif // ABOUT_H
