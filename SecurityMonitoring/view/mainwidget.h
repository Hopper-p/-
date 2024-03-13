#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QDateTime>
#include "settingwidget.h"
#include "loginwidget.h"
#include <QGridLayout>
#include "monitorwidget.h"
#include <QStackedWidget>
#include "playbackwidget.h"
#include "logwidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
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
    /**获取系统时间
     * @brief getNowTime
     * @return
     */
    QString getNowTime();

private:
    QVBoxLayout *totalLayout;
    QHBoxLayout *topLayout,*mainLayout;
    QWidget *topView,*bottomView,*mainView;
    QLabel *imgLogoLab,*titleLab,*timeLab;
    QPushButton *monitorToggleBtn,*playBackToggleBtn,*logQueryBtn,*settingsBtn,*loginBtn;
    QTimer *timer;
    SettingWidget *settingWin;
    LoginWidget *loginWin;
    MonitorWidget *monitorWin;
    PlayBackWidget *playBackWin;
    QStackedWidget *mainWin;
    QString userId;
    LogWidget *logWin;
    bool loginStaus;
protected:
    void closeEvent(QCloseEvent *event);
signals:

public slots:
    void updateImg();
    void timerUpdate(void);//使时间实时更新
    void showMain();//回到主界面
    void showMain(QString userId);//回到主界面(用户账号)
    void showSetting();//弹出设置界面
    void showLoginWin();//弹出登录界面
    void showMonitor();
    void showPlayBack();
    void showLog();
};

#endif // MAINWIDGET_H
