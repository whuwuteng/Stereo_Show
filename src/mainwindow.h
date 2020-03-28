#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QMainWindow>

#include "ui_mainwindow.h"
#include "imageshowview.h"
#include "imagescrollview.h"

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

private:
    Ui::mainwindow *ui;

    // stereo images
    QString m_strLeftImg;
    QString m_strRightImg;

    // show image in a label
    ImageShowView *m_pMainWidget;
    ImageScrollView *m_pScrollArea;
};
#endif // MAINWINDOW_H
