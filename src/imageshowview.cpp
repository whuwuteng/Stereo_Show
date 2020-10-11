
#include "imageshowview.h"

#include <iostream>
#include <algorithm>

#include <QPainter>

ImageShowView::ImageShowView( QWidget* parent/* = 0 */) : QWidget(parent)
{
    m_showType = LEFT_IMAGE;
    m_disparity = 0.0;

    m_nMaxDisp = 0;
    m_nMinDisp = 0;

    m_scale = 1.0;
}

ImageShowView::~ImageShowView()
{

}

bool ImageShowView::LoadStereoFile(QString strLeft, QString strRight)
{
    if (strLeft.isEmpty() || strRight.isEmpty()){
        return false;
    }
    if (! m_ImageLeft.load(strLeft)){
        QString msg = QString("Can not open: ") + strLeft;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return false;
    }
/*
    QImage::Format lfmt = m_ImageLeft.format();
    printf("left image foramt: %d\n", lfmt);
    if (lfmt != QImage::Format_RGB888 && lfmt != QImage::Format_Grayscale8){
        m_ImageLeft = m_ImageLeft.convertToFormat(QImage::Format_RGB888);
    }
*/
    // if image is too large, out of mememory
    /* m_ImageLeft = m_ImageLeft.convertToFormat(QImage::Format_RGB888);
    if (m_ImageLeft.isNull()){
        QString msg = QString("Can not convert: ") + strLeft;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return false;
    }*/

    if (! m_ImageRight.load(strRight)){
        QString msg = QString("Can not open: ") + strRight;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return false;
    }
/*
    QImage::Format rfmt = m_ImageLeft.format();
    printf("right image foramt: %d\n", rfmt);
    if (rfmt != QImage::Format_RGB888 && rfmt != QImage::Format_Grayscale8){
        m_ImageRight = m_ImageRight.convertToFormat(QImage::Format_RGB888);
    }
*/
    /* m_ImageRight = m_ImageRight.convertToFormat(QImage::Format_RGB888);
    if (m_ImageRight.isNull()){
        QString msg = QString("Can not convert: ") + strRight;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return false;
    }*/

    m_strLeftImg = strLeft;
    m_strRightImg = strRight;

    m_nMaxDisp = m_ImageLeft.width();
    m_nMinDisp = -m_ImageRight.width();

    if (m_showType == RED_GREEN){
        CreateRedGreenImage();
    }
    SetWidgetSize();
    return true;
}

void ImageShowView::ChangeModel(ImageShowType showType)
{
    m_showType = showType;
    CreateRedGreenImage();
    SetWidgetSize();
    update();
}

QImage ImageShowView::ImageToZoom(QImage & srcImg)
{
    int nCols = int(srcImg.width() * m_scale + 0.5);
    int nRows = int(srcImg.height() * m_scale + 0.5);
    return srcImg.scaled(nCols, nRows);
}

void ImageShowView::paintEvent(QPaintEvent * event)
{
    if (m_showType == LEFT_IMAGE){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), ImageToZoom(m_ImageLeft));
    }
    else if (m_showType == RIGHT_IMAGE){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), ImageToZoom(m_ImageRight));
    }
    else if (m_showType == RED_GREEN){
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), ImageToZoom(m_ImageRedGreen));
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
    int nChannel_L = m_ImageLeft.bitPlaneCount();

    //std::cout << "image channel: " << nChannel_L << std::endl;
    if (nChannel_L != 8 && nChannel_L != 24){
        QString msg = QString("Only support gray and RGB: ") + m_strLeftImg;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return;
    }

    // right image
    int nRows_R = m_ImageRight.height();
    int nCols_R = m_ImageRight.width();
    int nChannel_R = m_ImageRight.bitPlaneCount();

    if (nChannel_R != 8 && nChannel_R != 24){
        QString msg = QString("Only support gray and RGB: ") + m_strRightImg;
        QMessageBox::about(this, tr("Stereo Image Viewer"), msg);
        return;
    }

    int nDisparity = int(m_disparity + 0.5);

    int minCols_R = nDisparity;
    int maxCols_R = nCols_R + nDisparity;

    int minCols_L = std::min(0, minCols_R);
    int maxCols_L = std::max(nCols_L, maxCols_R);

    int nRows_LR = nRows_L;
    int nCols_LR = maxCols_L - minCols_L;
    int nChannel_LR = 3;

    unsigned char * pImage = new unsigned char[nRows_LR * nCols_LR * nChannel_LR];
    memset(pImage, 0, sizeof(unsigned char) * nRows_LR * nCols_LR * nChannel_LR);
    if (pImage == NULL){
        printf("out of memeory\n");
        return;
    }

    // attention: qimage bits is not as the real bits
    // rowbytes+3
    //unsigned char * pImgL = m_ImageLeft.bits();
    //unsigned char * pImgR = m_ImageRight.bits();

    // for each pixel
    unsigned char LeftPix[3] = { 0 };
    unsigned char RightPix[3] = { 0 };

    // red-green
    // scanLine(i) is different from the data block
    // should use other method to get color
    // refer https://stackoverflow.com/questions/12382301/qt-qimage-how-to-extract-rgb
    // refer https://forum.qt.io/topic/73504/qimage-read-pixels-and-copy-them-with-scanline-method/2
    for (int i = 0; i < nRows_LR; ++i){
        // get the data from images
        QRgb * pImgL = reinterpret_cast<QRgb*>(m_ImageLeft.scanLine(i));
        QRgb * pImgR = reinterpret_cast<QRgb*>(m_ImageRight.scanLine(i));
        //unsigned char * pImgL = m_ImageLeft.scanLine(i);
        //unsigned char * pImgR = m_ImageRight.scanLine(i);
        for (int j = minCols_L; j < maxCols_L; ++j){
            // left Image
            if (j < 0 || j >= nCols_L){
                memset(LeftPix, 0, sizeof(unsigned char) * 3);
            }
            else{
                //LeftPix[0] = pImgL[(i * nCols_L + j) * 3];
                /*if (nChannel_L == 24){
                    memcpy(LeftPix, pImgL + j * 3, sizeof(unsigned char) * 3);
                }
                else{
                    LeftPix[0] = pImgL[j];
                    LeftPix[1] = pImgL[j];
                    LeftPix[2] = pImgL[j];
                }*/
                QColor pixel_color(pImgL[j]);
                LeftPix[0] = pixel_color.red();
                LeftPix[1] = pixel_color.green();
                LeftPix[2] = pixel_color.blue();
            }

            // right image
            int nIndex_R = j - nDisparity;
            if (nIndex_R < 0 || nIndex_R >= nCols_R){
                memset(RightPix, 0, sizeof(unsigned char) * 3);
            }
            else{
               /*if (nChannel_R == 24) {
                    memcpy(RightPix, pImgR + nIndex_R * 3, sizeof(unsigned char) * 3);
                }
                else{
                    RightPix[0] = pImgR[nIndex_R];
                    RightPix[1] = pImgR[nIndex_R];
                    RightPix[2] = pImgR[nIndex_R];
                }*/
                QColor pixel_color(pImgR[nIndex_R]);
                RightPix[0] = pixel_color.red();
                RightPix[1] = pixel_color.green();
                RightPix[2] = pixel_color.blue();
            }

            // fusion
            int nIndex = j - minCols_L;
            pImage[(i * nCols_LR + nIndex) * 3] = RightPix[0];
            pImage[(i * nCols_LR + nIndex) * 3 + 1] = RightPix[1];
            pImage[(i * nCols_LR + nIndex) * 3 + 2] = LeftPix[2];
        }
    }

    // Format_RGB888 is wrong
    // should use Format_RGB32
    m_ImageRedGreen = QImage(nCols_LR, nRows_LR, QImage::Format_RGB32);
    m_ImageRedGreen.fill(0);
    for (int i = 0; i < nRows_LR; ++i){
        //memcpy(m_ImageRedGreen.scanLine(i), pImage + i * nCols_LR * 3, sizeof(unsigned char) * nCols_LR * 3);
        QRgb * pLineQimg = reinterpret_cast<QRgb*>(m_ImageRedGreen.scanLine(i));
        unsigned char * pLineImage = pImage + i * nCols_LR * 3;
        for (int j = 0; j < nCols_LR; ++j){
           QColor pixel_color(pLineImage[j * 3], pLineImage[j * 3 + 1], pLineImage[j * 3 + 2]);
           pLineQimg[j] = pixel_color.rgb();
        }
    }
    //m_ImageRedGreen.save("/home/tengwu/mountdisk/stereo.jpg");
    delete []pImage;        pImage = NULL;
}

void ImageShowView::SetDisparity(double disparity)
{
    m_disparity = disparity;
}

void ImageShowView::ChangeDisparity(double disparity)
{
    double NewDisparity = m_disparity + disparity/m_scale;
    if (NewDisparity <= m_nMaxDisp && NewDisparity >= m_nMinDisp){
        m_disparity = NewDisparity;
        CreateRedGreenImage();

        SetWidgetSize();
        update();
    }
}

void ImageShowView::ZoomImage(double scale)
{
    m_scale *= scale;
    SetWidgetSize();
    update();
}

void ImageShowView::SetScale(double scale)
{
    m_scale = scale;
    SetWidgetSize();
    update();
}

void ImageShowView::FitWindow(int width, int height)
{
    int nSrcCols = 0;
    int nSrcRows = 0;

    switch (m_showType) {
    case LEFT_IMAGE:
        nSrcCols = m_ImageLeft.width();
        nSrcRows = m_ImageLeft.height();
        break;
    case RIGHT_IMAGE:
        nSrcCols = m_ImageRight.width();
        nSrcRows = m_ImageRight.height();
        break;
    case RED_GREEN:
        nSrcCols = m_ImageRedGreen.width();
        nSrcRows = m_ImageRedGreen.height();
        break;
    default:
        nSrcCols = 100;
        nSrcRows = 100;
        break;
    }

    double wScale = (double)width/(double)nSrcCols;
    double hScale = (double)height/(double)nSrcRows;

    double scale = std::min(wScale, hScale);

/*
    if (scale > 1.0){
        scale = 1.0;
    }
*/
    m_scale = scale;
    SetWidgetSize();
    update();
}

void ImageShowView::SetWidgetSize()
{
    int nSrcCols = 0;
    int nSrcRows = 0;

    switch (m_showType) {
    case LEFT_IMAGE:
        nSrcCols = m_ImageLeft.width();
        nSrcRows = m_ImageLeft.height();
        break;
    case RIGHT_IMAGE:
        nSrcCols = m_ImageRight.width();
        nSrcRows = m_ImageRight.height();
        break;
    case RED_GREEN:
        nSrcCols = m_ImageRedGreen.width();
        nSrcRows = m_ImageRedGreen.height();
        break;
    default:
        nSrcCols = 100;
        nSrcRows = 100;
        break;
    }

    int nCols = int(nSrcCols * m_scale + 0.5);
    int nRows = int(nSrcRows * m_scale + 0.5);

    setFixedSize(nCols, nRows);
}
