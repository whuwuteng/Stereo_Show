
#include "stereodialog.h"
#include "ui_stereodialog.h"

#include <QtCore>
#include <QtWidgets>

stereodialog::stereodialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stereodialog)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton_Left, & QPushButton::clicked, this, & stereodialog::ScanLeft);
    QObject::connect(ui->pushButton_Right, & QPushButton::clicked, this, & stereodialog::ScanRight);
}

stereodialog::~stereodialog()
{
    delete ui;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void stereodialog::ScanLeft()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted){
        m_strLeftImg = dialog.selectedFiles().first();
    }

    //m_strLeftImg = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.bmp *.jpg)"));
    if (! m_strLeftImg.isEmpty()){
        ui->textBrowser_Left->setPlainText(m_strLeftImg);
    }
}

void stereodialog::ScanRight()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted){
        m_strRightImg = dialog.selectedFiles().first();
    }

    //m_strRightImg = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.bmp *.jpg)"));
    if (! m_strRightImg.isEmpty()){
        ui->textBrowser_Right->setPlainText(m_strRightImg);
    }
}
