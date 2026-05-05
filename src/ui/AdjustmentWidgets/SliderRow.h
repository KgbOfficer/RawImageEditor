#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

// ─────────────────────────────────────────────────────────────────────────────
// SliderRow – reusable label + slider + value label in one line.
// Used by every adjustment widget so they all share the same look.
// ─────────────────────────────────────────────────────────────────────────────
class SliderRow : public QWidget
{
    Q_OBJECT
public:
    explicit SliderRow(const QString &name, int min, int max, int defaultVal,
                       QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto *hbox = new QHBoxLayout(this);
        hbox->setContentsMargins(4, 2, 4, 2);
        hbox->setSpacing(6);

        m_nameLabel = new QLabel(name);
        m_nameLabel->setFixedWidth(100);
        m_nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_nameLabel->setObjectName("sliderName");

        m_slider = new QSlider(Qt::Horizontal);
        m_slider->setRange(min, max);
        m_slider->setValue(defaultVal);

        m_valueLabel = new QLabel(QString::number(defaultVal));
        m_valueLabel->setFixedWidth(42);
        m_valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_valueLabel->setObjectName("sliderValue");

        connect(m_slider, &QSlider::valueChanged, this, [this](int v) {
            m_valueLabel->setText(QString::number(v));
            emit valueChanged(v);
        });

        hbox->addWidget(m_nameLabel);
        hbox->addWidget(m_slider, 1);
        hbox->addWidget(m_valueLabel);
    }

    int  value()    const { return m_slider->value(); }
    void setValue(int v)  { m_slider->setValue(v); }
    void reset()          { m_slider->setValue(m_slider->minimum() == -m_slider->maximum()
                                                ? 0 : m_slider->minimum()); }

signals:
    void valueChanged(int value);

private:
    QLabel  *m_nameLabel;
    QSlider *m_slider;
    QLabel  *m_valueLabel;
};
