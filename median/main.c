#include "main.h"

int main()
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD  nWidth, nHeight;
	//char CallFileName[80];
	char MakeFileName[80];
	int MaskType;
	FILE* in, * out;

	//printf("Call File Name : ");
	//gets(CallFileName);
	//fflush(stdin);

	printf("Make File Name : ");
	scanf("%s",MakeFileName);
	fflush(stdin);

	printf("1 : 3by3 Median Filter \n2 : 5by5 Median Filter \n3 : 3by3 Gaussian Filter\n4 : 5by5 Gaussian Filter\nFilter Type : ");
	scanf("%d", &MaskType);
	fflush(stdin);

	in = fopen("akiyo_noise.bmp", "rb");
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

	if(MaskType == 1)
		Median_3by3("akiyo_noise.bmp", nWidth, nHeight, MakeFileName, MaskType);//(1) =CallFileName 
	else if(MaskType ==2)
		Median_5by5("akiyo_noise.bmp", nWidth, nHeight, MakeFileName, MaskType);//(1) =CallFileName 
	else if(MaskType == 3)
		Gaussian_3by3_filter("akiyo_noise.bmp", nWidth, nHeight, MakeFileName, MaskType);
	else
		Gaussian_5by5_filter("akiyo_noise.bmp", nWidth, nHeight, MakeFileName, MaskType);

	return 0;
}