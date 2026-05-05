#include "SaturationWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

SaturationWidget::SaturationWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Saturation");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);

    layout->addWidget(new SliderRow("Saturation", -100, 100, 0));
    layout->addWidget(new SliderRow("Vibrance",   -100, 100, 0));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
