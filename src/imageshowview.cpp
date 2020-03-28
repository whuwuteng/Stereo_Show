
#include "imageshowview.h"

#include <QPainter>

ImageShowView::ImageShowView( QWidget* parent/* = 0 */) : QWidget(parent)
{
    m_showType = LEFT_IMAGE;
    m_disparity = 0.0;
}

ImageShowView::~ImageShowView()
{

}

bool ImageShowView::LoadStereoFile(QString strLeft, QString strRight)
{
    m_ImageLeft.load(strLeft);
    m_ImageRight.load(strRight);

    return true;
}

void ImageShowView::paintEvent(QPaintEvent * event)
{
    if (m_showType == LEFT_IMAGE){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), m_ImageLeft);
    }
    else if (m_showType == RIGHT_IMAGE){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), m_ImageRight);
    }
    else if (m_showType == RED_GREEN){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), m_ImageRedGreen);
    }
}

// only after ctrl+wheel, this will change
void ImageShowView::CreateRedGreenImage()
{
    if (m_showType == RED_GREEN){

    }
}
