#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <linux/commdev.h>

typedef struct Object {

	struct RSObject RSObject;
	
	char type;
	char name;
	char flag;
	char state;
	int pinCount;

} Dobject;

typedef struct Video {

	struct Object Dobject;
	char video;	
	
	char EncodeType;
	char DecodeType;
	char Format;
	int Brightness;
	int Hue;
	int Effect;
	int Saturation;
	int Exposure;
	int Sharpness;
	int VinFrameRate;
	int VoutFramerate;
	int IFrameRate;
	int Resolution;

	int( *SetVideoAttValue)(const char* att, int Value);
	int( *GetVideoAttValue)(const char* att);

} video;

typedef struct VBVideo {
	
	video hkVideo;
	
	char vbVideo;	
	char NpMode;
	char VscMode;
	int MotionFrameRate;
	int DisplayMode;
	int AnalogEncodeMode;
	int FlipMirror;
	int LightingMode;
	int DividedImageEncodeMode;
	int CBR;
	int VBR;
	int Dispaly;
	int bandWidth;
	int maxQuality;
	int minQuality;

} vbVideo;

typedef struct Radio {
	
	struct AUDIO_CODEC tAUDIO_CODEC;
	struct DEVICE_INFO tDEVICE_INFO;
	
	char radio;
	
	char format;
	int direction;
	int channel;
	int volume;
	int outVol;		
	short deviceType;
	short channelNum;
	int enMethod;
	int audioCodec;
	int playTone;
	int ledOff;
	int ledOn;
	int ledWink;
	int silence;
	
	int ( *SetAudioAttValue)(const char* att, int Value);
	int ( *GetAudioAttValue)(const char* att);

} radio ;

typedef struct VbRadio {
	
	radio hkRadio;
	char hkradio;

}vbRadio;

typedef struct Control {
    
	char Contol;
	
	char protocol;
	int turnRight;
	int turnLeft;
	int turnUp;
	int turnDown;
	int focus;
	int scan;
	int visualAngle;
	int Verticalspeed;
	int Parallelspeed;
	int flip;
	int Aperture ;
	int ToZero;
	int ToPreset;
	int ClearPreset;
	int SetPreset;
	char *FileList;

	int ( *SetControlAttValue)(const char* att, int Value);
	int ( *GetControlAttValue)(const char* att);

} control;

typedef struct VBControl {
	
	 control vbControl;
	 char vbcontrol;
	
} vbControl;

//static void VideoInit() {
//
//	struct Video video;
//	struct VBVideo vbVideo;
//
//	vbVideo.video.Brightness = 4;
//	vbVideo.video.Effect = 4;
//	vbVideo.video.Saturation = 4;
//	vbVideo.video.Hue = 4;
//	vbVideo.video.Sharpness = 4;
//	vbVideo.video.Exposure = 4;
//
//	vbVideo.video.VinFrameRate = 12;
//	vbVideo.video.VoutFramerate =12;
//	vbVideo.video.IFrameRate =100;
//
//	vbVideo.video.EncodeType = MPEG4;
//	vbVideo.video.DecodeType = MPEG4;
//	vbVideo.video.Format = CIF;
//	vbVideo.video.Resolution = CIF;

//	vbVideo.NpMode = NTSC;
//	vbVideo.DividedImageEncodeMode = 0;
//	vbVideo.LightingMode =0;
//	vbVideo.AnalogEncodeMode = 1;
//	vbVideo.MotionFrameRate = 25;
//	vbVideo.VBR = 31;
//}


