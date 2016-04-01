#ifndef _IPCAM_MULLANG_H
#define _IPCAM_MULLANG_H

#define  MUL_LENGHT          256
typedef struct tagLANGHANDLE{
	FILE *fd;
	CHAR Content[MUL_LENGHT];
}LANGHANDLE, *LPLANGHANDLE;

LPLANGHANDLE MUL_CreateHandle  (CHAR *Path);
BOOL         MUL_DelHandle     (LPLANGHANDLE pHandle);
CHAR *       MUL_GetContent    (LPLANGHANDLE pHandle, CHAR *Key, INT Size);
INT          MUL_GetSameKeySize(LPLANGHANDLE pHandle, CHAR *Key);

#endif 
//IPCAM_MULLANG_H

