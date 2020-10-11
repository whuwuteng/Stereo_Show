
#include <qmessagebox.h>

#include <iostream>

#include "mainwindow.h"
#include "stereodialog.h"

// icons from project https://github.com/AntonioRedondo/ImageFeatureDetector
mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    m_strSettingsFile = QApplication::applicationDirPath() + "/settings.ini";
    std::cout << "setting file: " << m_strSettingsFile.toStdString() << std::endl;

    loadSettings();

    // message
    connect(ui->uiActionOpen, &QAction::triggered, this, &mainwindow::open);
    connect(ui->uiActionZoom_In, &QAction::triggered, this, &mainwindow::zoomIn);
    connect(ui->uiActionZoom_Out, &QAction::triggered, this, &mainwindow::zoomOut);
    connect(ui->uiActionNormal_Size, &QAction::triggered, this, &mainwindow::normalSize);
    connect(ui->uiActionFit_to_Window, &QAction::triggered, this, &mainwindow::fitToWindow);
    connect(ui->uiActionAbout, &QAction::triggered, this, &mainwindow::about);

    connect(ui->uiActionLeft, &QAction::triggered, this, &mainwindow::showLeft);
    connect(ui->uiActionRight, &QAction::triggered, this, &mainwindow::showRight);
    connect(ui->uiActionRed_Green, &QAction::triggered, this, &mainwindow::showRed_Green);
    // method 3

    ui->uiActionOpen->setIcon(QPixmap("icons/fileopen.svg"));
    ui->uiActionOpen->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionOpen);

    ui->uiActionZoom_In->setIcon(QPixmap("icons/zoom-in.svg"));
    ui->uiActionZoom_In->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionZoom_In);

    ui->uiActionZoom_Out->setIcon(QPixmap("icons/zoom-out.svg"));
    ui->uiActionZoom_Out->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionZoom_Out);

    ui->uiActionNormal_Size->setIcon(QPixmap("icons/zoom-original.svg"));
    ui->uiActionNormal_Size->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionNormal_Size);

    ui->uiActionFit_to_Window->setIcon(QPixmap("icons/zoom-fit-best.svg"));
    ui->uiActionFit_to_Window->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionFit_to_Window);

    ui->uiActionLeft->setIcon(QPixmap("icons/left.png"));
    ui->uiActionLeft->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionLeft);

    ui->uiActionRight->setIcon(QPixmap("icons/right.png"));
    ui->uiActionRight->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionRight);

    ui->uiActionRed_Green->setIcon(QPixmap("icons/stereo.jpg"));
    ui->uiActionRed_Green->setIconVisibleInMenu(true);
    ui->mainToolBar->addAction(ui->uiActionRed_Green);

    m_pMainWidget = new ImageShowView(this);
    //m_pMainWidget->setFixedSize(5000, 5000);
    m_pMainWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_pMainWidget->setStyleSheet("background-color: yellow ");
    m_pMainWidget->SetDisparity(m_disparity);

    m_pScrollArea = new ImageScrollView();
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setWidget(m_pMainWidget);
    //m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->setVisible(false);
    m_pScrollArea->show();

    setCentralWidget(m_pScrollArea);

    setWindowIcon(QPixmap("icons/red-green.jpg"));
    showMaximized();

    //m_strLeftImg = QString("/home/tengwu/mountdisk/L.jpg");
    //m_strRightImg = QString("/home/tengwu/mountdisk/R.jpg");

    //m_strLeftImg = QString("/home/tengwu/mountdisk/im2.png");
    //m_strRightImg = QString("/home/tengwu/mountdisk/im6.png");

    //m_strLeftImg = QString("/home/tengwu/left.png");
    //m_strRightImg = QString("/home/tengwu/right.png");
    LoadStereoFile();
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
    m_pMainWidget->ZoomImage(1.25);
}

void mainwindow::zoomOut()
{
    m_pMainWidget->ZoomImage(0.8);
}

void mainwindow::normalSize()
{
    m_pMainWidget->SetScale(1.0);
}

void mainwindow::fitToWindow()
{
    int nWidth = width();
    int nHeith = height();
    m_pMainWidget->FitWindow(nWidth, nHeith);
}

void mainwindow::about()
{
    QMessageBox::about(this, tr("About Stereo Image Viewer"),
            tr("<p>The <b> Stereo Image Viewer </b> shows the error in epilar images "));
}

void mainwindow::showLeft()
{
    m_pMainWidget->ChangeModel(ImageShowView::LEFT_IMAGE);
}

void mainwindow::showRight()
{
    m_pMainWidget->ChangeModel(ImageShowView::RIGHT_IMAGE);
}

void mainwindow::showRed_Green()
{
    m_pMainWidget->ChangeModel(ImageShowView::RED_GREEN);
}

void mainwindow::loadSettings()
{
    QSettings settings(m_strSettingsFile, QSettings::NativeFormat);
    QString sText = settings.value("disp", "").toString();

    m_disparity = sText.toDouble();

    std::cout << "initial disparity: " << m_disparity << std::endl;
}
