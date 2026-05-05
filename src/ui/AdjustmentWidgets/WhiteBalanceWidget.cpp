#include "WhiteBalanceWidget.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

WhiteBalanceWidget::WhiteBalanceWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group = new QGroupBox("White Balance");
    auto *layout = new QVBoxLayout(group);

    auto *kelvinSlider = new QSlider(Qt::Horizontal);
    kelvinSlider->setRange(2000, 50000);
    kelvinSlider->setValue(6500);
    auto *kLabel = new QLabel("6500");

    auto *tintSlider = new QSlider(Qt::Horizontal);
    tintSlider->setRange(-100, 100);
    tintSlider->setValue(0);
    auto *tLabel = new QLabel("0");

    connect(kelvinSlider, &QSlider::valueChanged, kLabel,
            [kLabel](int v) { kLabel->setText(QString::number(v) + " K"); });
    connect(tintSlider, &QSlider::valueChanged, tLabel,
            [tLabel](int v) { tLabel->setText(QString::number(v)); });

    layout->addWidget(new QLabel("Kelvin"));
    layout->addWidget(kelvinSlider);
    layout->addWidget(kLabel);
    layout->addWidget(new QLabel("Tint"));
    layout->addWidget(tintSlider);
    layout->addWidget(tLabel);

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0,0,0,0);
    outer->addWidget(group);
}