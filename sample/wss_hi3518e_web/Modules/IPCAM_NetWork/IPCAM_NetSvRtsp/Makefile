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
#       Fifo2005@gmail.com                              2011-08-30  第三次修改
#       Fifo2005@gmail.com                              2011-08-01  第二次修改
#       Fifo2005@gmail.com                              2008-09-10  第一次编写
# 版权信息:
#       Copyright(c) 2008~201x
#  	Fifo2005@gmail All rights reserved.
###############################################################################

include 	../../../config.local

LIB_TARGET = MOD_NetSvRtsp.a

OBJS = IPCAM_NetSvRtsp.o
INC = -I ../../../include 

all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJS)
	$(AR) -rc $(LIB_TARGET) $(OBJS) 
	$(CP) $(OBJS) ../obj/
	$(STRIP) $(LIB_TARGET)
	$(CP) $(LIB_TARGET) ../lib/
	$(CP) $(LIB_TARGET) ../../../$(LIBDIR)/
	ranlib $(LIB_TARGET)


%.o: %.c
	$(CC) ${INC}  -c  $< -o $@
clean:
	rm -f *.o
	rm -f $(LIB_TARGET)
	rm -rf ../../../$(LIBDIR)/$(LIB_TARGET)



