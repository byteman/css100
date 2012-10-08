//////////////////////////////////////////////////////////////////////////  
///     COPYRIGHT NOTICE  
///     Copyright (c) 2012,  
///     All rights reserved.  
///  
/// @file   DatabaseModuleImpl.h  
/// @brief 	ʵ�����ݿ�ӿ��ļ�
///  
/// 
///  
/// @version 1.0	
/// @author	 jiongjiong
/// @date    2012��9��21��22:39:01
///  
///  
///     �޶�˵��������汾  
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
		///�������ݿ�
    int connect(char *pDbPath);
		///@brief
		///�Ͽ����ݿ�
    int disconnect();
		
		/** 
		 *	@brief	
		 *	������Ӧ��IDд���ݿ��ļ� 
		 *	@param nType 	Ҫд������
		 *	@param pInBuf 	���������ָ��
		 *	@param nInLen 	��������ݳ���
		 *	@return    		д���ݽ�� 
		 *	@note    		���õ���ͬ����ʽ��ӳ�Ƚ���
		 */ 
    int setRecord(int nType,char *pInBuf,int nInLen);
		
		/** 
		 *	@brief	
		 *	�����ݿ��л������
		 *	@param nType 	Ҫ��ȡ�����ݱ�����
		 *	@param pOutBuf 	���������ָ��
		 *	@param nInLen 	��������ݳ���
		 *	@return    		��ȡ���ݽ�� 
		 */ 
    int getRecord(int nType,char *pOutBuf,int *nOutLen );
		
		/** 
		 *	@brief	
		 *	�������ݿ�����
		 *	@param nType 	Ҫ���µ�����
		 *	@param pInBuf 	���µ�����ָ��
		 *	@param nInLen 	���µ����ݳ���
		 *	@return    		�������ݽ�� 
		 */ 
    int updateRecord(int nType,char *pInBuf,int nInLen);
		
		/** 
		 *	@brief	
		 *	����IDɾ������
		 *	@param nType 	Ҫɾ��������
		 *	@return    		ɾ�����ݽ�� 
		 */ 
    int clearRecord(int nType);
		
		/** 
		 *	@brief	
		 *	�ж�nType�����Ƿ����
		 *	@param nType 	Ҫ�жϵ�����
		 *	@return    		ɾ�����ݽ�� 
		 */ 
    int isRecord(int nType);

public:

		///@brief
		///�û���Ϣ
    listUser* queryUser();
    void deletelistUser(listUser*param);
    int deleteUser(unsigned int nID);
	
		///@brief
		///���������Ϣ
    listNetParam* queryNetParam();
	int deleteNetParam(unsigned int nID);
    void deletelistNetParam(listNetParam*param);

private:
	
	CDbManager					m_CDbManager;
	CORE::Core_FastMutex		m_mutex;

};

#endif
