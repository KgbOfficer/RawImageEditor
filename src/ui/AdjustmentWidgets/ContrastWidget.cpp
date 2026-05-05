#include "ContrastWidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>

ContrastWidget::ContrastWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group = new QGroupBox("Contrast");
    auto *layout = new QVBoxLayout(group);
    auto *slider = new QSlider(Qt::Horizontal);
    slider->setRange(-100, 100);
    slider->setValue(0);
    auto *label = new QLabel("0");
    connect(slider, &QSlider::valueChanged, label,
            [label](int v) { label->setText(QString::number(v)); });
    layout->addWidget(slider);
    layout->addWidget(label);
    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0,0,0,0);
    outer->addWidget(group);
}