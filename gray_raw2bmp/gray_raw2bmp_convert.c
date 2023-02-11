#include <stdio.h>  
#include <stdlib.h>  
#include "HeadStruct.h"

// 그레이 RAW 파일을 그레이 비트맵 파일로 변환  
int Gray_Raw2Bmp(char* pRawName, DWORD nWidth, DWORD nHeight, char* pBmpName)
{
	BITMAPFILEHEADER  	file_h;
	BITMAPINFOHEADER  	info_h;
	DWORD             	dwBmpSize = 0;
	DWORD             	dwRawSize = 0;
	DWORD             	dwLine = 0;
	FILE				* in, * out;
	long              	lCount, i;
	char				* pData = NULL;
	RGBQUAD           	rgbPal[256]; // palette Color => 4개 = 4 * 256 = 1024

	//raw file 불러오기
	in = fopen(pRawName, "rb");
	if (!in)
	{
		printf("File Open Error!\n");
		return 0;
	}

	//저장할 bmp 파일 공간 확보 
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

	//힙영역에 크기 65552의 메모리 영역을 할당하고 그 시작주소값을 pData 에 반환
	pData = (char*)malloc(sizeof(char) * dwRawSize + 16);
	

	if (pData)
	{
		fread(pData, 1, dwRawSize, in);		


		for (i = 0; i < 256; i++)
		{
			rgbPal[i].rgbRed = (BYTE)(i % 256);
			rgbPal[i].rgbGreen = rgbPal[i].rgbRed;
			rgbPal[i].rgbBlue = rgbPal[i].rgbRed;
			rgbPal[i].rgbReserved = 0;
		}

		fwrite((char*)&file_h, 1, sizeof(BITMAPFILEHEADER), out); 	// 파일 헤드 작성
		fwrite((char*)&info_h, 1, sizeof(BITMAPINFOHEADER), out); 	// 영상 헤드 작성
		fwrite((char*)rgbPal, 1, sizeof(rgbPal), out); 				// 팔레트정보

		lCount = dwRawSize;

		for (lCount -= (long)info_h.biWidth; lCount >= 0; lCount -= (long)info_h.biWidth)
		{
			fwrite((pData + lCount), 1, (long)dwLine, out); //영상 데이터
		}

		free(pData); //pData의 해당 메모리 영역을 해제
		printf("complete\n");
	}

	fclose(in);
	fclose(out);

	return 1;
}

