#include <stdio.h>  
#include <stdlib.h>  
#include "HeadStruct.h"

int Gray_Raw2Bmp(char* pRawName, DWORD nWidth, DWORD nHeight, char* pBmpName);

int main()
{
	char szRawName[80];
	char szBmpName[80];
	DWORD  nWidth, nHeight; //부호없는 long 형

	printf("Enter the name of RAW File to be converted (ex)Name.raw \n:");
	scanf("%[^\n]%*c",szRawName);
	fflush(stdin);

	printf("Enter the name of BMP File to save (ex)Name.bmp \n:");
	scanf("%[^\n]%*c",szBmpName);
	fflush(stdin);

	printf("Enter the Raw file's Width & Height (ex)256 256 \n:");
	scanf("%u %u", &nWidth, &nHeight);

	Gray_Raw2Bmp(szRawName, nWidth, nHeight, szBmpName);

	return 0;
}