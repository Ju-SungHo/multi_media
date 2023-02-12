#include <stdio.h>  
#include <stdlib.h> 
#include "Bmp_head.h"

int Gray_Bmp_Histo_Eq(char* pRawName, DWORD nWidth, DWORD nHeight, char* pBmpName)
{
	BITMAPFILEHEADER  	file_h;
	BITMAPINFOHEADER  	info_h;
	DWORD             	dwBmpSize = 0;
	DWORD             	dwRawSize = 0;
	DWORD			  	seekSize = 0;
	DWORD             	dwLine = 0;
	RGBQUAD           	rgbPal[256]; // 1바이트 4개 = 4바이트 * 256 = 1024
	BYTE				image[512 * 512];

	int					value[256], sum;
	double				LUV_double[256];
	int					LUV[256];
	long              	lCount, i, j;
	char				* pData = NULL;
	char				* xData = NULL;

	FILE* in, * out;
	
	in = fopen(pRawName, "rb");
	if (!in)
	{
		printf("File Open Error!\n");
		return 0;
	}

	out = fopen(pBmpName, "wb");

	file_h.bfType = 0x4D42; //ASCII 'BM' 글자저장 (Littel Endian)
	file_h.bfReserved1 = 0;
	file_h.bfReserved2 = 0;
	file_h.bfOffBits = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 모든 헤더가 지난 후 data 시작
	info_h.biSize = sizeof(BITMAPINFOHEADER);// 구조체의 크기 => 40
	info_h.biWidth = (DWORD)nWidth; // 사진의 너비 = 256
	info_h.biHeight = (DWORD)nHeight; //사진의 높이 = 256
	info_h.biPlanes = 1; //색상판의 수 
	info_h.biBitCount = 8; // 1Pixel당 bit 수 => Grayscale = 8bit
	info_h.biCompression = BI_RGB; // 압축방식 => bmp는 보통 압축 x 
	info_h.biXPelsPerMeter = 0; //가로 해상도 
	info_h.biYPelsPerMeter = 0; // 세로 해상도 
	info_h.biClrUsed = 0; //테이블에서 실제 사용 색상 수 
	info_h.biClrImportant = 0;

	dwLine = info_h.biWidth * (info_h.biBitCount>>3); 	// biwidth * bibitcount[byte] = = 256;
	dwBmpSize = dwLine * info_h.biHeight; 				// bmp image data Size Lena.raw=> 256 * 256 = 65536

	info_h.biSizeImage = dwBmpSize; 					//pixel data 크기 = 65536
	file_h.bfSize = dwBmpSize + file_h.bfOffBits; 	// 65536 + 1078 + 2 = 66616;
	dwRawSize = info_h.biWidth * info_h.biHeight; 		// 65536

	seekSize = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	xData = (char*)malloc(sizeof(char) * file_h.bfOffBits);

	if (xData)
	{
		fread(xData, 1, seekSize, in); //헤더 데이터 읽고 xDATA에 저장
		fseek(in, seekSize, SEEK_SET); // offset 옮기기
		fread(image, 1, dwRawSize, in); // 영상 데이터의 각 픽셀값(8bit)을 배열에 저장
		fwrite(xData, 1, seekSize, out); //output file에 헤더 작성

		
		for (i = 0; i < 256; i++)
			value[i] = 0;
		for (i = 0; i < (nHeight*nWidth); i++)
		{
			for (j = 0; j < 256; j++)
			{
				if (image[i] == j)
					value[j]++;
			}
		}

		sum = 0;
		for (i = 0; i < 256; i++)
		{
			sum += value[i];
			LUV_double[i] = (float)255 * sum / (nHeight*nWidth) + 0.5;
			LUV[i] = (int)LUV_double[i];
		}
		for (i = 0; i < (nHeight*nWidth); i++)
		{
			for (j = 0; j < 256; j++)
				if (image[i] == j)
				{
					image[i] = LUV[j];
					break;
				}
		}

		fwrite(image, 1, dwRawSize, out);
		free(pData); //pData의 용무가 끝나면 해당 메모리 영역을 해제
		free(xData);
		printf("complete\n  ");
	}
	fclose(in);
	fclose(out);

	return 1;
}
