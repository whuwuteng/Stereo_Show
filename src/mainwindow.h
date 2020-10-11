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
    // file
    void open();

    // image zoom
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

    // image mode
    void showLeft();
    void showRight();
    void showRed_Green();

    // load setting
    void loadSettings();
    void about();

private:
    // load stereo image
    void LoadStereoFile();

private:
    Ui::mainwindow *ui;

    // stereo images
    QString m_strLeftImg;
    QString m_strRightImg;

    // setting file
    QString m_strSettingsFile;

    double m_disparity;

    // show image in a label
    ImageShowView *m_pMainWidget;
    ImageScrollView *m_pScrollArea;
};
#endif // MAINWINDOW_H
