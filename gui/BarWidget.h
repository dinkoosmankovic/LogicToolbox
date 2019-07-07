#ifndef QPA_BAR_WIDGET_H
#define QPA_BAR_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPropertyAnimation>

class BarWidget : public QWidget
{
Q_OBJECT
public:
    explicit BarWidget      (QWidget * parent = nullptr);
    ~BarWidget              () override = default;
    void Show               (const QRectF &, const bool isAnimated = false);
    void Hide               (const QRectF &, const bool isAnimated = false);
    bool IsHidden           () const {return isHidden;};
    bool IsFixed            () const {return checkFixed->isChecked ();};
    int  FullWidth          () const {return 150;};
private:
    QCheckBox             * checkFixed;
    QPropertyAnimation    * animation;
    bool                    isHidden {true};
};

#endif//QPA_BAR_WIDGET_H
