#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include <QList>
#include "data/setting.h"
class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);
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
    QLabel *vStorageLab,*iStorageLab,*acquisitionLab,*menuCameraLab;
    QLineEdit *vStorageEdit,*iStorageEdit;
    QComboBox *acquisitionCbx,*menuCameraCbx;
    QPushButton *vStorageBtn,*iStorageBtn,*okBtn,*outBtn;
    QList<Setting*> settingList;
signals:
    void backToMainWidget();
public slots:
    void showDialog();
    void doWrite();
    void closeThis();
};

#endif // SETTINGWIDGET_H
