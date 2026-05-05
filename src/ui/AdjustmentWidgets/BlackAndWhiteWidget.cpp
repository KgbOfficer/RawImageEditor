#include "BlackAndWhiteWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

BlackAndWhiteWidget::BlackAndWhiteWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Black & White");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);

    // Auto-mix button
    auto *autoBtn = new QPushButton("Auto Mix");
    autoBtn->setFixedHeight(22);
    layout->addWidget(autoBtn);

    // Per-hue luminance mix sliders
    layout->addWidget(new SliderRow("Reds",     -200, 200, 40));
    layout->addWidget(new SliderRow("Oranges",  -200, 200, 33));
    layout->addWidget(new SliderRow("Yellows",  -200, 200, 0));
    layout->addWidget(new SliderRow("Greens",   -200, 200, 0));
    layout->addWidget(new SliderRow("Aquas",    -200, 200, 0));
    layout->addWidget(new SliderRow("Blues",    -200, 200, 0));
    layout->addWidget(new SliderRow("Purples",  -200, 200, 0));
    layout->addWidget(new SliderRow("Magentas", -200, 200, 0));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
