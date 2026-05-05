#include "BrightnessWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

BrightnessWidget::BrightnessWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Brightness");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);

    layout->addWidget(new SliderRow("Brightness", -100, 100, 0));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
