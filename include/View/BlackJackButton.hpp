#pragma once
#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QEasingCurve>

class BlackjackButton : public QPushButton
{
    Q_OBJECT

public:
    explicit BlackjackButton(const QString &text = {}, QWidget *parent = nullptr)
        : QPushButton(text, parent)
    {
        setCursor(Qt::PointingHandCursor);
        // setMinimumSize(140, 44);
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    }
};
