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

enum
    // interface
public:
    // load stereo image
    bool LoadStereoFile(QString strLeft, QString strRight);

protected:
    // paint the scene
    virtual void paintEvent(QPaintEvent * event);

private:
    QImage m_ImageLeft;
    QImage m_ImageRight;
};
#endif // IMAGESHOWVIEW_H
