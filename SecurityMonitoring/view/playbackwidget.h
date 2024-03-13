#ifndef PLAYBACKWIDGET_H
#define PLAYBACKWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QCalendarWidget>
#include <QDateTimeEdit>
#include <QStackedWidget>
#include "imglistwidget.h"
#include "thread/decodevideothread.h"
#include "playvideowidget.h"
class PlayBackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayBackWidget(QWidget *parent = nullptr);
    /**加载样式
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
    void setUserId(const QString &value);
    void videoBack();

private:
    QVBoxLayout *leftLayout,*rightLayout;
    QHBoxLayout *totalLayout,*rightUpLayout,*rightDownLayout,*videoLayout;
    QWidget *leftView,*rightView,*rightUpView,*rightDownView,*videoView;
    QLabel *playVideoLab,*PageLab;
    QPushButton *videoListBtn,*leftPageBtn,*rightPageBtn,*topBtn,*DownBtn,*GoBtn,*clearTimeBtn;
    QLineEdit *pageEdit;
    QListWidget *videoListWidget,*titleListWidget;
    QCalendarWidget *calendar;
    QDateTimeEdit *searchEdit;
    int pageNum,currentPage,pageCount;
    QStackedWidget *playWin;
    ImgListWidget *imgWin;
    QImage image;
    DecodeVideoThread *videoThread;//回放线程
    PlayVideoWidget *VideoWin;//播放界面
    QString userId;
    QString dataTime;//用户查询时间
    bool queryIo;   //记录用户是否在查询
signals:

public slots:
    void clearTime();
    void updateImg();
    void videoLast();
    void videoNext();
    void toPlayer(QListWidgetItem *imageItem);
    void showImg(QImage image);//将解码的图片传入界面中
    void toWin(QListWidgetItem *usbItem);
    void rightPage();
    void leftPage();
    void topPage();
    void DownPage();
    void GoPage();
    void videoList();
};

#endif // PLAYBACKWIDGET_H
