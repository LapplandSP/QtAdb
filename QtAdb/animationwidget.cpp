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
    animation->setEndValue(QRect(301, 117, this->width(),this->height()));
    animation->setStartValue(QRect(301 + 50, 117, this->width(),this->height()));

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
