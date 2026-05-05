#include "LevelsWidget.h"
#include "SliderRow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <QLinearGradient>
#include <QPixmap>

// ─── tiny helper: draws a black→white ramp cropped to [black,white] ──────────
void LevelsWidget::updateGradientBar(QLabel *bar, int black, int white, bool /*isOutput*/)
{
    int w = bar->width() > 0 ? bar->width() : 200;
    int h = 10;
    QPixmap px(w, h);
    QPainter p(&px);
    QLinearGradient grad(0, 0, w, 0);
    grad.setColorAt(0, Qt::black);
    grad.setColorAt(1, Qt::white);
    p.fillRect(0, 0, w, h, grad);
    // Marker ticks
    p.setPen(QColor(255,165,0));
    int bx = black * w / 255;
    int wx = white * w / 255;
    p.drawLine(bx, 0, bx, h);
    p.drawLine(wx, 0, wx, h);
    bar->setPixmap(px);
}

LevelsWidget::LevelsWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *group  = new QGroupBox("Levels");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    // ── Input ────────────────────────────────────────────────────────────────
    layout->addWidget(new QLabel("Input"));
    m_inputBar = new QLabel;
    m_inputBar->setFixedHeight(10);
    m_inputBar->setScaledContents(true);
    layout->addWidget(m_inputBar);

    auto *inBlack = new SliderRow("Black Point", 0, 253, 0);
    auto *inGamma = new SliderRow("Midtones",    1, 999, 100);   // ×0.01 logically
    auto *inWhite = new SliderRow("White Point", 2, 255, 255);

    layout->addWidget(inBlack);
    layout->addWidget(inGamma);
    layout->addWidget(inWhite);

    // ── Output ───────────────────────────────────────────────────────────────
    layout->addWidget(new QLabel("Output"));
    m_outputBar = new QLabel;
    m_outputBar->setFixedHeight(10);
    m_outputBar->setScaledContents(true);
    layout->addWidget(m_outputBar);

    auto *outBlack = new SliderRow("Black", 0, 254, 0);
    auto *outWhite = new SliderRow("White", 1, 255, 255);

    layout->addWidget(outBlack);
    layout->addWidget(outWhite);

    // Update bars when sliders move
    auto refreshInput  = [=](int) {
        updateGradientBar(m_inputBar,  inBlack->value(),  inWhite->value(),  false); };
    auto refreshOutput = [=](int) {
        updateGradientBar(m_outputBar, outBlack->value(), outWhite->value(), true);  };

    connect(inBlack,  &SliderRow::valueChanged, this, refreshInput);
    connect(inWhite,  &SliderRow::valueChanged, this, refreshInput);
    connect(outBlack, &SliderRow::valueChanged, this, refreshOutput);
    connect(outWhite, &SliderRow::valueChanged, this, refreshOutput);

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
