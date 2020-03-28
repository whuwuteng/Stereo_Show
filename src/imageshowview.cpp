
#include "imageshowview.h"

#include <QPainter>

ImageShowView::ImageShowView( QWidget* parent/* = 0 */) : QWidget(parent)
{

}

ImageShowView::~ImageShowView()
{

}

void ImageShowView::paintEvent(QPaintEvent * event)
{
    QImage img;
    img.load("/home/tengwu/mountdisk/L.jpg");

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), img);
}

void ImageShowView::mouseMoveEvent(QMouseEvent *event)
{

}

// the message also transform to qscrollview
// should over write qscrollview
void ImageShowView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier))
    {
    QMessageBox::about(this, tr("Stereo Image Viewer"),
            tr("<b> image event </b>"));
    }
    else{
        QWidget::wheelEvent(event);
    }
}
