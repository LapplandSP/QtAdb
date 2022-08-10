#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QObject>

#include <QWidget>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

namespace Ui {
class animationWidget;
}

class animationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit animationWidget(QWidget *parent = nullptr);
    ~animationWidget();


    void playLoadAnimation();
    void playExitAnimation();

    bool isBasePage;
    QWidget *parent;

    QPropertyAnimation *animation;
    /*
    QGraphicsOpacityEffect * graphicsOpacityEffect;
    QPropertyAnimation * opacityLoadAnimation;
    QPropertyAnimation * opacityExitAnimation;*/

signals:
    void animationEnd();

};


#endif // ANIMATIONWIDGET_H
