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

protected:
    // paint the scene
    virtual void paintEvent(QPaintEvent * event);

    // generate red-green image
    void CreateRedGreenImage();

private:
    QImage m_ImageLeft;
    QImage m_ImageRight;

    // red-green image
    QImage m_ImageRedGreen;

    // show type
    ImageShowType m_showType;

    // image offset
    double m_disparity;
};
#endif // IMAGESHOWVIEW_H
