//////////////////////////////////////////////////////////////////////////  
///     COPYRIGHT NOTICE  
///     Copyright (c) 2012,  
///     All rights reserved.  
///  
/// @file   DatabaseModuleImpl.h  
/// @brief 	实现数据库接口文件
///  
/// 
///  
/// @version 1.0	
/// @author	 jiongjiong
/// @date    2012年9月21日22:39:01
///  
///  
///     修订说明：最初版本  
//////////////////////////////////////////////////////////////////////////

#ifndef DatabaseModuleImpl_H
#define DatabaseModuleImpl_H

#include "DatabaseModuleInc.h"
#include "DatabaseModuleConfig.h"
#include "CDbManager.h"
#include "QureySqlList.h"
class DATABASEMODULE_API DatabaseModuleImpl
{
public:
	DatabaseModuleImpl();

	~DatabaseModuleImpl();

public:
	void start();

	void stop();

	static DatabaseModuleImpl&instance();

public:
		///@brief
		///连接数据库
    int connect(char *pDbPath);
		///@brief
		///断开数据库
    int disconnect();
		
		/** 
		 *	@brief	
		 *	根据相应的ID写数据库文件 
		 *	@param nType 	要写的数据
		 *	@param pInBuf 	输入的数据指针
		 *	@param nInLen 	输入的数据长度
		 *	@return    		写数据结果 
		 *	@note    		采用的是同步方式反映比较慢
		 */ 
    int setRecord(int nType,char *pInBuf,int nInLen);
		
		/** 
		 *	@brief	
		 *	从数据库中获得数据
		 *	@param nType 	要读取的数据表类型
		 *	@param pOutBuf 	输出的数据指针
		 *	@param nInLen 	输出的数据长度
		 *	@return    		读取数据结果 
		 */ 
    int getRecord(int nType,char *pOutBuf,int *nOutLen );
		
		/** 
		 *	@brief	
		 *	更新数据库数据
		 *	@param nType 	要更新的数据
		 *	@param pInBuf 	更新的数据指针
		 *	@param nInLen 	更新的数据长度
		 *	@return    		更新数据结果 
		 */ 
    int updateRecord(int nType,char *pInBuf,int nInLen);
		
		/** 
		 *	@brief	
		 *	根据ID删除数据
		 *	@param nType 	要删除的数据
		 *	@return    		删除数据结果 
		 */ 
    int clearRecord(int nType);
		
		/** 
		 *	@brief	
		 *	判断nType数据是否存在
		 *	@param nType 	要判断的数据
		 *	@return    		删除数据结果 
		 */ 
    int isRecord(int nType);

public:

		///@brief
		///用户信息
    listUser* queryUser();
    void deletelistUser(listUser*param);
    int deleteUser(unsigned int nID);
	
		///@brief
		///网络参数信息
    listNetParam* queryNetParam();
	int deleteNetParam(unsigned int nID);
    void deletelistNetParam(listNetParam*param);

private:
	
	CDbManager					m_CDbManager;
	CORE::Core_FastMutex		m_mutex;

};

#endif
