#ifndef IMAGESCROLLVIEW_H
#define IMAGESCROLLVIEW_H

#include <QtCore>
#include <QtWidgets>

class ImageScrollView : public QScrollArea
{
public:
    ImageScrollView( QWidget* parent = 0 );
    ~ImageScrollView();

protected:
    virtual void wheelEvent(QWheelEvent *event);
};
#endif // IMAGESCROLLVIEW_H
