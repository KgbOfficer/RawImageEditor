#include "ColorBalanceWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QGroupBox>

static QGroupBox *makeToneGroup(const QString &name)
{
    auto *g = new QGroupBox(name);
    auto *l = new QVBoxLayout(g);
    l->setSpacing(2);
    l->addWidget(new SliderRow("Cyan – Red",     -100, 100, 0));
    l->addWidget(new SliderRow("Magenta – Green",-100, 100, 0));
    l->addWidget(new SliderRow("Yellow – Blue",  -100, 100, 0));
    return g;
}

ColorBalanceWidget::ColorBalanceWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Color Balance");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    layout->addWidget(makeToneGroup("Shadows"));
    layout->addWidget(makeToneGroup("Midtones"));
    layout->addWidget(makeToneGroup("Highlights"));

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
