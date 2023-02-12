#include <stdio.h>  
#include <stdlib.h> 
#include "Bmp_head.h"

int Gray_Bmp_Histo_Eq(char* pRawName, DWORD nWidth, DWORD nHeight, char* pBmpName);

int main()
{
	char szRawName[80] = { "map.bmp" };
	char szBmpName[80] = { "map_change.bmp" };
	DWORD  nWidth, nHeight;
	nWidth = 512;
	nHeight = 512;
	Gray_Bmp_Histo_Eq(szRawName, nWidth, nHeight, szBmpName);
	return 0;
}