#ifndef IMGLISTWIDGET_H
#define IMGLISTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QCalendarWidget>
#include <QDateTimeEdit>
class ImgListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImgListWidget(QWidget *parent = nullptr);
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
    void updateImg();
private:
    QVBoxLayout *rightLayout,*leftLayout;
    QHBoxLayout *totalLayout,*queryLayout,*queryBtnLayout;
    QWidget *leftView,*leftUpView,*rightView,*queryView,*queryBtnView;
    QGridLayout *leftUpLayout;
    QLabel *imgLabs[9],*imgNameLab,*imgSizeLab,*imgDimLab,*imgNameLabel,*imgSizeLabel,*imgDimLabel;
    QPushButton *videoListBtn,*clearTimeBtn;
    int page_num,imageNum,total_page_num;
    bool isShowSingle;
    QCalendarWidget *calendar;
    QDateTimeEdit *searchEdit;
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
};

#endif // IMGLISTWIDGET_H
