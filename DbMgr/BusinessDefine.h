//////////////////////////////////////////////////////////////////////////  
///     COPYRIGHT NOTICE  
///     Copyright (c) 2012,  
///     All rights reserved.  
///  
/// @file   BusinessDefine.h  
/// @brief 	定义业务数据，数据库需要的数据文件
///  
/// 
///  
/// @version 1.0	
/// @author	 jiongjiong
/// @date    2012年9月21日22:25:57
///  
///  
///     修订说明：最初版本  
//////////////////////////////////////////////////////////////////////////
#ifndef BusinessDefine_H
#define BusinessDefine_H


#define MAX_LEN 128

/**    数据库表的枚举定义   
  *    
  *    该枚举定义了数据库表类型\n   
  *    可以使用该枚举作为系统数据库不同的表之间的区别
  */
typedef enum DataBaseEnum
{
	E_User = 0,											/**< 枚举，用户表    */     
	E_NetParam ,											/**< 枚举，系统参数表    */       
} DBEnum;

///@brief
///用户参数
typedef struct  tag_User 
{
	unsigned int		nId;
	unsigned int		nUserid;
	char				sUserName[MAX_LEN];					/**< 结构体，登陆用户名    */     
	char				sPassword[MAX_LEN];					/**< 结构体，登陆用户密码    */     
	unsigned char		cUserState;							/**< 结构体，登陆用户状态    */     
	unsigned char		cUserPermission;					/**< 结构体，登陆用户权限    */     
	char				cEfficentTime[MAX_LEN];				/**< 结构体，登陆用户有效时间    */     
	int					nRecordState;			            /**< 结构体，0：删除 1：有效    */     //
}TUser;


///@brief
///网络参数
typedef struct  tag_netParam 
{
	unsigned int		nId;
	char				sLocalIp[MAX_LEN];
	char				sLocalDns[MAX_LEN];
	char				sLocalMark[MAX_LEN];
	char				sLocalBroadCast[MAX_LEN];
	char				sServerIP[MAX_LEN];
	int					nServerPort;
	int					nRecordState;			            //0：删除 1：有效
}TNetParam ;


#endif


