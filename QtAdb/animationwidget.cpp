#include "animationwidget.h"

animationWidget::animationWidget(QWidget *p)
{

    /*
    graphicsOpacityEffect = new QGraphicsOpacityEffect(this);
    graphicsOpacityEffect->setOpacity(1.0);
    this->setGraphicsEffect(graphicsOpacityEffect);*/

    animation = new QPropertyAnimation(this,"geometry");
    setParent(p);
    parent = p;
    this->hide();
    /*
    animation->setDuration(500);
    animation->setStartValue(QRect(this->geometry().x() + this->width()/2, this->geometry().y() + this->height()/2, this->width(),this->height()));
    animation->setEndValue(this->geometry());*/
    //animation->setEndValue(QRect(this->width(), 0, this->width(), this->height()));

    /*
    QPropertyAnimation *animation1= new QPropertyAnimation(this->centralWidget(),"geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(-this->centralWidget()->width(), 0, this->centralWidget()->width(), this->centralWidget()->height()));
    animation1->setEndValue(this->centralWidget()->geometry());

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animation1);
    group->start();*/
}

void animationWidget::playLoadAnimation()
{
    /*
    opacityLoadAnimation = new QPropertyAnimation(graphicsOpacityEffect,"opacity",this);
    opacityLoadAnimation->setDuration(500);
    opacityLoadAnimation->setStartValue(0);
    opacityLoadAnimation->setEndValue(1.0);
    opacityLoadAnimation->start();*/
    animation->setDuration(500);
    //qDebug() << "parent is " << parent;
    //qDebug() << "parent's geometry is " << parent->geometry();
    /*
    animation->setEndValue(QRect(parent->geometry().x(), parent->geometry().y(), this->width(),this->height()));
    animation->setStartValue(QRect(parent->geometry().x() + 50, parent->geometry().y(), this->width(),this->height()));*/

    animation->setEndValue(QRect(301, 111, this->width(),this->height()));
    animation->setStartValue(QRect(301 + 50, 111, this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
    emit animationEnd();
}

void animationWidget::playExitAnimation()
{
/*
    opacityExitAnimation = new QPropertyAnimation(graphicsOpacityEffect,"opacity",this);
    opacityExitAnimation->setDuration(500);
    opacityExitAnimation->setStartValue(1.0);
    opacityExitAnimation->setEndValue(0);

    opacityExitAnimation->start();*/
}

animationWidget::~animationWidget()
{
    playExitAnimation();
    //delete this;
}
