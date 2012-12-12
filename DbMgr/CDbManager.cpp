#include "CDbManager.h"

#include "CoreInc.h"

CDbManager::CDbManager():
				m_isConnect(false)
{

}
CDbManager::~CDbManager()
{

}



int CDbManager::connect(char *pDbPath)
{
	int nRet = 0;
	
	try
	{
		m_pDB.open(pDbPath);
		m_isConnect = true;
		_LogTrace<<"@@@@@@ connect ok"<<_LogTraceEnd;
		return 1;
	}
	catch(CppSQLite3Exception &e)
	{
		m_isConnect = false;
		_LogTrace<<"@@@@@@ connect error:"<<e.errorMessage()<<_LogTraceEnd;
		return 0;
	}
	return 0;
}

int CDbManager::disconnect()
{
	int nRet = 0;
	try
	{
		m_pDB.close();
		m_isConnect = false;
		return 0;

	}
	catch(CppSQLite3Exception &e)
	{
		_LogTrace<<"@@@@@@ disconnect error:"<<e.errorMessage() <<_LogTraceEnd;
		m_isConnect = true;
		return 1;

	}
	return 0;
}


int CDbManager::getRecord(int nType,char *pOutBuf,int *nOutLen )
{
	int nRet = 0;
	switch(nType)
	{
		case E_User:
		{
			TUser tInfo;
			memset(&tInfo, 0, sizeof(tInfo));
			memcpy(&tInfo, pOutBuf, sizeof(tInfo));
			nRet = getUserInfo(tInfo);
			if (nRet)
			{
				memcpy(pOutBuf, &tInfo, sizeof(tInfo));
				*nOutLen = sizeof(tInfo);
			}
			break;
		}
		case E_NetParam:
		{
			TNetParam tInfo;
			memset(&tInfo, 0, sizeof(tInfo));
			memcpy(&tInfo, pOutBuf, sizeof(tInfo));
			nRet = getNetParamInfo(tInfo);
			if (nRet)
			{
				memcpy(pOutBuf, &tInfo, sizeof(tInfo));
				*nOutLen = sizeof(tInfo);
			}
			break;
		}
		
		default:
		break;	
	}
	return 0;
}

int CDbManager::setRecord(int nType,char *pInBuf,int nInLen)
{
	int nRet = 0;
	switch(nType)
	{
		case E_User:
		{
			TUser tInfo;
			memset(&tInfo, 0, sizeof(tInfo));
			memcpy(&tInfo, pInBuf, sizeof(tInfo));
			nRet = setUserInfo(tInfo);
			break;
		}
		case E_NetParam:
		{
			TNetParam tInfo;
			memset(&tInfo,0,sizeof(tInfo));
			memcpy(&tInfo,pInBuf,sizeof(tInfo));
			nRet = setNetParamInfo(tInfo);
			break;
		}
		default:
		break;
	}
	return nRet;
}

int CDbManager::updateRecord(int nType,char *pInBuf,int nInlen)
{
	int nRet = 0;
	switch(nType)
	{
		case E_User:
		{
			TUser tInfo;
			memset(&tInfo, 0, sizeof(tInfo));
			memcpy(&tInfo, pInBuf, sizeof(tInfo));
			nRet = updateUserInfo(tInfo);
			break;
		}
		case E_NetParam:
		{
			TNetParam tInfo;
			memset(&tInfo, 0, sizeof(tInfo));
			memcpy(&tInfo, pInBuf, sizeof(tInfo));
			nRet = updateNetParamInfo(tInfo);
			break;
		}
		
		default:
		break;
		
	}
	return 0;
}

int CDbManager::clearRecord(int nType)
{
	int nRet = 0;
	switch(nType)
	{
		case E_User:
		{
			break;
		}
		
		case E_NetParam:
		{
			break;
		}
		
		default:
		break;
	}
	return nRet;
	return 0;
}

int CDbManager::isRecord(int nType)
{
	return 0;
}

int CDbManager::setUserInfo(TUser tInfo)
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		printf("DB is not connected!");
		return nRet;
	}
	
	try
	{
		CppSQLite3Buffer strInst;
		const char *tmp=strInst.format("Insert into %s (userid,  username, password, state, permission, efficienttime, recordstate)values(%u, '%s', '%s',  %u, %u, '%s', %u)",
			TB_USER
			,tInfo.nUserid
			,tInfo.sUserName
			,tInfo.sPassword
			,tInfo.cUserState
			,tInfo.cUserPermission
			,tInfo.cEfficentTime
			,tInfo.nRecordState);

			int row = m_pDB.execDML(tmp);
			if(row > 0)
			{
				return 1;
			}
	}
	catch(CppSQLite3Exception &e)
	{
		printf("setUserInfo erorr %s",e.errorMessage());
	}
	return 0;
}

int CDbManager::updateUserInfo(TUser tInfo)
{
	printf("updateUserInfo!\n");
	if(false == m_isConnect)
	{
		printf("DB is not connected!");
		return 0;
	}

	int nRet = 0;
	try
	{
		CppSQLite3Buffer strUPinfo;
		const char *tmp = strUPinfo.format("update %s set  username = '%s', password = '%s', state = %u,\
		permission = %u, efficienttime = '%s', recordstate = %u where userid = %u",
			TB_USER
			,tInfo.sUserName
			,tInfo.sPassword
			,tInfo.cUserState
			,tInfo.cUserPermission
			,tInfo.cEfficentTime
			,tInfo.nRecordState
			, tInfo.nUserid);
			int rows =m_pDB.execDML(tmp);
			if(rows > 0)
			{
				nRet = 1;
			}
	}
	catch(CppSQLite3Exception &e)
	{
		printf("updateUserInfo erorr %s",e.errorMessage());
	}
	return nRet;
}

int CDbManager::getUserInfo(TUser & tInfo)
{
	printf("getUserInfo\n");
	if(false == m_isConnect)
	{
		printf("DB is not connected!");
		return 0;
	}
	int nRet = 0;
	CORE::CData strUserLoginName;
	CORE::CData strUserName;
	CORE::CData strPassword;
	CORE::CData strEfficentTime;
	try
	{
		CppSQLite3Buffer strSql;
		const char * tmp = strSql.format("select * from %s where userid = %u",TB_USER,tInfo.nUserid);
		CppSQLite3Query qry = m_pDB.execQuery(tmp);
		while(!qry.eof())
		{
			strUserName=qry.getStringField("username");
			strPassword=qry.getStringField("password");
			strEfficentTime=qry.getStringField("efficienttime");
			
			tInfo.cUserState =  qry.getIntField("state");
			tInfo.cUserPermission=  qry.getIntField("permission");
			tInfo.nRecordState =  qry.getIntField("recordstate");
			
			qry.nextRow();
			nRet = 1;
		
			strcpy(tInfo.sUserName, strUserName.c_str());
			strcpy(tInfo.sPassword, strPassword.c_str());
			strcpy(tInfo.cEfficentTime, strEfficentTime.c_str());
		}
		qry.finalize();
	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n getUserInfo: eCode = %u, eMsg = %s",e.errorCode(), e.errorMessage());
	}
	
	return nRet;
}
	///@brief
	///查询用户信息
listUser* CDbManager::queryUser()
{
	if (!m_isConnect)
	{
		printf("\n Db is not connected!");
		return 0;
	}
	
	listUser*retList=0;
	TUser*tInfo;
	try
	{
		CppSQLite3Buffer strSql;
		const char* tmp = strSql.format("select * from %s limit 1000",	TB_USER);
		CppSQLite3Query qry =  m_pDB.execQuery(tmp);
		if(qry.eof())
		{
			return 0;
		}
		
		retList=new listUser;
		
		while (!qry.eof())
		{
			tInfo=new TUser;
			memset(tInfo, 0, sizeof(TUser));
			retList->push_back(tInfo);

			tInfo->nId 				=  qry.getIntField("nId");
			tInfo->nUserid			=  qry.getIntField("userid");
			
			if(strlen(qry.getStringField("username"))<128)
				strncpy(tInfo->sUserName, qry.getStringField("username"), strlen(qry.getStringField("username")));
				
			if(strlen(qry.getStringField("password"))<128)
				strncpy(tInfo->sPassword, qry.getStringField("password"), strlen(qry.getStringField("password")));
				
			tInfo->cUserState		=  qry.getIntField("state");
			
			tInfo->cUserPermission	=  qry.getIntField("permission");
			
			if(strlen(qry.getStringField("efficienttime"))<128)
				strncpy(tInfo->cEfficentTime, qry.getStringField("efficienttime"), strlen(qry.getStringField("efficienttime")));
				
			tInfo->nRecordState=  qry.getIntField("recordstate");
			qry.nextRow();
			
		}	
		qry.finalize();
	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n queryUser: eCode = %u, eMsg = %s",e.errorCode(), e.errorMessage());
	}

	return retList;
}
	///@brief
	///删除用户信息
int CDbManager::deleteUser(unsigned int nID)
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		printf("DB is not connected!");
		return nRet;
	}
	try
	{
		CppSQLite3Buffer strSql;
		const char * tmp = strSql.format("delete from %s where nId = %u",TB_USER,nID);
		int rows = m_pDB.execDML(tmp);
		if(rows > 0)
		{
			nRet = 1;
		}
	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n deleteUser: eCode = %d, eMsg = %s",e.errorCode(), e.errorMessage());
	}
	return nRet;
}

	///@brief
	///设置网络信息
int CDbManager::setNetParamInfo(TNetParam tInfo)
{
	if(false == m_isConnect)
	{
		return 0;
	}
	
	int nRet = 0;
	try
	{
		CppSQLite3Buffer strInst;
		const char *tmp = strInst.format("insert into %s (nId,localIp,localDns,localMark,localBroadCast,serverIP,serverPort,recordstate)values(%u,%s,%s,%s,%s,%s,%u,%u) ",
		TB_NetParam,
		tInfo.nId,
		tInfo.sLocalIp,
		tInfo.sLocalDns,
		tInfo.sLocalMark,
		tInfo.sLocalBroadCast,
		tInfo.sServerIP,
		tInfo.nServerPort);

		int row = m_pDB.execDML(tmp);

		if(row > 0)
		{
			return 1;
		}
	}
	catch(CppSQLite3Exception &e)
	{

		printf("setNetParmInfo erorr %s",e.errorMessage());
	}

}
	///@brief
	///更新网络信息
int CDbManager::updateNetParamInfo(TNetParam tInfo)
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		return nRet;
	}
	
	try
	{
		CppSQLite3Buffer strUpdate;
		const char * tmp = strUpdate.format("update %s set localIp = %s, localDns = %s,localMark = %s,localBroadCast = %s,serverIP = %s,\
		serverPort = %u,recordstate = %u where strTime = %s",
		TB_NetParam,
		tInfo.sLocalIp,
		tInfo.sLocalDns,
		tInfo.sLocalMark,
		tInfo.sLocalBroadCast,
		tInfo.sServerIP,
		tInfo.nServerPort,
		tInfo.nId);

		nRet = m_pDB.execDML(tmp);
		if(nRet > 0)
		{
			nRet = 1;
		}
	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n updateNetParamInfo: eCode = %d, eMsg = %s",e.errorCode(), e.errorMessage());
	}
	return nRet;
}
	///@brief
	///得到网络信息
int	CDbManager::getNetParamInfo(TNetParam& tInfo)
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		return nRet;
	}
	
	try
	{
		CORE::CData strlocalIp;
		CORE::CData strlocalDns;
		CORE::CData strlocalMark;
		CORE::CData strlocalBroadCast;
		CORE::CData strserverIP;

		CppSQLite3Buffer strSelect;
		const char * tmp = strSelect.format("select * from %s where nId = %u",TB_NetParam,tInfo.nId);
		CppSQLite3Query qry = m_pDB.execQuery(tmp);
		while(!qry.eof())
		{

			strlocalIp=qry.getStringField("localIp");
			strlocalDns=qry.getStringField("localDns");
			strlocalMark=qry.getStringField("localMark");
			strlocalBroadCast=qry.getStringField("localBroadCast");
			strserverIP=qry.getStringField("serverIP");
			
			tInfo.nServerPort =  qry.getIntField("serverPort");
			tInfo.nRecordState =  qry.getIntField("recordstate");
			
			qry.nextRow();
			nRet = 1;
		
			strncpy(tInfo.sLocalIp, strlocalIp.c_str(),MAX_LEN);
			strncpy(tInfo.sLocalDns, strlocalDns.c_str(),MAX_LEN);
			strncpy(tInfo.sLocalMark, strlocalMark.c_str(),MAX_LEN);
			strncpy(tInfo.sLocalBroadCast, strlocalBroadCast.c_str(),MAX_LEN);
			strncpy(tInfo.sServerIP, strserverIP.c_str(),MAX_LEN);

		}

	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n getNetParamInfo: eCode = %d, eMsg = %s",e.errorCode(), e.errorMessage());
	}
	return nRet;
}
	///@brief
	///查询网络信息
listNetParam* CDbManager::queryNetParam()
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		return 0;
	}
	listNetParam *retList;
	TNetParam *tInfo;
	try
	{
		CppSQLite3Buffer strQry;
		const char * tmp = strQry.format("select * from %s where nId > 1000",TB_NetParam);
		CppSQLite3Query qry  = m_pDB.execQuery(tmp);

		if(!qry.eof())
		{
			return 0;
		}
		retList = new listNetParam;

		while(!qry.eof())
		{
			tInfo = new TNetParam;
			memset(tInfo,0,sizeof(tag_netParam));

			retList->push_back(tInfo);

			tInfo->nId 				=  qry.getIntField("nId");
			
			if(strlen(qry.getStringField("localIp"))<128)
				strncpy(tInfo->sLocalIp, qry.getStringField("localIp"), strlen(qry.getStringField("localIp")));
				
			if(strlen(qry.getStringField("localDns"))<128)
				strncpy(tInfo->sLocalDns, qry.getStringField("localDns"), strlen(qry.getStringField("localDns")));

			if(strlen(qry.getStringField("localMark"))<128)
				strncpy(tInfo->sLocalMark, qry.getStringField("localMark"), strlen(qry.getStringField("localMark")));

			if(strlen(qry.getStringField("localBroadCast"))<128)
				strncpy(tInfo->sLocalBroadCast, qry.getStringField("localBroadCast"), strlen(qry.getStringField("localBroadCast")));

			if(strlen(qry.getStringField("serverIP"))<128)
				strncpy(tInfo->sServerIP, qry.getStringField("serverIP"), strlen(qry.getStringField("serverIP")));

			tInfo->nServerPort		=  qry.getIntField("serverPort");
			
			tInfo->nRecordState=  qry.getIntField("recordstate");
			qry.nextRow();
		}
		
		
	}
	catch(CppSQLite3Exception &e)
	{
		printf("queryNetParm: eCode = %d,eMsg = %s",e.errorCode(),e.errorMessage());
	}
	return retList;
}
	///@brief
	///删除网络信息
int CDbManager::deleteNetParam(unsigned int nID)
{
	int nRet = 0;
	if(false == m_isConnect)
	{
		printf("DB is not connected!");
		return nRet;
	}
	try
	{
		CppSQLite3Buffer strSql;
		const char * tmp = strSql.format("delete from %s where nId = %u",TB_NetParam,nID);
		int rows = m_pDB.execDML(tmp);
		if(rows > 0)
		{
			nRet = 1;
		}
	}
	catch (CppSQLite3Exception& e)
	{
		printf("\n deleteNetParm: eCode = %d, eMsg = %s",e.errorCode(), e.errorMessage());
	}
	return nRet;
}

    
