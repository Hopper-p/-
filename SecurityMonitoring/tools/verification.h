#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QPushButton>


class Verification : public QPushButton
{
    Q_OBJECT
public:
    explicit Verification(QWidget *parent = nullptr);
    /*****************************************************************
    * 函数名称： getColor()
    * 功能描述： 随机挑选颜色
    * 参数说明： 无
    * 返回值：   返回颜色
    ******************************************************************/
    Qt::GlobalColor* getColor();
    //虚函数 接收绘制事件
    void paintEvent(QPaintEvent *event);
    QString m_captcha;
    Qt::GlobalColor* m_color;
    QTimer *m_timer;

signals:

public slots:
    /*****************************************************************
    * 函数名称： genCaptcha()
    * 功能描述： 产生验证码
    * 参数说明： 无
    * 返回值：   无
    ******************************************************************/
    QString genCaptcha();
    /*****************************************************************
    * 函数名称： TimeoutSlot()
    * 功能描述： 如果图片被点击，就更新
    * 参数说明： 无
    * 返回值：   无
    ******************************************************************/
    void TimeoutSlot();
};

#endif // VERIFICATION_H
