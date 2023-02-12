#include "main.h"

int main()
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD  nWidth, nHeight;
	char callFileName[80];
	char MakeFileName[80];
	int MaskType;
	int FilterType;
	FILE* in, * out;
	char Filenamerr;

	printf("1 : Blurring \n2 : Sharpening\nFilter Type : ");
	scanf("%d", &FilterType);
	fflush(stdin);

	if (FilterType == 1)
		printf("1 : Mask3x3 \n2 : Mask5x5 \n3 : GaussianMask \nInPut MaskType : ");
	else if (FilterType == 2)
		printf("1 : case1 \n2 : case2 \n3 : case3 \n4 : HPF \n5 : HPF+128\nInPut MaskType : ");

	scanf("%d", &MaskType);
	fflush(stdin);


	printf("Call File Name : ");
	scanf("%s",callFileName);
	fflush(stdin);

	printf("Make File Name : ");
	scanf("%s",MakeFileName);
	fflush(stdin);
	
	Filenamerr = strcmp(callFileName, MakeFileName);
	if (!Filenamerr)
	{
		printf("\nChange MakeFile Name\n");
		return 0;
	}


	in = fopen(callFileName, "rb");
	if (in == NULL)
	{
		printf("File Open Error!\n");
		return 0;
	}

	out = fopen(MakeFileName, "wb");
	fseek(in, 18, SEEK_SET);
	fread(&info_h.biWidth, 1, 4, in);
	fread(&info_h.biHeight, 1, 4, in);

	nWidth = info_h.biWidth;
	nHeight = info_h.biHeight;
	fclose(in);
	fclose(out);

	if (FilterType == 1)
	{
		if (info_h.biWidth == 256)
			Filter_blurring256(callFileName, nWidth, nHeight, MakeFileName, MaskType);
		else if (info_h.biWidth == 512)
			Filter_blurring512(callFileName, nWidth, nHeight, MakeFileName, MaskType);
	}
	else if (FilterType == 2)
	{
		if (info_h.biWidth == 256)
			Filter_sharpening256(callFileName, nWidth, nHeight, MakeFileName, MaskType);
		else if(info_h.biWidth == 512)
			Filter_sharpening512(callFileName, nWidth, nHeight, MakeFileName, MaskType);
	}

	return 0;
}