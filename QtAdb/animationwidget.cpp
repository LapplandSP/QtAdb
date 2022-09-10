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
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11, 600,wgtHeight));
    }
    else
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11, parent->width(),wgtHeight));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 + 50 - 29, 117 - 6 - 11, parent->width()-50,wgtHeight));

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
        animation->setEndValue(QRect(301 - 29, 117 - 6 -11, 600,h));
    }
    else
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11, parent->width(),h));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 + 50 - 29, 117 - 6 - 11, parent->width()-50,h));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    //this->setDisabled(true);
    emit animationEnd();
}

void animationWidget::playLoadAnimation_sp(int h)
{
    animation->setDuration(500);
    //animation->setEndValue(QPoint(301,117));
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(0,0, parent->width(),h));
    }
    else
    {
        animation->setEndValue(QRect(0,0, parent->width(),h));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(0,-10, parent->width(),h));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playLoadAnimation_bp(int h)
{
    animation->setDuration(500);
    //animation->setEndValue(QPoint(301,117));
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 -11, 600,h));
    }
    else
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11, parent->width(),h));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 - 29, 117 - 6 - 11 + 10, parent->width(),h));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playExitAnimation()
{
    animation->setDuration(300);
    //animation->setEndValue(QPoint(301,117));
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11 + 50, parent->width(),wgtHeight));
    }
    else
    {
        animation->setEndValue(QRect(301 - 29, 117 - 6 - 11 + 50, parent->width(),wgtHeight));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    //animation->setStartValue(QRect(301 + 50 - 30, 117 - 6 - 11, parent->width()-50,wgtHeight));
    animation->setStartValue(QRect(301 - 29, 117 - 6 - 11, parent->width(),wgtHeight));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playExitAnimation_sp()
{
    animation->setDuration(500);
    //animation->setEndValue(QPoint(301,117));
    //qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(0,-11, parent->width(),wgtHeight));
    }
    else
    {
        animation->setEndValue(QRect(0,-11, parent->width(),wgtHeight));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(0,0, parent->width(),wgtHeight));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

animationWidget::~animationWidget()
{
    playExitAnimation();
    delete animation;
}
