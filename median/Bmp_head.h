#ifndef HEADSTRUCT_H
#define HEADSTRUCT_H

#include <stdint.h>

#ifndef BI_RGB  
#define BI_RGB         0  
#endif  

typedef __uint16_t 	WORD;
typedef __uint32_t  DWORD;
typedef __uint32_t  LONG;
typedef __uint8_t  	BYTE;

//file head
typedef struct tagBITMAPFILEHEADER
{
	WORD   bfType; 			//2
	DWORD  bfSize; 			//4 파일의 전체 크기(단위 : Byte)
	WORD   bfReserved1; 	//2 x
	WORD   bfReserved2;		//2 x
	DWORD  bfOffBits;		//4 Image까지 거리
}__attribute__((aligned(2),packed)) BITMAPFILEHEADER ;

//image head
typedef struct tagBITMAPINFOHEADER
{
	DWORD   biSize;			 //4 헤더(구조체) 크기
	LONG    biWidth;		 //4 image 폭(단위 : bit)
	LONG    biHeight;		 //4 image 폭(단위 : bit)
	WORD    biPlanes;		 //2 항상 1
	WORD    biBitCount;		 //2 pixel 당 bit 수
	DWORD   biCompression;	 //4 압축 여부
	DWORD   biSizeImage;	 //4 image size(Byte)
	LONG    biXPelsPerMeter; //4 가로 해상도
	LONG    biYPelsPerMeter; //4 세로 해상도
	DWORD   biClrUsed;		 //4 사용되는 색상 수
	DWORD   biClrImportant;	 //4 중요 색상 인덱스
}__attribute__((aligned(2),packed)) BITMAPINFOHEADER;

//Palette (8bit 표현이라 사용)
typedef struct tagRGBQUAD
{
	//unsigned char(1바이트)  1 Color : 8bit 색상 표현
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}__attribute__((aligned(2),packed)) RGBQUAD;

#endif