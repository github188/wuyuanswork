#pragma  once
#include "utils/HKDataBase.h"
#define AFX_EXT_CLASS
#ifdef __cplusplus
extern "C"
{
#endif
AFX_EXT_CLASS int				NetOpen();		
AFX_EXT_CLASS void				NetClose();

AFX_EXT_CLASS int				InitWAN( HKNETCALLBACK funCallBack );	// 初始化 广域网
AFX_EXT_CLASS void				UnInitWAN();							// 注销广域网

//  将要被替换 ----
AFX_EXT_CLASS int				NetInit( HKNETCALLBACK funCallBack );              // 打开本地服务。
AFX_EXT_CLASS void				NetUnInit();
AFX_EXT_CLASS int				NetBindPipe( unsigned int nPIPEID );			  // 绑定对方管道
AFX_EXT_CLASS int				NetUnBindPipe( unsigned int nPIPEID );			      // 解除绑定

//-----------------

AFX_EXT_CLASS int				AddLocalHostInfo( HKHOSTInfo *rHostInfo );                                // 添加本地监听
AFX_EXT_CLASS int				ConRemoteHostInfo( HKHOSTInfo *rHostInfo );                  // 连接远程服务器           															          
AFX_EXT_CLASS int				NetWrite( const HKPacketInfo *rPackInfo,char *pData,unsigned short nSize );    


AFX_EXT_CLASS int				NewPipe( unsigned int nPipeID );	  // 新建通道
AFX_EXT_CLASS void              DelPipe( unsigned int nPipeID );

///////----------------------小网接口

AFX_EXT_CLASS int			    InitLAN( HKLANNETCALLBACK lanCallBack );			// 初始化小网
AFX_EXT_CLASS void			    UnInitLAN();
AFX_EXT_CLASS short				AddLANEP( char * szIP, unsigned short nPort );			// 添加远程EP
AFX_EXT_CLASS void				RemLANEP( unsigned short nDstID );						// 删除远程EP
AFX_EXT_CLASS int				LANNetWrite( unsigned short nDstID,const HKPacketInfo *rPackInfo,char *pData,unsigned short nSize );               // nCHID = 0 SYS通道
AFX_EXT_CLASS short				GetLANEPNodeInfo( unsigned short nDstID,char *buf,short nLen );
AFX_EXT_CLASS int               LANConRemoteHostInfo( unsigned short nDstID );                    //Huqing 06-17 小网连接

AFX_EXT_CLASS void              LANReFlash( char *pBuf,unsigned short nLen );            //Huqing 06-20 小网刷新接口

AFX_EXT_CLASS void              SetMonPortInfoList( char *pBuf, unsigned short nLen );  //Huqing 10-23 增加监听端口信息列表
#ifdef __cplusplus
}
#endif

