#include "settingcontroller.h"
#include <QDebug>
#include "model/settingmodel.h"
SettingController *SettingController::instance = nullptr;
SettingController *SettingController::getInstance()
{
    if(nullptr == SettingController::instance)
        SettingController::instance = new SettingController;
    return SettingController::instance;
}

int SettingController::doSetting(QString vStorage,QString iStorage,int time,QString cameraName)
{
    int res = -1;
    QList<Setting*> settingList = SettingController::getInstance()->initSettingData();
    if(settingList.size() == 1)
    {
        res = SettingModel::getInstance()->upadteBySetting(vStorage,iStorage,time,cameraName);
    }else {
        res = SettingModel::getInstance()->insertBySetting(vStorage,iStorage,time,cameraName);
    }
    if(res == 0)
    {
        qDebug()<<"设置数据写入成功";
        return res;
    }else{
        qDebug()<<"设置数据写入失败";
        return res;
    }
}

QList<Setting *> SettingController::initSettingData()
{
    char **qres = nullptr;
    QList<Setting *> settingList;
    int row = 0,col = 0;
    int res = SettingModel::getInstance()->selectBySetting(qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)
        {
            for(int i=1;i<row+1;i++)
            {
                settingList.push_back(new Setting((qres[i*col]),(qres[i*col+1]),
                        atoi(qres[i*col+2]),(qres[i*col+3])));
            }
        }
    }
    //qDebug()<<qres[6];
    //qDebug()<<settingList.at(0)->getImagePath();
    //qDebug()<<"SettingController::initSettingData() res="<<res<<"row="<<row;
    return settingList;
}

SettingController::SettingController()
{

}
