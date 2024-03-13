#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
#include "singleclass.h"
class UserModel
{
public:
    static UserModel* getInstance();
    /** 校验账号和密码是否存在
     * @brief selectByUserIdAndPwd
     * @param Id
     * @param pwd
     * @return  0-成功 1-失败 -1-sql执行失败
     */
    int selectByUserIdAndPwd(QString Id,QString pwd);
    /** 将用户登录状态进行更新
     * @brief updateUserStatus
     * @param Id
     * @param status
     * @return 0-执行成功   -1-执行失败
     */
    int updateUserStatus(QString Id,int status);
    /** 根据用户账户来查询用户名
     * @brief selectByUserName
     * @param userId
     * @param qres
     * @return  0-成功 1-失败 -1-sql执行失败
     */
    int selectByUserName(QString userId,char **&qres);
    /** 插入新用户数据
     * @brief insertByUser
     * @param name
     * @param pwd
     * @return  0-执行成功 -1-执行失败
     */
    int insertByUser(QString account,QString name,QString pwd);
    /** 根据用户ID来查询登录状态
     * @brief selectByUserStatus
     * @param userId
     * @param qres
     * @return
     */
    int selectByUserStatus(QString userId,char **&qres);

    int selectByUserId(int userId, char **&qres);
private:
    UserModel();
    static UserModel* instance;
};

#endif // USERMODEL_H
