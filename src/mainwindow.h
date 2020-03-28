#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QMainWindow>

#include "ui_mainwindow.h"
#include "imageshowview.h"

namespace Ui {
class mainwindow;
}

// reference https://stackoverflow.com/questions/36389717/difference-between-drawing-with-qpainter-and-qgraphicsview-qgraphicsscene
class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

protected:
    //virtual void paintEvent(QPaintEvent * event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

private:
    // load stereo image
    void LoadStereoFile();

    // use scroll bar
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    // scale image
    void scaleImage(double factor);

    // show image
    void ShowScene();

private:
    Ui::mainwindow *ui;

    // stereo images
    QString m_strLeftImg;
    QString m_strRightImg;

    // show image in a label
    QLabel *m_pImageLabel;
    QScrollArea *m_pScrollArea;

    // a higher interface for QPainter
    //QGraphicsScene* m_pScene;
    //QGraphicsView* m_pView;

    double m_ScaleFactor;

    QImage m_ImgLeft;
    QImage m_ImgRight;
};
#endif // MAINWINDOW_H
