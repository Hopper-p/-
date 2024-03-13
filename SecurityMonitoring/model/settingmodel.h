#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H
#include <QString>
#include "singleclass.h"

class SettingModel
{
public:
    static SettingModel* getInstance();
    /** 写入用户设置的视频/图片存储位置、摄像头，采集时间
     * @brief insertBySetting
     * @param vStorage      视频存储位置
     * @param iStorage      图片存储位置
     * @param time          采集时间间隔
     * @param cameraName    摄像头配置
     * @return  0-成功  -1-失败
     */
    int insertBySetting(QString vStorage,QString iStorage,int time,QString cameraName);
    /** 查询设置表内的数据
     * @brief selectBySetting
     * @param qres
     * @param row
     * @param col
     * @return  0-查询成功 1-查询失败 -1-sql执行失败
     */
    int selectBySetting(char **&qres, int &row, int &col);
    /** 修改设置表内的数据
     * @brief upadteBySetting
     * @param vStorage
     * @param iStorage
     * @param time
     * @param cameraName
     * @return 0-修改成功  -1-修改失败
     */
    int upadteBySetting(QString vStorage,QString iStorage,int time,QString cameraName);
private:
    SettingModel();
    static SettingModel* instance;
};

#endif // SETTINGMODEL_H
