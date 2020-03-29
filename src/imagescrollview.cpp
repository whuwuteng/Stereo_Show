#include "imagescrollview.h"

#include "imageshowview.h"

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
        int px = 1;
        if (event->delta() < 0){
            px = -1;
        }

        if (event->modifiers().testFlag(Qt::ShiftModifier)){
            px *= 5;
        }

        ImageShowView * pWidget = (ImageShowView * )widget();
        pWidget->ChangeDisparity(px);
    }
    else{
        QScrollArea::wheelEvent(event);
    }
}
