include ../../Makefile.param
include ../Makefile.param



TARGET      = hkipc_E
OBJPATH     = .
SOURCES     = $(wildcard *.c) 
OBJS        = $(patsubst %.c,%.o,$(SOURCES))
FULLOBJS    = $(patsubst %.c,$(OBJPATH)/%.o,$(SOURCES))
TARGETPATH  = /home/wuyuan

INCPATH     = -I . -I /home/wuyuan/include 			  \
			  -I ../../include 								  \
			  -I /home/wuyuan/Hi3518_SDK_V1.0.B.0/mpp/extdrv/tw2865 \
			  -I /home/wuyuan/lib_openssl/include \
			  -I /home/wuyuan/Hi3518_SDK_V1.0.B.0/drv/hisi-irda	  \
			  -I /home/wuyuan/wss_hi3518e_web/include
			  #-I /home/zqjun/Cloud/curl_arm/include \
			  #-I /home/zqjun/Cloud/ossc/include

LIBPATH     = -L ../lib_so -lsystem -lchinalink -lnetfactory -lutils 									\
			  -L ../../lib -lpthread -lm -lmpi -lVoiceEngine -laec -lresampler -lanr -lisp -lsns_ov9712 \
			  -L /home/wuyuan/lib_openssl/lib -lssl -lcrypto \
			  -L /home/wuyuan/wss_hi3518e_web/lib/LibSo -lrtsp -lOnvif
			
MODULES =  /home/wuyuan/wss_hi3518e_web/lib/MOD_NetSvRtsp.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetServer.a	\
		   /home/wuyuan/wss_hi3518e_web/lib/Mod_NetConfig.a	\
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetWebCallBack.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetSvStreamVideo.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetSvStreamAudio.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetClStreamAudio.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_NetDdns.a \
		   /home/wuyuan/wss_hi3518e_web/lib/LIB_Ddns.a \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_SysContext.a	\
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_Cgi.a	\
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_MulLanguage.a	\
		   /home/wuyuan/wss_hi3518e_web/lib/LIB_WebServer.a	 \
		   /home/wuyuan/wss_hi3518e_web/lib/MOD_OnvifServer.a \
		  /home/wuyuan/Hi3518_SDK_V1.0.B.0/mpp/sample/lib_so/libvoiceADC.a

LINKFLAGS   = -Wall -g
COMPFLAGS   = -c -O2 -fPIC -lpthread -D_GNU_SOURCE -D_HKIPC -DRTSARM
CXX         = arm-hisiv100nptl-linux-gcc


all:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(LINKFLAGS) $(FULLOBJS) -o $(TARGET) $(LIBPATH) $(MODULES)
	arm-hisiv100nptl-linux-strip $(TARGET)
	rm -f $(OBJPATH)/.*.swp
	rm -f $(OBJPATH)/*.o
	ls -lh $(TARGET)
	cp $(TARGET) $(TARGETPATH)/

$(OBJS):$(SOURCES)
	$(CXX) $(COMPFLAGS) $*.c -o $(OBJPATH)/$@ $(INCPATH)

clr:
	rm -f $(OBJPATH)/*.o
	ctags -Rn ./

clean:
	rm -f $(OBJPATH)/*.o
	rm -f $(OBJPATH)/.*.swp
	rm -f $(TARGET)
	rm -f $(TARGETPATH)/$(TARGET)
	ctags -Rn ./* ../../include/* /home/wuyuan/include /home/wuyuan/Hi3518_SDK_V1.0.B.0/mpp/component/isp/sensor/ov_9712+ .

