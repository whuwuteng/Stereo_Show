
#include "imageshowview.h"

#include <QPainter>

ImageShowView::ImageShowView( QWidget* parent/* = 0 */) : QWidget(parent)
{

}

ImageShowView::~ImageShowView()
{

}

bool ImageShowView::LoadStereoFile(QString strLeft, QString strRight)
{

    return true;
}

void ImageShowView::paintEvent(QPaintEvent * event)
{
    QImage img;
    img.load("/home/tengwu/mountdisk/L.jpg");

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), img);
}

