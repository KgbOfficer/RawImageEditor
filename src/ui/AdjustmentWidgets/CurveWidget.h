#pragma once
#include <QWidget>
#include <QVector>
#include <QPointF>

// ─────────────────────────────────────────────────────────────────────────────
// CurveCanvas – the interactive spline canvas embedded inside CurveWidget
// ─────────────────────────────────────────────────────────────────────────────
class CurveCanvas : public QWidget
{
    Q_OBJECT
public:
    enum Channel { ALL = 0, RED, GREEN, BLUE };

    explicit CurveCanvas(QWidget *parent = nullptr);

    void setChannel(Channel ch);
    void reset();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private:
    struct Curve {
        QVector<QPointF> pts;      // normalised 0-1 space
        QColor           color;
    };

    QVector<Curve> m_curves;   // index matches Channel enum
    int            m_channel = 0;
    int            m_drag    = -1; // index of dragged point, or -1

    QPointF  toCanvas(QPointF norm)  const;
    QPointF  toNorm(QPointF canvas)  const;
    int      hitTest(QPointF canvas) const;
    void     drawCurve(QPainter &p, const Curve &c);
    QColor   channelColor(int ch) const;
};

// ─────────────────────────────────────────────────────────────────────────────
// CurveWidget – group-box wrapper that holds channel buttons + the canvas
// ─────────────────────────────────────────────────────────────────────────────
class CurveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CurveWidget(QWidget *parent = nullptr);
};
