#ifndef STEREODIALOG_H
#define STEREODIALOG_H

#include <QDialog>

namespace Ui {
class stereodialog;
}

class stereodialog : public QDialog
{
    Q_OBJECT

public:
    explicit stereodialog(QWidget *parent = 0);
    ~stereodialog();

public:
    QString m_strLeftImg;
    QString m_strRightImg;

public slots:
    // load Left Image
    void ScanLeft();

    // load right Image
    void ScanRight();

private:
    Ui::stereodialog *ui;
};
#endif // STEREODIALOG_H
