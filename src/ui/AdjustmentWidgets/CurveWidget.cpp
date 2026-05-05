#include "CurveWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLinearGradient>
#include <QtMath>
#include <algorithm>

// ─────────────────────────────────────── constants ───────────────────────────
static constexpr int   PAD      = 12;
static constexpr int   CANVAS_W = 200;
static constexpr int   CANVAS_H = 200;
static constexpr double HIT_R   = 8.0;

// ─────────────────────────────────────── CurveCanvas ─────────────────────────

CurveCanvas::CurveCanvas(QWidget *parent) : QWidget(parent)
{
    setFixedSize(CANVAS_W + 2*PAD, CANVAS_H + 2*PAD);
    setCursor(Qt::CrossCursor);

    // Initialise one default diagonal per channel
    QVector<QColor> cols = { QColor(220,220,220), QColor(220,60,60),
                              QColor(60,200,60),   QColor(80,120,255) };
    for (int i = 0; i < 4; ++i) {
        Curve c;
        c.color = cols[i];
        c.pts   = { {0,0}, {0.25,0.25}, {0.5,0.5}, {0.75,0.75}, {1,1} };
        m_curves.append(c);
    }
}

void CurveCanvas::setChannel(Channel ch) { m_channel = ch; update(); }

void CurveCanvas::reset()
{
    auto &c = m_curves[m_channel];
    c.pts = { {0,0}, {0.25,0.25}, {0.5,0.5}, {0.75,0.75}, {1,1} };
    update();
}

QPointF CurveCanvas::toCanvas(QPointF n) const
{
    return { PAD + n.x() * CANVAS_W,
             PAD + (1.0 - n.y()) * CANVAS_H };
}

QPointF CurveCanvas::toNorm(QPointF cv) const
{
    return { (cv.x() - PAD) / CANVAS_W,
             1.0 - (cv.y() - PAD) / CANVAS_H };
}

int CurveCanvas::hitTest(QPointF cv) const
{
    const auto &pts = m_curves[m_channel].pts;
    for (int i = 0; i < pts.size(); ++i) {
        QPointF d = toCanvas(pts[i]) - cv;
        if (d.x()*d.x() + d.y()*d.y() <= HIT_R*HIT_R)
            return i;
    }
    return -1;
}

// Catmull-Rom: draw a smooth curve through the control points
void CurveCanvas::drawCurve(QPainter &p, const Curve &c)
{
    const auto &pts = c.pts;
    if (pts.size() < 2) return;

    QPen pen(c.color, 1.5);
    p.setPen(pen);

    QVector<QPointF> cv;
    cv.reserve(pts.size());
    for (auto &np : pts) cv.append(toCanvas(np));

    QPainterPath path;
    path.moveTo(cv.first());

    for (int i = 0; i < cv.size() - 1; ++i) {
        QPointF p0 = cv[qMax(i-1, 0)];
        QPointF p1 = cv[i];
        QPointF p2 = cv[i+1];
        QPointF p3 = cv[qMin(i+2, (int)cv.size()-1)];

        // Catmull-Rom → cubic Bézier conversion
        QPointF cp1 = p1 + (p2 - p0) / 6.0;
        QPointF cp2 = p2 - (p3 - p1) / 6.0;
        path.cubicTo(cp1, cp2, p2);
    }
    p.drawPath(path);
}

void CurveCanvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Background
    p.fillRect(rect(), QColor(28, 28, 28));

    // Curve area background
    QRectF canvas(PAD, PAD, CANVAS_W, CANVAS_H);
    p.fillRect(canvas, QColor(38, 38, 38));

    // Grid lines
    p.setPen(QColor(60, 60, 60));
    for (int i = 1; i < 4; ++i) {
        double x = PAD + i * CANVAS_W / 4.0;
        double y = PAD + i * CANVAS_H / 4.0;
        p.drawLine(QPointF(x, PAD), QPointF(x, PAD + CANVAS_H));
        p.drawLine(QPointF(PAD, y), QPointF(PAD + CANVAS_W, y));
    }

    // Diagonal reference
    p.setPen(QPen(QColor(70, 70, 70), 1, Qt::DashLine));
    p.drawLine(QPointF(PAD, PAD + CANVAS_H), QPointF(PAD + CANVAS_W, PAD));

    // Border
    p.setPen(QColor(80, 80, 80));
    p.drawRect(canvas.adjusted(0, 0, -1, -1));

    // Draw inactive channels faintly
    for (int i = 0; i < 4; ++i) {
        if (i == m_channel) continue;
        QPen fp(m_curves[i].color.darker(300), 1);
        p.setPen(fp);
        drawCurve(p, m_curves[i]);
    }

    // Active channel
    drawCurve(p, m_curves[m_channel]);

    // Control points
    const auto &pts = m_curves[m_channel].pts;
    for (int i = 0; i < pts.size(); ++i) {
        QPointF cv = toCanvas(pts[i]);
        p.setPen(QPen(m_curves[m_channel].color, 1.5));
        p.setBrush(i == m_drag ? m_curves[m_channel].color : QColor(45, 45, 45));
        p.drawEllipse(cv, 4.5, 4.5);
    }
}

void CurveCanvas::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_drag = hitTest(e->pos());
        if (m_drag < 0) {
            // Add new point
            QPointF n = toNorm(e->pos());
            n.setX(qBound(0.0, n.x(), 1.0));
            n.setY(qBound(0.0, n.y(), 1.0));
            auto &pts = m_curves[m_channel].pts;
            pts.append(n);
            std::sort(pts.begin(), pts.end(),
                      [](const QPointF &a, const QPointF &b){ return a.x() < b.x(); });
            m_drag = pts.indexOf(n);
        }
        update();
    }
}

void CurveCanvas::mouseMoveEvent(QMouseEvent *e)
{
    if (m_drag < 0) return;
    auto &pts = m_curves[m_channel].pts;
    QPointF n = toNorm(e->pos());
    n.setX(qBound(0.0, n.x(), 1.0));
    n.setY(qBound(0.0, n.y(), 1.0));
    // Keep endpoints locked to x=0 and x=1
    if (m_drag == 0)           n.setX(0.0);
    if (m_drag == pts.size()-1) n.setX(1.0);
    pts[m_drag] = n;
    update();
}

void CurveCanvas::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) m_drag = -1;
}

void CurveCanvas::mouseDoubleClickEvent(QMouseEvent *e)
{
    // Double-click removes a point (not the endpoints)
    int idx = hitTest(e->pos());
    auto &pts = m_curves[m_channel].pts;
    if (idx > 0 && idx < pts.size() - 1) {
        pts.remove(idx);
        m_drag = -1;
        update();
    }
}

// ─────────────────────────────────────── CurveWidget ─────────────────────────

CurveWidget::CurveWidget(QWidget *parent) : QWidget(parent)
{
    auto *group  = new QGroupBox("Curves");
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(4);

    // Channel selector buttons
    auto *btnRow = new QHBoxLayout;
    const QStringList labels = { "ALL", "R", "G", "B" };
    const QStringList ids    = { "btnAll", "btnR", "btnG", "btnB" };

    auto *canvas = new CurveCanvas;

    for (int i = 0; i < 4; ++i) {
        auto *btn = new QPushButton(labels[i]);
        btn->setObjectName(ids[i]);
        btn->setCheckable(true);
        btn->setFixedHeight(20);
        btn->setChecked(i == 0);
        int ch = i; // capture
        connect(btn, &QPushButton::clicked, canvas, [canvas, ch]() {
            canvas->setChannel(static_cast<CurveCanvas::Channel>(ch));
        });
        btnRow->addWidget(btn);
    }
    layout->addLayout(btnRow);
    layout->addWidget(canvas, 0, Qt::AlignHCenter);

    auto *resetBtn = new QPushButton("Reset");
    resetBtn->setFixedHeight(20);
    connect(resetBtn, &QPushButton::clicked, canvas, &CurveCanvas::reset);
    layout->addWidget(resetBtn);

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(group);
}
