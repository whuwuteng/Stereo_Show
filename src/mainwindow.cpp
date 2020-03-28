
#include <qmessagebox.h>

#include "mainwindow.h"
#include "stereodialog.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    // message
    connect(ui->uiActionOpen, &QAction::triggered, this, &mainwindow::open);
    connect(ui->uiActionZoom_In, &QAction::triggered, this, &mainwindow::zoomIn);
    connect(ui->uiActionZoom_Out, &QAction::triggered, this, &mainwindow::zoomOut);
    connect(ui->uiActionNormal_Size, &QAction::triggered, this, &mainwindow::normalSize);
    connect(ui->uiActionFit_to_Window, &QAction::triggered, this, &mainwindow::fitToWindow);
    connect(ui->uiActionAbout,&QAction::triggered, this, &mainwindow::about);
/*
    // reference https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
    // method 1
    m_pImageLabel = new QLabel();
    m_pImageLabel->setBackgroundRole(QPalette::Base);
    m_pImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_pImageLabel->setScaledContents(true);

    m_pScrollArea = new QScrollArea();
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setWidget(m_pImageLabel);
    //m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->setVisible(false);
    m_pScrollArea->show();

    QImage img;
    img.load("/home/tengwu/mountdisk/L.jpg");
    //QPixmap pixmap("/home/tengwu/mountdisk/L.jpg");

    QPixmap pixmap;
    pixmap.convertFromImage(img, Qt::ColorOnly);
    m_pImageLabel->setPixmap(pixmap);

    // important
    m_pImageLabel->resize(m_pImageLabel->pixmap()->size());
    m_pImageLabel->show();

    setCentralWidget(m_pScrollArea);
*/
/*
    // method 2
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(img));
    scene->addItem(item);
    view->show();

    setCentralWidget(view);

    m_pScene = new QGraphicsScene();
    m_pView = new QGraphicsView(m_pScene);
    setCentralWidget(m_pView);

    QImage img;
    img.load("/home/tengwu/mountdisk/L.jpg");

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(img));
    m_pScene->addItem(item);
    m_pView->show();
*/

    // method 3

    ImageShowView * pMainWidget = new ImageShowView(this);
    pMainWidget->setFixedSize(5000, 5000);
    pMainWidget->setStyleSheet("background-color: yellow ");
    pMainWidget->show();

    m_pScrollArea = new QScrollArea();
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setWidget(pMainWidget);
    //m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->setVisible(false);
    m_pScrollArea->show();

    setCentralWidget(m_pScrollArea);

    setWindowIcon(QPixmap("icons/red-green.jpg"));
    showMaximized();
}

mainwindow::~mainwindow()
{
    delete ui;
}

// load stereo images
void mainwindow::open() {
    // set the stereo image
    //loadFile(QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.bmp *.jpg)")));

    stereodialog dlg(this);
    dlg.show();
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted){
        m_strLeftImg = dlg.m_strLeftImg;
        m_strRightImg = dlg.m_strRightImg;
    }
    dlg.close();

    if (m_strLeftImg.isEmpty() || m_strRightImg.isEmpty()){
        QMessageBox::about(this, tr("Stereo Image Viewer"),
                tr("<b> Please open stereo images </b>"));
    }
    else{
        LoadStereoFile();
        ShowScene();
    }
}

// load stereo image
void mainwindow::LoadStereoFile()
{
    m_ImgLeft.load(m_strLeftImg);
    m_ImgRight.load(m_strRightImg);
}

// show the scrooll
void mainwindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void mainwindow::zoomIn()
{
    scaleImage(1.25);
}

void mainwindow::zoomOut()
{
    scaleImage(0.8);
}

void mainwindow::normalSize()
{
    //m_pImageLabel->adjustSize();
    m_ScaleFactor = 1.0;
}

//
void mainwindow::fitToWindow()
{

}

void mainwindow::about()
{
    QMessageBox::about(this, tr("About Stereo Image Viewer"),
            tr("<p>The <b> Stereo Image Viewer </b> shows the error in epilar images "));
}

void mainwindow::scaleImage(double factor)
{
    //Q_ASSERT(m_pImageLabel->pixmap());

    m_ScaleFactor *= factor;
    //m_pImageLabel->resize(m_ScaleFactor * m_pImageLabel->pixmap()->size());

}

// first test only one image
void mainwindow::ShowScene()
{
    //QPixmap pixmap;
    //pixmap.convertFromImage(m_ImgLeft, Qt::ColorOnly);
    //m_pImageLabel->setPixmap(pixmap);
    //m_pImageLabel->setMask(pixmap.mask());

    //m_pImageLabel->show();

    //ui->label_show->setPixmap(pixmap);
    //ui->label_show->setMask(pixmap.mask());


    //QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(m_ImgLeft));
    //m_pScene->addItem(item);
    //m_pView->show();
}

// same with MFC onDraw()
/*void mainwindow::paintEvent(QPaintEvent* event)
{

    QImage img;
    img.load("/home/tengwu/mountdisk/L.jpg");

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), img);
}
*/
// move mouse
void mainwindow::mouseMoveEvent(QMouseEvent *event)
{

}

void mainwindow::wheelEvent(QWheelEvent *event)
{
    QMessageBox::about(this, tr("Stereo Image Viewer"),
            tr("<b> main event </b>"));

}
