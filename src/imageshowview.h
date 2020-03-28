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

protected:
    virtual void paintEvent(QPaintEvent * event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
};
#endif // IMAGESHOWVIEW_H
