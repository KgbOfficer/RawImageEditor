#include "HDRWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

HDRWidget::HDRWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("HDR / Tone");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);

    layout->addWidget(new SliderRow("Highlights", -100, 100, 0));
    layout->addWidget(new SliderRow("Shadows",    -100, 100, 0));
    layout->addWidget(new SliderRow("Whites",     -100, 100, 0));
    layout->addWidget(new SliderRow("Blacks",     -100, 100, 0));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
