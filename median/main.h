#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>
#include "Bmp_head.h"

#ifndef BI_RGB  
#define BI_RGB         0  
#endif  

int Median_3by3(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Median_5by5(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Gaussian_3by3_filter(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);
int Gaussian_5by5_filter(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType);


#endif