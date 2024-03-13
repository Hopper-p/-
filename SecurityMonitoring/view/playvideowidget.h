#ifndef PLAYVIDEOWIDGET_H
#define PLAYVIDEOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QComboBox>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include "thread/decodevideothread.h"
#include "controller/settingcontroller.h"
#include "downwidget.h"
class PlayVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayVideoWidget(QWidget *parent = nullptr);
    /**加载QSS
     * @brief loadQss
     */
    void loadQss();
    /**加载控件
     * @brief initControl
     */
    void initControl();
    /**加载链接
     * @brief initConnect
     */
    void initConnect();
    void setVideoName(const QString &value);

    void playStart(QString videoUrl);
    void setUserId(const QString &value);

private:
    QVBoxLayout *totalLayout,*playLayout;
    QHBoxLayout *topLayout,*middLayout,*bottomLayout,*botLayout1,*botLayout2,*timLayout;
    QWidget *topview,*middleView,*bottomView,*bottomViews;
    QLabel *topLab1,*topLab2,*topLab3,*timeLab,*proLabel,*playLab;
    QPushButton *playBtn,*plyBtn2,*plyBtn5,*lastEpisodeBtn,*nextEpisodeBtn;
    QProgressBar *playBar;
    QComboBox *comBx2;
    QString videoName;
    QImage image;
    bool isPlay;
    QString videoUrl;
    DecodeVideoThread *videoThread;//回放线程
    QString userId;
    QList<Setting*> settingList;
    DownWidget *DownWin;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void videoLast();
    void videoNext();
    void updateImg();
public slots:
    void showDown();
    void showImg(QImage image);
    void playHandover();
    void Changes(QString mulriple);
    void toDownload();
    void picture();
};

#endif // PLAYVIDEOWIDGET_H
