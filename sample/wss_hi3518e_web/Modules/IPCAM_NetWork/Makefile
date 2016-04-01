###############################################################################
# 编译说明:
#     CT IPCM 软件系统基本编译文件。编译系统由一组编译文件组成，各模块或扩展库
#     有自己的编译方式和目标，可单独编译也可综合编译。所以编译文件使用工程根目
#     录的config.local 作为编译环境的导入文件，本次编译环境为arm-gcc-3.6 ,linux
#     版本为2.6.14 .
#
# 文件描述:
# 
# 文件编写:
#       Fifo2005@gmail.com                              2011-04-01  第二次修改
#       Fifo2005@gmail.com                              2008-09-10  第一次编写
# 版权信息:
#       Copyright(c) 2008~201x
#  	Fifo2005@gmail All rights reserved.
###############################################################################
MAKE=make
include ../../config.local
LIB_TARGET = LIB_NetWork.a

#OBJS_a=lib/LIB_NetConfig.a\
#	lib/LIB_NetSend.a\
#	lib/LIB_NetRecord.a\
#	lib/LIB_NetPlayback.a

OBJS_o=obj/*.o

all:
	$(MAKE) -C IPCAM_NetConfig all
	$(MAKE) -C IPCAM_NetSend all
	$(MAKE) -C IPCAM_NetRecord all
	$(MAKE) -C IPCAM_NetPlayback all
	$(MAKE) -C IPCAM_NetDdns all
	$(MAKE) -C IPCAM_NetVideo all
	$(MAKE) -C IPCAM_NetServer all
	$(MAKE) -C IPCAM_NetNtp all
	$(MAKE) -C IPCAM_NetMjpeg all
	$(MAKE) -C IPCAM_NetDevUpdate all
	
	$(AR) -cru $(LIB_TARGET) $(OBJS_o)
	ranlib $(LIB_TARGET)
	
	$(CP) $(LIB_TARGET) lib/
	$(CP) $(LIB_TARGET) ../../lib/	
clean:
	$(MAKE) -C IPCAM_NetConfig clean
	$(MAKE) -C IPCAM_NetSend clean
	$(MAKE) -C IPCAM_NetRecord clean
	$(MAKE) -C IPCAM_NetPlayback clean
	$(MAKE) -C IPCAM_NetDdns clean
	$(MAKE) -C IPCAM_NetVideo clean
	$(MAKE) -C IPCAM_NetServer clean
	$(MAKE) -C IPCAM_NetNtp clean
	$(MAKE) -C IPCAM_Mjpeg clean
	$(MAKE) -C IPCAM_NetDevUpate clean
	rm -rf lib/*.* $(LIB_TARGET) $(OBJS_o) ../../lib/$(LIB_TARGET)



