#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <math.h>
#include "Bmp_head.h"

int Filter_blurring256(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Filter_blurring512(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Filter_sharpening512(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Filter_sharpening256(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);


#endif