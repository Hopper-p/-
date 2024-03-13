#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H
#include <QString>
#include "singleclass.h"
class VideoModel
{
public:
    static VideoModel* getInstance();
    /** 插入视频数据
     * @brief insertByUser
     * @param name
     * @param pwd
     * @return  0-执行成功 -1-执行失败
     */
    int insertByVideo(QString videoName, QString videoPath, QString videoCoverPath, QString createTime, int frameNum);
    /** 查询分页的数据
     * @brief selectByVideoName
     * @param count
     * @param pageNum
     * @param qres
     * @param row
     * @param col
     * @return
     */
    int selectByVideoName(int count,int pageNum,char **&qres,int &row,int &col);
    /** 查询存储了多少数据
     * @brief selectByBideoCol
     * @param row
     * @return  0-查询成功 1-查询失败 -1-执行失败
     */
    int selectByBideoCol(int &row);
    /** 根据视频名称查找路径
     * @brief selectByVideoPath
     * @param videoName
     * @param qres
     * @return 0-查询成功 1-查询失败 -1-执行失败
     */
    int selectByVideoPath(QString videoName,char **&qres);

    int selectByVideoTime(QString videoTime,char **&qres,int &row,int &col);
    int selectByVideoTime(QString videoTime,int count,int pageNum,char **&qres,int &row,int &col);
private:
    VideoModel();
    static VideoModel* instance;
};

#endif // VIDEOMODEL_H
