//
//  main.c
//  file_test
//
//  Created by 徐悟源 on 16/4/7.
//  Copyright © 2016年 徐悟源. All rights reserved.
//

#include "filesystem.h"

/**
 "r" 打开，只读；
 "w" 打开，文件指针指到头，只写； 
 "a" 打开，指向文件尾，在已存在文件中追加； 
 "rb" 打开一个二进制文件，只读； 
 "wb" 打开一个二进制文件，只写； 
 "ab" 打开一个二进制文件，进行追加 ；
 "r+" 以读/写方式打开一个已存在的文件； 
 "w+" 以读/写方式建立一个新的文本文件 ；
 "a+" 以读/写方式打开一个文件文件进行追加 ；
 "rb+" 以读/写方式打开一个二进制文件； 
 "wb+" 以读/写方式建立一个新的二进制文件 ；
 "ab+" 以读/写方式打开一个二进制文件进行追加 ；
 */

void readString(const char *path , char *operateType,int len,char *cpyStr)
{
    FILE *fp;
    
    if((fp = fopen(path, operateType)) == NULL)
    {
        printf("read file open failed \r\n");
        return;
    }
    
    fgets(cpyStr, len, fp);
    
    fclose(fp);
}

void insertString(const char *path , char *operateType,char *string)
{
    // 写模式，打开文件
    FILE *fp;
    if((fp = fopen(path, operateType)) == NULL)
    {
        printf("insert file open failed \r\n");
        return;
    }
    
    fputs(string, fp);
    
    fclose(fp);
    
}

void setupAFile(const char *path)
{
    FILE *fp;
    
    // 打开文件，如果没有在创建一个
    if((fp = fopen(path, "r+")) == NULL)
    {
        if((fp = fopen(path, "w+")) == NULL)
        {
            printf("setup file failed");
            return;
        }
    }
    
    fclose(fp);
}


