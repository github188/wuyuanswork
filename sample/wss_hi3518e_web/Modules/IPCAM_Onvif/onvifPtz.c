#if  1
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "IPCAM_Export.h"

#ifdef __cplusplus
};
#endif

extern int IsValidVideoSrcToken(CHAR *pToken);
int IsValidToken(CHAR *token, int tokentype);

BOOL PtzGetConfig (CHAR * PtzConfigToken,LPPTZCONFIG  lpPtzConfig)//?
{
	int ret=0;
	if (PtzConfigToken == NULL || lpPtzConfig == NULL)
    {
        return FALSE;
    }
	ret = IsValidToken(PtzConfigToken,3);
	if(ret<0)
		return FALSE;
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if (!strcmp(PtzConfigToken,"PtzConfigToken0")){
	
		strncpy(lpPtzConfig->PtzCfgName  ,"PtzConfigToken0",OVFCHARLENTH);
		strncpy(lpPtzConfig->PtzCfgToken ,"PtzConfigToken0",OVFCHARLENTH);  
		strncpy(lpPtzConfig->PtzCfgNodeToken,"onvif_ptz_0",OVFCHARLENTH);
		lpPtzConfig->PtzCfgUseCount  = 2;
		strncpy(lpPtzConfig->DefPTZTimeout,"PT3M",OVFCHARLENTH);
		
		strncpy(lpPtzConfig->DefAbsPantTiltPosSpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefAbsZoomPosSpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefRelativePanTiltTranslationSpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefRelativeZoomTranslationSpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefPTZSpeed.PanTilt.space,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefPTZSpeed.Zoom.space,"http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefContinuousPanTiltVelocitySpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",OVFBCHARLENTH);
		strncpy(lpPtzConfig->DefContinuousZoomVelocitySpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",OVFBCHARLENTH);

		strncpy(lpPtzConfig->LimitsPanTilt.Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
		lpPtzConfig->LimitsPanTilt.Space2dXRange.Max= 1;
		lpPtzConfig->LimitsPanTilt.Space2dXRange.Min=-1;
		lpPtzConfig->LimitsPanTilt.Space2dYRange.Max= 1;
		lpPtzConfig->LimitsPanTilt.Space2dYRange.Min=-1;
		
		strncpy(lpPtzConfig->LimitsZoom.Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
		lpPtzConfig->LimitsZoom.Space1XRange.Max= 1;
		lpPtzConfig->LimitsZoom.Space1XRange.Min=-1;
		
	}else
		return FALSE;
	
	return TRUE;
}
BOOL PtzSetConfig(CHAR * PtzConfigToken,LPPTZCONFIG    PtzConfig){//?
	int Ret			   =0;
	if (PtzConfigToken == NULL || PtzConfig == NULL)
    {
        return FALSE;
    }
	Ret=IsValidToken(PtzConfigToken,3);
	if( Ret < 0){
		return FALSE;
	}
	
	return TRUE;
}
BOOL PtzGetConfigs(LPPTZCONFIGS lpPtzConfigs)
{
	lpPtzConfigs->PtzCfgSize				= 1;
	strncpy(lpPtzConfigs->PtzCfgs[0].PtzCfgToken, "PtzConfigToken0", OVFCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].PtzCfgName , "PtzConfigToken0",OVFCHARLENTH);
	lpPtzConfigs->PtzCfgs[0].PtzCfgUseCount	= 2;
	strncpy(lpPtzConfigs->PtzCfgs[0].PtzCfgNodeToken,"onvif_ptz_0",OVFCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefPTZTimeout,"PT1M",OVFCHARLENTH);

	strncpy(lpPtzConfigs->PtzCfgs[0].DefAbsPantTiltPosSpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefAbsZoomPosSpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefRelativePanTiltTranslationSpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefRelativeZoomTranslationSpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.PanTilt.space,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.Zoom.space,"http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefContinuousPanTiltVelocitySpace,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigs->PtzCfgs[0].DefContinuousZoomVelocitySpace,"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	
	lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.PanTilt.x = 1;
	lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.PanTilt.y = 1;
	
	strncpy(lpPtzConfigs->PtzCfgs[0].LimitsPanTilt.Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
	lpPtzConfigs->PtzCfgs[0].LimitsPanTilt.Space2dXRange.Max=1;
	lpPtzConfigs->PtzCfgs[0].LimitsPanTilt.Space2dXRange.Min=-1;
	lpPtzConfigs->PtzCfgs[0].LimitsPanTilt.Space2dYRange.Max=1;
	lpPtzConfigs->PtzCfgs[0].LimitsPanTilt.Space2dYRange.Min=-1;

	strncpy(lpPtzConfigs->PtzCfgs[0].LimitsZoom.Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
	lpPtzConfigs->PtzCfgs[0].LimitsZoom.Space1XRange.Max=1;
	lpPtzConfigs->PtzCfgs[0].LimitsZoom.Space1XRange.Min=-1;

	//wss 20141022
	lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.PanTilt.x = 1;
	lpPtzConfigs->PtzCfgs[0].DefPTZSpeed.PanTilt.y = 1;
	
	return TRUE;
}

BOOL PtzGetNodes(LPPTZNODES lpPtzNodes){
	lpPtzNodes->NodeSize =1;
	lpPtzNodes->Nodes[0].AuxCommandsSize =1;
	lpPtzNodes->Nodes[0].MaxPresets      =255;
	strncpy(lpPtzNodes->Nodes[0].Nodetoken,"onvif_ptz_0",OVFCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodeName,"onvif_ptz_0",OVFCHARLENTH);
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeAbsolutePanTiltPositionSpace =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeAbsoluteZoomPositionSpace    =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeRelativePanTiltTranslationSpace=1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeRelativeZoomTranslationSpace   =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeContinuousPanTiltVelocitySpace =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeContinuousZoomVelocitySpace    =1;
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dDespURL , "http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.AbsoluteZoomPositionSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.RelativeZoomTranslationSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace",OVFBCHARLENTH);	
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.PanTiltSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.ZoomSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzNodes->Nodes[0].NodePTZSpaces.ContinuousZoomVelocitySpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",OVFBCHARLENTH);

	lpPtzNodes->Nodes[0].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange.Min =-1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange.Max =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange.Min =-1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange.Max =1;

	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeAbsoluteZoomPositionSpace =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizeZoomSpeedSpace    =1;
	lpPtzNodes->Nodes[0].NodePTZSpaces.SizePanTiltSpeedSpace =1;
	lpPtzNodes->Nodes[0].HomeSupported =1;
	return TRUE;

}

BOOL PtzGetNode(CHAR * PtzPtzNodeToken,LPPTZNODE PtzNode){
	int ret =0;
	if(NULL == PtzPtzNodeToken || NULL == PtzNode)
	{
		return FALSE;
	}
	ret =IsValidToken(PtzPtzNodeToken,6);
	if(ret<0)
		return FALSE;
	strncpy(PtzNode->Nodetoken,"onvif_ptz_0",OVFCHARLENTH);
	strncpy(PtzNode->NodeName,"onvif_ptz_0",OVFCHARLENTH);
	PtzNode->NodePTZSpaces.SizeAbsolutePanTiltPositionSpace =1;
	PtzNode->NodePTZSpaces.SizeAbsoluteZoomPositionSpace    =1;
	PtzNode->NodePTZSpaces.SizeContinuousPanTiltVelocitySpace=1;
	PtzNode->NodePTZSpaces.SizeContinuousZoomVelocitySpace   =1;
	PtzNode->NodePTZSpaces.SizeRelativePanTiltTranslationSpace=1;
	PtzNode->NodePTZSpaces.SizeRelativeZoomTranslationSpace=1;
	strncpy(PtzNode->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dDespURL , "http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.AbsoluteZoomPositionSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.RelativeZoomTranslationSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace",OVFBCHARLENTH);	
	strncpy(PtzNode->NodePTZSpaces.PanTiltSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.ZoomSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	strncpy(PtzNode->NodePTZSpaces.ContinuousZoomVelocitySpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	
	PtzNode->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange.Min =-1;
	PtzNode->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange.Max =1;
	PtzNode->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange.Min =-1;
	PtzNode->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange.Max =1;

	PtzNode->NodePTZSpaces.SizePanTiltSpeedSpace =1;
	PtzNode->NodePTZSpaces.SizeZoomSpeedSpace    =1;
	PtzNode->HomeSupported = 1;
	return TRUE;
}
BOOL PtzGetConfigOptions(LPPTZCONFIGOPTIONS lpPtzConfigOptions){
    if (lpPtzConfigOptions == NULL)
    {
        return FALSE;
    }
	lpPtzConfigOptions->Spaces.SizeAbsolutePanTiltPositionSpace =1;
	strncpy(lpPtzConfigOptions->Spaces.AbsolutePanTiltPositionSpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.AbsoluteZoomPositionSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.RelativePanTiltTranslationSpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.RelativeZoomTranslationSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace",OVFBCHARLENTH);	
	strncpy(lpPtzConfigOptions->Spaces.PanTiltSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.ZoomSpeedSpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/ZoomGenericSpeedSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.ContinuousPanTiltVelocitySpace->Space2dDespURL,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",OVFBCHARLENTH);
	strncpy(lpPtzConfigOptions->Spaces.ContinuousZoomVelocitySpace->Space1dURI,"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",OVFBCHARLENTH);

	lpPtzConfigOptions->Spaces.AbsolutePanTiltPositionSpace->Space2dXRange.Min =-1;
	lpPtzConfigOptions->Spaces.AbsolutePanTiltPositionSpace->Space2dXRange.Max =1;
	lpPtzConfigOptions->Spaces.AbsolutePanTiltPositionSpace->Space2dYRange.Min =-1;
	lpPtzConfigOptions->Spaces.AbsolutePanTiltPositionSpace->Space2dYRange.Max =1;

	lpPtzConfigOptions->Spaces.SizeAbsoluteZoomPositionSpace =1;
	lpPtzConfigOptions->Spaces.AbsoluteZoomPositionSpace->Space1XRange.Max=1;
	lpPtzConfigOptions->Spaces.AbsoluteZoomPositionSpace->Space1XRange.Min=-1;

	lpPtzConfigOptions->Spaces.SizeRelativePanTiltTranslationSpace =1;
	lpPtzConfigOptions->Spaces.RelativePanTiltTranslationSpace->Space2dXRange.Max=1;
	lpPtzConfigOptions->Spaces.RelativePanTiltTranslationSpace->Space2dXRange.Min=-1;
	lpPtzConfigOptions->Spaces.RelativePanTiltTranslationSpace->Space2dYRange.Max=1;
	lpPtzConfigOptions->Spaces.RelativePanTiltTranslationSpace->Space2dYRange.Min=-1;

	lpPtzConfigOptions->Spaces.SizePanTiltSpeedSpace   =1;
	lpPtzConfigOptions->Spaces.SizeZoomSpeedSpace      =1;
	
	lpPtzConfigOptions->Spaces.SizeRelativeZoomTranslationSpace =1;
	lpPtzConfigOptions->Spaces.RelativeZoomTranslationSpace->Space1XRange.Max=1;
	lpPtzConfigOptions->Spaces.RelativeZoomTranslationSpace->Space1XRange.Min=0;

	lpPtzConfigOptions->Spaces.SizeContinuousPanTiltVelocitySpace =1;
	lpPtzConfigOptions->Spaces.SizeContinuousZoomVelocitySpace    =1;
	lpPtzConfigOptions->PTZTimeout.Max				   =180;
	lpPtzConfigOptions->PTZTimeout.Min				   =30;
	return TRUE;
}
BOOL PtzGetStatus(CHAR * MediaProfileToken,LPPTZSTATUS lpPtzStatus){
	int ret =0;
	if(NULL == lpPtzStatus ||NULL== MediaProfileToken )
		return FALSE;
	ret = IsValidToken(MediaProfileToken,0);
	if(ret <0)
		return FALSE;
	lpPtzStatus->PanTilt  =PTZMOV_IDLE;
	lpPtzStatus->Zoom     =PTZMOV_IDLE;
	strncpy(lpPtzStatus->Position.PanTilt.space ,"http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace",OVFBCHARLENTH);
	return TRUE;
}

BOOL  PtzMovContinuous(CHAR * MediaProfileToken,LPPTZSPEED PtzSpeed,char *ptztimeOut){
	printf("PtzMovContinuous-------------1111\n");
	int ret =0;
	if(NULL== MediaProfileToken || NULL== PtzSpeed)
		return FALSE;
	ret = IsValidToken(MediaProfileToken,0);
	if(ret <0)
		return FALSE;
	
	printf("PtzMovContinuous-------------222\n");
	//NETMSGPACKET netPacket;
	//memset(&netPacket,0,sizeof(NETMSGPACKET));
	//netPacket.MsgPtzCommand.ptzcommand.channel = 0;
	if(NULL != &PtzSpeed->PanTilt){		
		printf("PtzMovContinuous-------------33333\n");
		
		printf("x=%d-------y=%d-----------\n",PtzSpeed->PanTilt.x,PtzSpeed->PanTilt.y);
		if(PtzSpeed->PanTilt.x>0 && PtzSpeed->PanTilt.y>0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_UP_START;
		{
			printf("ptz----------------------------RIGHT_UP_START\n");
		}
		if(PtzSpeed->PanTilt.x>0 && PtzSpeed->PanTilt.y<0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_DOWN_START;
		{
			printf("ptz----------------------------RIGHT_DOWN_START\n");
		}
		if(PtzSpeed->PanTilt.x<0 && PtzSpeed->PanTilt.y>0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_UP_START;
		{
			printf("ptz----------------------------RIGHT_UP_START\n");
		}
		if(PtzSpeed->PanTilt.x<0 && PtzSpeed->PanTilt.y<0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_DOWN_START;
		{
			printf("ptz----------------------------RIGHT_DOWN_START\n");
		}
		if(PtzSpeed->PanTilt.x<0 && PtzSpeed->PanTilt.y==0)//netPacket.MsgPtzCommand.ptzcommand.cmd = LEFT_START;
		{
			printf("ptz----------------------------LEFT_START\n");
		}
		if(PtzSpeed->PanTilt.x>0 && PtzSpeed->PanTilt.y==0)//netPacket.MsgPtzCommand.ptzcommand.cmd = RIGHT_START;
		{
			printf("ptz----------------------------RIGHT_START\n");
		}
		if(PtzSpeed->PanTilt.x==0&& PtzSpeed->PanTilt.y>0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = UP_START;
		{
			printf("ptz----------------------------UP_START\n");
		}
		if(PtzSpeed->PanTilt.x==0&& PtzSpeed->PanTilt.y<0)//netPacket.MsgPtzCommand.ptzcommand.cmd  = DOWN_START;
		{
			printf("ptz----------------------------DOWN_START\n");
		}
	}
	if(NULL != &PtzSpeed->Zoom){
		
		printf("PtzMovContinuous-------------44444\n");
		
		printf("PtzSpeed->Zoom.x=%d-------------44444\n",PtzSpeed->Zoom.x);
		if(PtzSpeed->Zoom.x>0)//netPacket.MsgPtzCommand.ptzcommand.cmd = RIGHT_START;
		{
			printf("Zoom----ptz----------------------------RIGHT_START\n");
		}
		if(PtzSpeed->Zoom.x<0)//netPacket.MsgPtzCommand.ptzcommand.cmd = LEFT_START;
		{
			printf("Zoom-----ptz----------------------------LEFT_START\n");
		}
	}
	//CallBackNetConfig(0,MSG_PTZWRITE_REQ,&netPacket);
	return TRUE;
}

BOOL  PtzMovRelative(CHAR * MediaProfileToken,LPPTZVECTOR lpPosition   ,LPPTZSPEED  PtzSpeed){
	int ret =0;
	if(NULL == lpPosition ||NULL== MediaProfileToken || NULL== PtzSpeed)
		return FALSE;
	ret = IsValidToken(MediaProfileToken,0);
	if(ret <0)
		return FALSE;
	//NETMSGPACKET netPacket;
	//memset(&netPacket,0,sizeof(NETMSGPACKET));
	//netPacket.MsgPtzCommand.ptzcommand.channel = 0;
	if(NULL != &lpPosition->PanTilt){
	#if 0
		if(lpPosition->PanTilt.x>0 && lpPosition->PanTilt.y>0)netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_UP_START;
		if(lpPosition->PanTilt.x>0 && lpPosition->PanTilt.y<0)netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_DOWN_START;
		if(lpPosition->PanTilt.x<0 && lpPosition->PanTilt.y>0)netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_UP_START;
		if(lpPosition->PanTilt.x<0 && lpPosition->PanTilt.y<0)netPacket.MsgPtzCommand.ptzcommand.cmd  = RIGHT_DOWN_START;
		if(lpPosition->PanTilt.x<0 && lpPosition->PanTilt.y==0)netPacket.MsgPtzCommand.ptzcommand.cmd = LEFT_START;
		if(lpPosition->PanTilt.x>0 && lpPosition->PanTilt.y==0)netPacket.MsgPtzCommand.ptzcommand.cmd = RIGHT_START;
		if(lpPosition->PanTilt.x==0&& lpPosition->PanTilt.y>0)netPacket.MsgPtzCommand.ptzcommand.cmd  = UP_START;
		if(lpPosition->PanTilt.x==0&& lpPosition->PanTilt.y<0)netPacket.MsgPtzCommand.ptzcommand.cmd  = DOWN_START;
	#endif
	}
	if(NULL != &lpPosition->Zoom){
		//if(lpPosition->Zoom.x>0)netPacket.MsgPtzCommand.ptzcommand.cmd = RIGHT_START;
		//if(lpPosition->Zoom.x<0)netPacket.MsgPtzCommand.ptzcommand.cmd = LEFT_START;
	}
	//CallBackNetConfig(0,MSG_PTZWRITE_REQ,&netPacket);
	return TRUE;
}
BOOL    PtzMovAbsolute(CHAR * MediaProfileToken,LPPTZVECTOR lpTranslation,LPPTZSPEED  PtzSpeed){
	int ret=0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret = IsValidToken(MediaProfileToken,0);
	if (lpTranslation->PanTilt.x >1 || lpTranslation->PanTilt.x <-1 || lpTranslation->PanTilt.y >1|| lpTranslation->PanTilt.y<-1)
	{
		return FALSE;
	}
	if(ret<0)
		return FALSE;
	return TRUE;
}

BOOL  PtzStop(CHAR * MediaProfileToken,BOOL IsStopPanTilt,BOOL IsStopRoom){
	int ret =0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret=IsValidToken(MediaProfileToken,0);
	if(ret<0)
		return FALSE;
	
	if(IsStopPanTilt){
		//NETMSGPACKET netPacket;
		//memset(&netPacket,0,sizeof(NETMSGPACKET));
		//netPacket.MsgPtzCommand.ptzcommand.channel = 0;
		//netPacket.MsgPtzCommand.ptzcommand.cmd     = PTZ_STOP;
		//CallBackNetConfig(0,MSG_PTZWRITE_REQ,&netPacket);
	}
	return TRUE;
}

BOOL    PtzGetPresets(CHAR * MediaProfileToken,LPPTZPRESETS lpPtzPresets){
	int ret =0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret=IsValidToken(MediaProfileToken,0);
	if(ret<0)
		return FALSE;
	lpPtzPresets->PresetSize =1;
 	strncpy(lpPtzPresets->Presets->PresetName ,"preset0",OVFCHARLENTH);
 	strncpy(lpPtzPresets->Presets->PresetToken,"preset0",OVFCHARLENTH);
	return TRUE;
}
BOOL	PtzSetPreset(CHAR * MediaProfileToken,CHAR *PresetToken,CHAR *PresetName){
	int ret=0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret = IsValidToken(MediaProfileToken,0);
	if(ret<0)
		return FALSE;
	//NETMSGPACKET netPacket;
	//memset(&netPacket,0,sizeof(NETMSGPACKET));
	//netPacket.MsgPtzCommand.ptzcommand.channel = 0;
	//netPacket.MsgPtzCommand.ptzcommand.cmd     = SET_POINT;
	//CallBackNetConfig(0,MSG_PTZWRITE_REQ,&netPacket);
	return TRUE;
}
BOOL    PtzGotoPreset(CHAR * MediaProfileToken,CHAR *PresetToken,LPPTZSPEED   PtzSpeed){
	int ret=0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret = IsValidToken(MediaProfileToken,0);
	return TRUE;
}
BOOL    PtzSetHomePosition(CHAR * MediaProfileToken){
	int ret=0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret = IsValidToken(MediaProfileToken,0);
	if(ret<0)return FALSE;
	return TRUE;
}
BOOL    PtzGotoHomePosition(CHAR * MediaProfileToken,LPPTZSPEED  PtzSpeed){
	int ret=0;
	if (NULL == MediaProfileToken)
	{
		return FALSE;
	}
	ret = IsValidToken(MediaProfileToken,0);
	return TRUE;
}

CALLBACKPTZ    g_CallBackPtz = {0};

VOID InitCallBackPtz()
{
    g_CallBackPtz.PtzGetConfig  =PtzGetConfig;
	g_CallBackPtz.PtzSetConfig  =PtzSetConfig;
	g_CallBackPtz.PtzGetConfigs =PtzGetConfigs;
	g_CallBackPtz.PtzGetNodes	=PtzGetNodes;
	g_CallBackPtz.PtzGetNode	=PtzGetNode;
	g_CallBackPtz.PtzGetConfigOptions=PtzGetConfigOptions;
	g_CallBackPtz.PtzGetStatus  =PtzGetStatus;
	g_CallBackPtz.PtzMovRelative   =PtzMovRelative;
	g_CallBackPtz.PtzMovAbsolute=PtzMovAbsolute;
	g_CallBackPtz.PtzMovContinuous = PtzMovContinuous;
	g_CallBackPtz.PtzStop       =PtzStop;
	g_CallBackPtz.PtzGetPresets =PtzGetPresets;
	g_CallBackPtz.PtzSetPreset  =PtzSetPreset;
	g_CallBackPtz.PtzGotoPreset =PtzGotoPreset;
	g_CallBackPtz.PtzGotoHomePosition=PtzGotoHomePosition;
	g_CallBackPtz.PtzSetHomePosition =PtzSetHomePosition;
	
}
#endif
