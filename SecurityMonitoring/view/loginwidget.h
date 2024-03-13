#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QPaintEvent>
#include "tools/verification.h"
#include "regwidget.h"
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
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
private:
    QLabel *nameLab,*pwdLab,*codeLab;
    QLineEdit *nameEdit,*pwdEdit,*codeEdit;
    QPushButton *logBtn,*regBtn,*codeBtn,*exitBtn,*eyesBtn;
    Verification *captchaBtn;
    bool handMod;
    RegWidget *regWin;
signals:
    void backToMain(QString name);
public slots:
    void doLogin();
    void handText();
    void toReg();
    void showSelf();
    void showSelf(QString name);
};

#endif // LOGINWIDGET_H
