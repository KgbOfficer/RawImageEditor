#include "RightPanel.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

// Adjustment widgets
#include "ui/AdjustmentWidgets/WhiteBalanceWidget.h"
#include "ui/AdjustmentWidgets/ExposureWidget.h"
#include "ui/AdjustmentWidgets/ContrastWidget.h"
#include "ui/AdjustmentWidgets/BrightnessWidget.h"
#include "ui/AdjustmentWidgets/SaturationWidget.h"
#include "ui/AdjustmentWidgets/HDRWidget.h"
#include "ui/AdjustmentWidgets/LevelsWidget.h"
#include "ui/AdjustmentWidgets/CurveWidget.h"
#include "ui/AdjustmentWidgets/ColorEditorWidget.h"
#include "ui/AdjustmentWidgets/ColorBalanceWidget.h"
#include "ui/AdjustmentWidgets/BlackAndWhiteWidget.h"
#include "ui/AdjustmentWidgets/DehazeWidget.h"
#include "ui/AdjustmentWidgets/ClarityWidget.h"
#include "ui/AdjustmentWidgets/VignetteWidget.h"

RightPanel::RightPanel(QWidget *parent)
    : QScrollArea(parent)
{
    setWidgetResizable(true);
    auto *container = new QWidget;
    auto *layout = new QVBoxLayout(container);

    // Histogram placeholder
    QGroupBox *histogramGroup = new QGroupBox("Histogram");
    histogramGroup->setLayout(new QVBoxLayout);
    histogramGroup->layout()->addWidget(new QLabel("Histogram (placeholder)"));
    layout->addWidget(histogramGroup);

    // All adjustment widgets
    layout->addWidget(new WhiteBalanceWidget);
    layout->addWidget(new ExposureWidget);
    layout->addWidget(new ContrastWidget);
    layout->addWidget(new BrightnessWidget);
    layout->addWidget(new SaturationWidget);
    layout->addWidget(new HDRWidget);
    layout->addWidget(new LevelsWidget);
    layout->addWidget(new CurveWidget);
    layout->addWidget(new ColorEditorWidget);
    layout->addWidget(new ColorBalanceWidget);
    layout->addWidget(new BlackAndWhiteWidget);
    layout->addWidget(new DehazeWidget);
    layout->addWidget(new ClarityWidget);
    layout->addWidget(new VignetteWidget);

    layout->addStretch();
    setWidget(container);
}