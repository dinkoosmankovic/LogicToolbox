#include "BarWidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QGraphicsProxyWidget>


BarWidget::BarWidget (QWidget * parent)
            : QWidget (parent)
{
    checkFixed = new QCheckBox ("Fix");
    checkFixed->setChecked (false);
    QGroupBox   * groupI    = new QGroupBox   ("Group I");
    QGroupBox   * groupII   = new QGroupBox   ("Group II");
    QPushButton * buttonA   = new QPushButton ("Button A");
    QPushButton * buttonB   = new QPushButton ("Button B");
    QPushButton * buttonC   = new QPushButton ("Button C");
    QPushButton * buttonD   = new QPushButton ("Button D");
    QPushButton * buttonE   = new QPushButton ("Button E");
    QVBoxLayout * layoutTop = new QVBoxLayout ();
    QVBoxLayout * layoutGroupI  = new QVBoxLayout ();
    QVBoxLayout * layoutGroupII = new QVBoxLayout ();
    groupI->setLayout  (layoutGroupI);
    groupII->setLayout (layoutGroupII);
    layoutGroupI->addWidget (buttonA);
    layoutGroupI->addWidget (buttonB);
    layoutGroupI->addWidget (buttonC);
    layoutGroupII->addWidget (buttonD);
    layoutGroupII->addWidget (buttonE);
    layoutTop->addWidget (checkFixed);
    layoutTop->addWidget (groupI);
    layoutTop->addWidget (groupII);
    layoutTop->setSizeConstraint (QLayout::SetMaximumSize);
    setLayout (layoutTop);

    animation = new QPropertyAnimation (nullptr, "geometry", this);
}

void BarWidget::Show (const QRectF & end, const bool isAnimated)
{
    if (!animation->targetObject () ) {
        if (graphicsProxyWidget () ) {
            animation->setTargetObject (graphicsProxyWidget () );
        }
    }

    if (animation->targetObject () && isAnimated) {
        animation->setStartValue (geometry () );
        animation->setEndValue (end);
        animation->setDuration (250);
        animation->start ();
    }

    if (!isAnimated && graphicsProxyWidget () ) {
        graphicsProxyWidget ()->setGeometry (end);
    }

    isHidden = false;
}

void BarWidget::Hide (const QRectF & end, const bool isAnimated)
{
    if (!animation->targetObject () ) {
        if (graphicsProxyWidget () ) {
            animation->setTargetObject (graphicsProxyWidget () );
        }
    }

    if (animation->targetObject () && isAnimated) {
        animation->setStartValue (geometry () );
        animation->setEndValue (end);
        animation->setDuration (250);
        animation->start ();
    }

    if (!isAnimated && graphicsProxyWidget () ) {
        graphicsProxyWidget ()->setGeometry (end);
    }

    isHidden = true;
}
