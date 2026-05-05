#pragma once
#include <QWidget>

class QLabel;

class LevelsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LevelsWidget(QWidget *parent = nullptr);

private:
    // Gradient bar showing input/output ramps
    QLabel *m_inputBar  = nullptr;
    QLabel *m_outputBar = nullptr;

    void updateGradientBar(QLabel *bar, int black, int white, bool isOutput);
};
