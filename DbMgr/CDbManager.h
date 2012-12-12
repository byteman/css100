#ifndef CDbManager_H
#define CDbManager_H

#include "CppSQLite3.h"
#include "QureySqlList.h"

///////////////////////表名定义宏///////////////////////////////////////////////////
#define TB_USER			"tb_user"		                    /*用户信息*/
#define TB_NetParam   	"tb_netParam"		                /*网络参数信息*/

class CDbManager
{
    
public:
    CDbManager();

    virtual ~CDbManager();


public:
		///@brief
		///连接数据库
    int connect(char *pDbPath);
		///@brief
		///断开数据库
    int disconnect();
		///@brief
		///根据ID获取数据
    int getRecord(int nType,char *pOutBuf,int *nOutLen );
		///@brief
		///根据ID设置数据
    int setRecord(int nType,char *pInBuf,int nInLen);
		///@brief
		///根据ID更新数据
    int updateRecord(int nType,char *pInBuf,int nInlen);
		///@brief
		///清除数据
    int clearRecord(int nType);
		///@brief
		///判断信息是否存在
    int isRecord(int nType);

public:
		///@brief
		///设置用户信息
	int setUserInfo(TUser tInfo);
		///@brief
		///更新用户信息
	int updateUserInfo(TUser tInfo);
		///@brief
		///得到用户信息
	int	getUserInfo(TUser& tInfo);
		///@brief
		///查询用户信息
    listUser* queryUser();
		///@brief
		///删除用户信息
    int deleteUser(unsigned int nID);


		
public:
		///@brief
		///设置网络信息
	int setNetParamInfo(TNetParam tInfo);
		///@brief
		///更新网络信息
	int updateNetParamInfo(TNetParam tInfo);
		///@brief
		///得到网络信息
	int	getNetParamInfo(TNetParam& tInfo);
		///@brief
		///查询网络信息
    listNetParam* queryNetParam();
		///@brief
		///删除网络信息
    int deleteNetParam(unsigned int nID);
	
    
public:
	CppSQLite3DB 			m_pDB;
	bool					m_isConnect;

    
};


#endif
