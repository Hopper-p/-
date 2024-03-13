#ifndef DOWNWIDGET_H
#define DOWNWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "thread/transcodetonormalthread.h"
class DownWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownWidget(QWidget *parent = nullptr);
    void initControl();
    void setVideoName(const QString &value);

    void setVideoUrl(const QString &value);

    void setUserId(const QString &value);

private:
    QVBoxLayout *totalLayout;
    QHBoxLayout *topLayout,*middLayout,*bottomLayout;
    QWidget *topview,*middleView,*bottomView;
    QLabel *pathLab,*nameLab;
    QLineEdit *pathEdit,*nameEdit;
    QPushButton *okBtn,*outBtn,*urlBtn;
    QComboBox *urlBox1;
    QString videoName,videoUrl;
    TransCodeToNormalThread *TransCode;
    QString userId;
signals:

public slots:
    void showDialog();
    void downFile();
};

#endif // DOWNWIDGET_H
