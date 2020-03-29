
#include "imageshowview.h"

#include <algorithm>

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
    m_ImageLeft = m_ImageLeft.convertToFormat(QImage::Format_RGB888);

    m_ImageRight.load(strRight);
    m_ImageRight = m_ImageRight.convertToFormat(QImage::Format_RGB888);

    return true;
}

void ImageShowView::ChangeModel(ImageShowType showType)
{
    m_showType = showType;
    CreateRedGreenImage();
    update();
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
// use left image as base
void ImageShowView::CreateRedGreenImage()
{
    if (m_showType != RED_GREEN)
        return;

    // left image
    int nRows_L = m_ImageLeft.height();
    int nCols_L = m_ImageLeft.width();
    int nChannel_L = m_ImageLeft.byteCount();

    // right image
    int nRows_R = m_ImageRight.height();
    int nCols_R = m_ImageRight.width();
    int nChannel_R = m_ImageRight.byteCount();

    int nDisparity = int(m_disparity + 0.5);

    int minCols_R = -nDisparity;
    int maxCols_R = nCols_R - nDisparity;

    int minCols_L = std::min(0, minCols_R);
    int maxCols_L = std::max(nCols_L, maxCols_R);

    int nRows_LR = nRows_L;
    int nCols_LR = maxCols_L - minCols_L;
    int nChannel_LR = 3;

    unsigned char * pImage = new unsigned char[nRows_LR * nCols_LR * nChannel_LR];
    memset(pImage, 0, sizeof(unsigned char) * nRows_LR * nCols_LR * nChannel_LR);

    // for each pixel
    unsigned char LeftPix[3] = { 0 };
    unsigned char RightPix[3] = { 0 };

    // red-green
    for (int i = 0; i < nRows_LR; ++i){
        // get the data from images
        unsigned char * pImgL = m_ImageLeft.scanLine(i);
        unsigned char * pImgR = m_ImageRight.scanLine(i);
        for (int j = minCols_L; j < maxCols_L; ++j){
            // left Image
            if (j < 0 || j >= nCols_L){
                memset(LeftPix, 0, sizeof(unsigned char) * 3);
            }
            else{
                //LeftPix[0] = pImgL[(i * nCols_L + j) * 3];
                memcpy(LeftPix, pImgL + j * 3, sizeof(unsigned char) * 3);
            }

            // right image
            int nIndex_R = j - nDisparity;
            if (nIndex_R < 0 || nIndex_R >= nCols_R){
                memset(RightPix, 0, sizeof(unsigned char) * 3);
            }
            else{
                memcpy(RightPix, pImgR + nIndex_R * 3, sizeof(unsigned char) * 3);
            }

            // fusion
            int nIndex = j - minCols_L;
            pImage[(i * nCols_LR + nIndex) * 3] = RightPix[0];
            pImage[(i * nCols_LR + nIndex) * 3 + 1] = RightPix[1];
            pImage[(i * nCols_LR + nIndex) * 3 + 2] = LeftPix[2];
        }
    }

    m_ImageRedGreen = QImage(nCols_LR, nRows_LR, QImage::Format_RGB888);
    for (int i = 0; i < nRows_LR; ++i){
        memcpy(m_ImageRedGreen.scanLine(i), pImage + i * nCols_LR * 3, sizeof(unsigned char) * nCols_LR * 3);
    }

    delete []pImage;        pImage = NULL;
}
