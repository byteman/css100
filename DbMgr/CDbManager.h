#ifndef CDbManager_H
#define CDbManager_H

#include "CppSQLite3.h"
#include "QureySqlList.h"

///////////////////////���������///////////////////////////////////////////////////
#define TB_USER			"tb_user"		                    /*�û���Ϣ*/
#define TB_NetParam   	"tb_netParam"		                /*���������Ϣ*/

class CDbManager
{
    
public:
    CDbManager();

    virtual ~CDbManager();


public:
		///@brief
		///�������ݿ�
    int connect(char *pDbPath);
		///@brief
		///�Ͽ����ݿ�
    int disconnect();
		///@brief
		///����ID��ȡ����
    int getRecord(int nType,char *pOutBuf,int *nOutLen );
		///@brief
		///����ID��������
    int setRecord(int nType,char *pInBuf,int nInLen);
		///@brief
		///����ID��������
    int updateRecord(int nType,char *pInBuf,int nInlen);
		///@brief
		///�������
    int clearRecord(int nType);
		///@brief
		///�ж���Ϣ�Ƿ����
    int isRecord(int nType);

public:
		///@brief
		///�����û���Ϣ
	int setUserInfo(TUser tInfo);
		///@brief
		///�����û���Ϣ
	int updateUserInfo(TUser tInfo);
		///@brief
		///�õ��û���Ϣ
	int	getUserInfo(TUser& tInfo);
		///@brief
		///��ѯ�û���Ϣ
    listUser* queryUser();
		///@brief
		///ɾ���û���Ϣ
    int deleteUser(unsigned int nID);


		
public:
		///@brief
		///����������Ϣ
	int setNetParamInfo(TNetParam tInfo);
		///@brief
		///����������Ϣ
	int updateNetParamInfo(TNetParam tInfo);
		///@brief
		///�õ�������Ϣ
	int	getNetParamInfo(TNetParam& tInfo);
		///@brief
		///��ѯ������Ϣ
    listNetParam* queryNetParam();
		///@brief
		///ɾ��������Ϣ
    int deleteNetParam(unsigned int nID);
	
    
public:
	CppSQLite3DB 			m_pDB;
	bool					m_isConnect;

    
};


#endif
