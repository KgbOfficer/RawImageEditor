// ImageView.cpp
#include "ImageView.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>

ImageView::ImageView(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void ImageView::setImage(const QPixmap &pixmap)
{
    m_image = pixmap;
    m_zoomFactor = 1.0;
    m_offset = QPoint(0, 0);
    update();
}

void ImageView::fitToView()
{
    if (m_image.isNull()) return;
    double wScale = double(width()) / m_image.width();
    double hScale = double(height()) / m_image.height();
    m_zoomFactor = qMin(wScale, hScale);
    m_offset = QPoint(0, 0);
    update();
}

void ImageView::zoomIn()
{
    m_zoomFactor *= 1.2;
    m_zoomFactor = qMin(m_zoomFactor, 10.0);
    update();
}

void ImageView::zoomOut()
{
    m_zoomFactor /= 1.2;
    m_zoomFactor = qMax(m_zoomFactor, 0.05);
    update();
}

void ImageView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::darkGray);

    if (m_image.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "No Image");
        return;
    }

    QSizeF scaledSize = m_image.size() * m_zoomFactor;
    QPointF topLeft = QPointF((width() - scaledSize.width()) / 2.0,
                              (height() - scaledSize.height()) / 2.0)
                      + m_offset;

    painter.drawPixmap(QRectF(topLeft, scaledSize), m_image);
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    double oldZoom = m_zoomFactor;
    if (event->angleDelta().y() > 0)
        m_zoomFactor *= 1.1;
    else
        m_zoomFactor /= 1.1;
    m_zoomFactor = qBound(0.05, m_zoomFactor, 10.0);

    QPointF mousePos = event->position();
    QPointF imagePos = (mousePos - QPointF(width()/2.0, height()/2.0) - m_offset) / oldZoom;
    m_offset = mousePos - QPointF(width()/2.0, height()/2.0) - imagePos * m_zoomFactor;

    update();
    event->accept();
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_offset += delta;
        m_lastMousePos = event->pos();
        update();
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        setCursor(Qt::ArrowCursor);
    }
}