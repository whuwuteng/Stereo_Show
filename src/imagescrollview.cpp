#include "imagescrollview.h"

ImageScrollView::ImageScrollView( QWidget* parent/* = 0 */) : QScrollArea(parent)
{

}

ImageScrollView::~ImageScrollView()
{

}

// the message also transform to qscrollview
// should over write qscrollview
void ImageScrollView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)){
        //QMessageBox::about(this, tr("Stereo Image Viewer"), tr("<b> image event </b>"));

    }
    else{
        QScrollArea::wheelEvent(event);
    }
}
