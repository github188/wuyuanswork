#ifndef __FILESYSTEM_H_
#define __FILESYSTEM_H_

#include <stdio.h>
#include <stdlib.h>

#define REMOTEFILEPATH "/mnt/sif/remoteID.txt"
#define WRITETOTAIL    "a+"
#define READFROMHEAD   "r"

void readString(const char *path , char *operateType,int len,char *cpyStr);
void insertString(const char *path , char *operateType,char *string);
void setupAFile(const char *path);

#endif