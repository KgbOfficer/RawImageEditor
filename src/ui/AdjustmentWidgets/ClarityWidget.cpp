#include "ClarityWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

ClarityWidget::ClarityWidget(QWidget *parent) : QWidget(parent)
{
    auto *group  = new QGroupBox("Clarity & Texture");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(2);
    layout->addWidget(new SliderRow("Clarity", -100, 100, 0));
    layout->addWidget(new SliderRow("Texture", -100, 100, 0));
    layout->addWidget(new SliderRow("Sharpness",  0, 100, 0));
    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
