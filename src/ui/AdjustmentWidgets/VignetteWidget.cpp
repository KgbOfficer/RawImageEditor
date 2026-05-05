#include "VignetteWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

VignetteWidget::VignetteWidget(QWidget *parent) : QWidget(parent)
{
    auto *group  = new QGroupBox("Vignette");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);

    layout->addWidget(new SliderRow("Amount",     -100, 100, 0));
    layout->addWidget(new SliderRow("Midpoint",      0, 100, 50));
    layout->addWidget(new SliderRow("Roundness",  -100, 100, 0));
    layout->addWidget(new SliderRow("Feather",       0, 100, 50));
    layout->addWidget(new SliderRow("Highlights",    0, 100, 0));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
