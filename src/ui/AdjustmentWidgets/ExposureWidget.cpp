#include "ExposureWidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>

ExposureWidget::ExposureWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group = new QGroupBox("Exposure");
    auto *layout = new QVBoxLayout(group);

    auto *slider = new QSlider(Qt::Horizontal);
    slider->setRange(-500, 500);
    slider->setValue(0);
    auto *label = new QLabel("0");

    connect(slider, &QSlider::valueChanged, label,
            [label](int v) { label->setText(QString::number(v)); });

    layout->addWidget(slider);
    layout->addWidget(label);

    auto *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0,0,0,0);
    outerLayout->addWidget(group);
}