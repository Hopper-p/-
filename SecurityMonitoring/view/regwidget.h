#ifndef REGWIDGET_H
#define REGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>
class RegWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegWidget(QWidget *parent = nullptr);
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
    QLabel *accountLab,*nickNameLab,*pwdLab,*conPwdLab;
    QLineEdit *accountEdit,*nickNameEdit,*pwdEdit,*conPwdEdit;
    QPushButton *logBtn,*exitBtn,*eyesPwdBtn,*eyesConPwdBtn;
    bool handMod,handMod1;
    QRegExpValidator *valid1,*valid2;
signals:
    void backToLogin();
    void backToLogin(QString account);
public slots:
    void doReg();
    void handPwdText();
    void handConPwdText();
};

#endif // REGWIDGET_H
