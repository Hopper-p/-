#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H
#include <QString>
#include <QList>
#include "data/setting.h"
class SettingController
{
public:
    static SettingController* getInstance();
    //写入设置信息
    int doSetting(QString vStorage,QString iStorage,int time,QString cameraName);
    //查询设置表内是否有数据
    QList<Setting*> initSettingData();
private:
    SettingController();
    static SettingController* instance;
};

#endif // SETTINGCONTROLLER_H
