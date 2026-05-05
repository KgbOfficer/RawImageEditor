// ImageView.h
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QPixmap>

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);
    void setImage(const QPixmap &pixmap);
    void fitToView();
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap m_image;
    double m_zoomFactor = 1.0;
    QPointF m_offset;
    bool m_dragging = false;
    QPoint m_lastMousePos;
};

#endif