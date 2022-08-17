#include "animationwidget.h"

animationWidget::animationWidget(QWidget *p)
{
    animation = new QPropertyAnimation(this,"geometry");
    setParent(p);
    parent = p;
    this->hide();
}

void animationWidget::playLoadAnimation()
{
    animation->setDuration(750);
    //animation->setEndValue(QPoint(301,117));
    qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301, 117 - 6, 600,wgtHeight));
    }
    else
    {
        animation->setEndValue(QRect(301, 117 - 6, parent->width(),wgtHeight));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 + 50, 117 - 6, parent->width()-50,wgtHeight));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playLoadAnimation(int h)
{
    animation->setDuration(750);
    //animation->setEndValue(QPoint(301,117));
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301, 117 - 6, 600,h));
    }
    else
    {
        animation->setEndValue(QRect(301, 117 - 6, parent->width(),h));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 + 50, 117 - 6, parent->width()-50,h));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playExitAnimation()
{

}

animationWidget::~animationWidget()
{
    playExitAnimation();
    delete animation;
}
