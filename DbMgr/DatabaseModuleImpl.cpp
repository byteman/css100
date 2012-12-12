#include "DatabaseModuleImpl.h"

DatabaseModuleImpl::DatabaseModuleImpl()
{

}

DatabaseModuleImpl::~DatabaseModuleImpl()
{

}

void DatabaseModuleImpl::start()
{
	_LogTrace<<"@@@@@@数据库模块启动"<<_LogTraceEnd;

	#ifdef DEBUG
	m_CDbManager.connect("F://GOGOGO//CSS100//Soft_Design//Target//db//CSS100System.sqlite3");
	#else
	m_CDbManager.connect("./CSS100System.sqlite3");
	#endif

}

void DatabaseModuleImpl::stop()
{
	m_CDbManager.disconnect();
}

DatabaseModuleImpl&DatabaseModuleImpl::instance()
{
	static  CORE::SingletonHolder<DatabaseModuleImpl> sh;
	return *sh.get();
}

int DatabaseModuleImpl::connect(char *pDbPath)
{
	return 0;
}

int DatabaseModuleImpl::disconnect()
{
	return 0;
}


int DatabaseModuleImpl::getRecord(int nType,char *pOutBuf,int *nOutLen )
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);
	return m_CDbManager.getRecord(nType, pOutBuf, nOutLen);
}

int DatabaseModuleImpl::setRecord(int nType,char *pInBuf,int nInLen)
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);
	return m_CDbManager.setRecord(nType,pInBuf,nInLen);
}

int DatabaseModuleImpl::updateRecord(int nType,char *pInBuf,int nInLen)
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);
	return m_CDbManager.updateRecord(nType,pInBuf,nInLen);
}

int DatabaseModuleImpl::clearRecord(int nType)
{
	return 0;
}

int DatabaseModuleImpl::isRecord(int nType)
{
	return 0;
}



	///@brief
	///用户信息
listUser* DatabaseModuleImpl::queryUser()
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);

	return m_CDbManager.queryUser();
}

void DatabaseModuleImpl::deletelistUser(listUser*param)
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);

	TUser*item;
	listUser::iterator it;
	
	for(it=param->begin();it!=param->end();it++)
	{
		item=*it;
		delete item;
	}

	param->clear();
	delete param;
	param=0;
}


int DatabaseModuleImpl::deleteUser(unsigned int nID)
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);

	return m_CDbManager.deleteUser(nID);
}

	///@brief
	///网络参数信息
listNetParam* DatabaseModuleImpl::queryNetParam()
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);

	return m_CDbManager.queryNetParam();

}
int DatabaseModuleImpl::deleteNetParam(unsigned int nID)
{
	CORE::Core_FastMutex::ScopedLock lock(m_mutex);

	return m_CDbManager.deleteNetParam(nID);
}

void  DatabaseModuleImpl::deletelistNetParam(listNetParam*param)
{
	TNetParam*item;
	listNetParam::iterator it;
	
	for(it=param->begin();it!=param->end();it++)
	{
		item=*it;
		delete item;
	}

	param->clear();
	delete param;
	param=0;

}




