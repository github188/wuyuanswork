//IPCAM_Mjpeg.h
/*##############################################################################
#Project Description:
#      
#
# The File Description:
# 
# Authors:
#       Fifo2005@gmail.com                                       2011-08-25  Secend
#       Fifo2005@gmail.com                                       2011-08-24  First
#Copyright:
#       Copyright(c) 2008~200x 
#  	  Fifo2005@gmail All rights reserved.
###############################################################################*/

#include "IPCAM_Export.h"



#define MJPEG_STREAM 	1
#define MJPEG_SNAPSHOT  2


VOID MJPEG_HandleStream( INT socketed,INT Channel, INT GetType);

VOID MJPEG_Init(VOID);



