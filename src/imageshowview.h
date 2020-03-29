#ifndef IMAGESHOWVIEW_H
#define IMAGESHOWVIEW_H

#include <QtCore>
#include <QtWidgets>

// a widget should be used
// Use QLabel has no problem
// if use the method 3
// the widget over write the event of qmainwindow
// conclusion :
// ImageShowView only show the image
// ImageScrollView pass the message

// a problem
// qimage is not spvzimagelayer
// zoomin image red-green is create in 1:1
// disparity and scale is not in the same loop
class ImageShowView : public QWidget
{
public:
    ImageShowView( QWidget* parent = 0 );
    ~ImageShowView();

    // image show model
    enum ImageShowType{ LEFT_IMAGE = 1, RIGHT_IMAGE, RED_GREEN };

    // interface
public:
    // load stereo image
    bool LoadStereoFile(QString strLeft, QString strRight);

    // change view model
    void ChangeModel(ImageShowType showType);

    // change disparity
    void ChangeDisparity(double disparity);

    // Zoom image
    void ZoomImage(double scale);

    // set scale
    void SetScale(double scale);

    // best fit
    void FitWindow(int width, int height);

protected:
    // paint the scene
    virtual void paintEvent(QPaintEvent * event);

    // generate red-green image
    void CreateRedGreenImage();

    // set widget size
    void SetWidgetSize();

    // create show image
    QImage ImageToZoom(QImage & srcImg);

private:
    QImage m_ImageLeft;
    QImage m_ImageRight;

    // red-green image
    QImage m_ImageRedGreen;

    // show type
    ImageShowType m_showType;

    // image offset
    double m_disparity;
    int m_nMaxDisp;
    int m_nMinDisp;

    double m_scale;
};
#endif // IMAGESHOWVIEW_H
