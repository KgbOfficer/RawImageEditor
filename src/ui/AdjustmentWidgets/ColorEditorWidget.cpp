#include "ColorEditorWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>

ColorEditorWidget::ColorEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Color Editor");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    // Colour swatch selector ──────────────────────────────────────────────────
    struct Swatch { QString label; QColor color; };
    const QVector<Swatch> swatches = {
        {"R",  QColor(210, 50,  50)},
        {"Or", QColor(220,130,  30)},
        {"Y",  QColor(200,190,  20)},
        {"G",  QColor( 40,160,  40)},
        {"Aq", QColor( 30,170, 170)},
        {"B",  QColor( 50, 90, 210)},
        {"Pu", QColor(140, 50, 180)},
        {"Mg", QColor(200, 50, 120)},
    };

    auto *swatchRow  = new QHBoxLayout;
    auto *stack      = new QStackedWidget;

    for (int i = 0; i < swatches.size(); ++i) {
        const auto &sw = swatches[i];

        // Button
        auto *btn = new QPushButton(sw.label);
        btn->setFixedSize(24, 22);
        btn->setCheckable(true);
        btn->setChecked(i == 0);
        QString bg = sw.color.name();
        QString fg = sw.color.lightness() > 140 ? "#000" : "#fff";
        btn->setStyleSheet(
            QString("QPushButton{background:%1;color:%2;border:none;border-radius:2px;font-size:9px;}"
                    "QPushButton:checked{border:2px solid #fff;}").arg(bg, fg));
        swatchRow->addWidget(btn);

        // Sliders page
        auto *page   = new QWidget;
        auto *pLayout = new QVBoxLayout(page);
        pLayout->setSpacing(2);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pLayout->addWidget(new SliderRow("Hue",        -180, 180,  0));
        pLayout->addWidget(new SliderRow("Saturation", -100, 100,  0));
        pLayout->addWidget(new SliderRow("Lightness",  -100, 100,  0));
        stack->addWidget(page);

        int idx = i;
        connect(btn, &QPushButton::clicked, stack, [stack, idx]() {
            stack->setCurrentIndex(idx);
        });
    }

    layout->addLayout(swatchRow);
    layout->addWidget(stack);

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
