
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

    // method 3

    m_pMainWidget = new ImageShowView(this);
    m_pMainWidget->setFixedSize(5000, 5000);
    m_pMainWidget->setStyleSheet("background-color: yellow ");

    m_pScrollArea = new ImageScrollView();
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setWidget(m_pMainWidget);
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
    }
}

// load stereo image
void mainwindow::LoadStereoFile()
{
    m_pMainWidget->LoadStereoFile(m_strLeftImg, m_strRightImg);

    // make no sense
    m_pMainWidget->show();
}

void mainwindow::zoomIn()
{
    //scaleImage(1.25);
}

void mainwindow::zoomOut()
{
    //scaleImage(0.8);
}

void mainwindow::normalSize()
{
    //m_pImageLabel->adjustSize();
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
