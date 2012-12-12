//////////////////////////////////////////////////////////////////////////  
///     COPYRIGHT NOTICE  
///     Copyright (c) 2012,  
///     All rights reserved.  
///  
/// @file   BusinessDefine.h  
/// @brief 	����ҵ�����ݣ����ݿ���Ҫ�������ļ�
///  
/// 
///  
/// @version 1.0	
/// @author	 jiongjiong
/// @date    2012��9��21��22:25:57
///  
///  
///     �޶�˵��������汾  
//////////////////////////////////////////////////////////////////////////
#ifndef BusinessDefine_H
#define BusinessDefine_H


#define MAX_LEN 128

/**    ���ݿ���ö�ٶ���   
  *    
  *    ��ö�ٶ��������ݿ������\n   
  *    ����ʹ�ø�ö����Ϊϵͳ���ݿⲻͬ�ı�֮�������
  */
typedef enum DataBaseEnum
{
	E_User = 0,											/**< ö�٣��û���    */     
	E_NetParam ,											/**< ö�٣�ϵͳ������    */       
} DBEnum;

///@brief
///�û�����
typedef struct  tag_User 
{
	unsigned int		nId;
	unsigned int		nUserid;
	char				sUserName[MAX_LEN];					/**< �ṹ�壬��½�û���    */     
	char				sPassword[MAX_LEN];					/**< �ṹ�壬��½�û�����    */     
	unsigned char		cUserState;							/**< �ṹ�壬��½�û�״̬    */     
	unsigned char		cUserPermission;					/**< �ṹ�壬��½�û�Ȩ��    */     
	char				cEfficentTime[MAX_LEN];				/**< �ṹ�壬��½�û���Чʱ��    */     
	int					nRecordState;			            /**< �ṹ�壬0��ɾ�� 1����Ч    */     //
}TUser;


///@brief
///�������
typedef struct  tag_netParam 
{
	unsigned int		nId;
	char				sLocalIp[MAX_LEN];
	char				sLocalDns[MAX_LEN];
	char				sLocalMark[MAX_LEN];
	char				sLocalBroadCast[MAX_LEN];
	char				sServerIP[MAX_LEN];
	int					nServerPort;
	int					nRecordState;			            //0��ɾ�� 1����Ч
}TNetParam ;


#endif


