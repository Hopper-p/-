#include "settingmodel.h"
SettingModel *SettingModel::instance = nullptr;
SettingModel *SettingModel::getInstance()
{
    if(nullptr == SettingModel::instance)
        SettingModel::instance;
    return SettingModel::instance;
}

int SettingModel::insertBySetting(QString vStorage, QString iStorage, int time, QString cameraName)
{
    QString insertQsq = QString("INSERT INTO tbl_setting VALUES ('%1','%2',%3,'%4');")
            .arg(vStorage).arg(iStorage).arg(time).arg(cameraName);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(insertQsq);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

int SettingModel::selectBySetting(char **&qres, int &row, int &col)
{
    QString selectSql = QString("SELECT * FROM tbl_setting;");

    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->getData(selectSql.toUtf8(),qres,row,col);
    if(SQLITE_OK == res)
    {
        if(row>0)   //查询到内容
        {
            return 0;   //查询成功
        }else {
            return 1;   //查询失败
        }
    }else {
        return -1;      //执行失败
    }
}

int SettingModel::upadteBySetting(QString vStorage, QString iStorage, int time, QString cameraName)
{
    QString upSql = QString("UPDATE tbl_setting SET video_path='%1',image_path='%2',interval_time=%3,camera_name='%4';")
            .arg(vStorage).arg(iStorage).arg(time).arg(cameraName);
    SingleClass *dbinstance = SingleClass::getInstance();
    int res = dbinstance->insertDeleteUpdate(upSql);
    if(SQLITE_OK == res)
    {
        return 0;      //执行成功
    }else {
        return -1;     //执行失败
    }
}

SettingModel::SettingModel()
{

}
