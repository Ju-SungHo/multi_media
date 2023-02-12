#include "main.h"

int Filter_blurring256(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD             dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image_256[256][256];
	BYTE				image_256ex1[258][258];
	BYTE				image_256ex2[260][260];
	BYTE				image_256final[256][256];
	double				blurring_maskcase1[3][3] = { 1,1,1,1,1,1,1,1,1 };
	double				blurring_maskgaussian[3][3] = { 1,2,1,2,4,2,1,2,1 };
	double				blurring_maskcase2[5][5] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	double				sum = 0;
	double				result = 0;

	in = fopen(CallFileName, "rb");
	if (in == NULL)
	{
		printf("File Open Error!\n");
		return 0;
	}
	out = fopen(MakeFileName, "wb");
	fread(&file_h.bfType, 1, sizeof(file_h.bfType), in);
	fread(&file_h.bfSize, 1, sizeof(file_h.bfSize), in);
	fread(&file_h.bfReserved1, 1, sizeof(file_h.bfReserved1), in);
	fread(&file_h.bfReserved2, 1, sizeof(file_h.bfReserved2), in);
	fread(&file_h.bfOffBits, 1, sizeof(file_h.bfOffBits), in);
	dataSize = nHeight * nWidth;
	info_h.biSize = sizeof(BITMAPINFOHEADER);
	info_h.biWidth = (DWORD)nWidth;
	info_h.biHeight = (DWORD)nHeight;
	info_h.biPlanes = 1; //plane의 갯수 = 1개
	info_h.biBitCount = 8; // 이미지 bit depth
	info_h.biCompression = BI_RGB;
	info_h.biXPelsPerMeter = 0;
	info_h.biYPelsPerMeter = 0;
	info_h.biClrUsed = 0;
	info_h.biClrImportant = 0;
	info_h.biSizeImage = dataSize;
	file_h.bfSize = dataSize + file_h.bfOffBits + 2;

	seekSize = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	xData = (char*)malloc(sizeof(char) * file_h.bfOffBits);

	if (xData)
	{
		fseek(in, 0, SEEK_SET);
		fread(xData, 1, seekSize, in);
		fseek(in, seekSize, SEEK_SET);
		fread(image_256, 1, dataSize, in);
		if (MaskType == 1 || MaskType == 3)
		{
			for (i = 0; i < info_h.biHeight + 2; i++)
			{
				for (j = 0; j < info_h.biWidth + 2; j++)
				{
					image_256ex1[i][j] = 0;
				}
			}
			for (i = 0; i < info_h.biHeight; i++)
			{
				for (j = 0; j < info_h.biWidth; j++)
				{
					image_256ex1[i + 1][j + 1] = image_256[i][j];
				}
			}

			for (i = 1; i <= info_h.biHeight; i++)
			{
				for (j = 1; j <= info_h.biWidth; j++)
				{
					sum = 0;
					result = 0;

					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (MaskType == 1)
								sum += image_256ex1[(i - 1) + m][(j - 1) + n] * blurring_maskcase1[m][n];
							else if (MaskType == 3)
								sum += image_256ex1[(i - 1) + m][(j - 1) + n] * blurring_maskgaussian[m][n];
						}
					}
					if (MaskType == 1)
						result = sum / 9;
					else if (MaskType == 3)
						result = sum / 16;

					if (result > 255)
						image_256final[i - 1][j - 1] = 255;
					else if (result < 0)
						image_256final[i - 1][j - 1] = abs((int)result);
					else
						image_256final[i - 1][j - 1] = (int)(result + 0.5);
				}
			}
		}
		else if (MaskType == 2)
		{
			for (i = 0; i < info_h.biHeight + 4; i++)
			{
				for (j = 0; j < info_h.biWidth + 4; j++)
				{
					image_256ex2[i][j] = 0;
				}
			}
			for (i = 0; i < info_h.biHeight; i++)
			{
				for (j = 0; j < info_h.biWidth; j++)
				{
					image_256ex2[i + 2][j + 2] = image_256[i][j];
				}
			}
			for (i = 2; i <= info_h.biHeight + 1; i++)
			{
				for (j = 2; j <= info_h.biWidth + 1; j++)
				{
					sum = 0;
					result = 0;

					for (m = 0; m < 5; m++)
					{
						for (n = 0; n < 5; n++)
						{
							sum += image_256ex2[(i - 1) + m][(j - 1) + n] * blurring_maskcase2[m][n];
						}
					}
					result = sum / 25;

					if (result > 255)
						image_256final[i - 2][j - 2] = 255;
					else if (result < 0)
						image_256final[i - 2][j - 2] = abs((int)result);
					else
						image_256final[i - 2][j - 2] = (int)(result + 0.5);
				}
			}
		}
		fseek(out, 0, SEEK_SET);
		fwrite(xData, 1, seekSize, out);
		fwrite(image_256final, 1, dataSize, out);

		free(xData);
		printf("BMP 파일 변환 성공\n  ");
	}
	fclose(in);
	fclose(out);

	return 1;
}


int Filter_blurring512(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long			  i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image_512[512][512];
	BYTE				image_512ex1[514][514];
	BYTE				image_512ex2[516][516];
	double				blurring_maskcase1[3][3] = { 1,1,1,1,1,1,1,1,1 };
	double				blurring_maskgaussian[3][3] = { 1,2,1,2,4,2,1,2,1 };
	double				blurring_maskcase2[5][5] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	double				sum = 0;
	double				result = 0;

	in = fopen(CallFileName, "rb");
	if (in == NULL)
	{
		printf("File Open Error!\n");
		return 0;
	}
	out = fopen(MakeFileName, "wb");
	fread(&file_h.bfType, 1, sizeof(file_h.bfType), in);
	fread(&file_h.bfSize, 1, sizeof(file_h.bfSize), in);
	fread(&file_h.bfReserved1, 1, sizeof(file_h.bfReserved1), in);
	fread(&file_h.bfReserved2, 1, sizeof(file_h.bfReserved2), in);
	fread(&file_h.bfOffBits, 1, sizeof(file_h.bfOffBits), in);

	info_h.biSize = sizeof(BITMAPINFOHEADER);
	info_h.biWidth = (DWORD)nWidth;
	info_h.biHeight = (DWORD)nHeight;
	info_h.biPlanes = 1; //plane의 갯수 = 1개
	info_h.biBitCount = 8; // 이미지 bit depth
	info_h.biCompression = BI_RGB;
	info_h.biXPelsPerMeter = 0;
	info_h.biYPelsPerMeter = 0;
	info_h.biClrUsed = 0;
	info_h.biClrImportant = 0;
	info_h.biSizeImage = dataSize;
	file_h.bfSize = dataSize + file_h.bfOffBits + 2;
	dataSize = info_h.biWidth * info_h.biHeight;

	seekSize = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	xData = (char*)malloc(sizeof(char) * file_h.bfOffBits);

	if (xData)
	{
		fseek(in, 0, SEEK_SET);
		fread(xData, 1, seekSize, in);
		fseek(in, seekSize, SEEK_SET);
		fread(image_512, 1, dataSize, in);
		if (MaskType == 1 || MaskType == 3)
		{
			for (i = 0; i < info_h.biHeight + 2; i++)
			{
				for (j = 0; j < info_h.biWidth + 2; j++)
				{
					image_512ex1[i][j] = 0;
				}
			}
			for (i = 0; i < info_h.biHeight; i++)
			{
				for (j = 0; j < info_h.biWidth; j++)
				{
					image_512ex1[i + 1][j + 1] = image_512[i][j];
				}
			}

			for (i = 1; i <= info_h.biHeight; i++)
			{
				for (j = 1; j <= info_h.biWidth; j++)
				{
					sum = 0;
					result = 0;

					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (MaskType == 1)
								sum += image_512ex1[(i - 1) + m][(j - 1) + n] * blurring_maskcase1[m][n];
							else if (MaskType == 3)
								sum += image_512ex1[(i - 1) + m][(j - 1) + n] * blurring_maskgaussian[m][n];
						}
					}
					if (MaskType == 1)
						result = sum / 9;
					else if (MaskType == 3)
						result = sum / 16;

					if (result > 255)
						image_512[i - 1][j - 1] = 255;
					else if (result < 0)
						image_512[i - 1][j - 1] = abs((int)result);
					else
						image_512[i - 1][j - 1] = (int)(result + 0.5);
				}
			}
		}
		else if (MaskType == 2)
		{
			for (i = 0; i < info_h.biHeight + 4; i++)
			{
				for (j = 0; j < info_h.biWidth + 4; j++)
				{
					image_512ex2[i][j] = 0;
				}
			}
			for (i = 0; i < info_h.biHeight; i++)
			{
				for (j = 0; j < info_h.biWidth; j++)
				{
					image_512ex2[i + 2][j + 2] = image_512[i][j];
				}
			}
			for (i = 2; i <= info_h.biHeight + 1; i++)
			{
				for (j = 2; j <= info_h.biWidth + 1; j++)
				{
					sum = 0;
					result = 0;

					for (m = 0; m < 5; m++)
					{
						for (n = 0; n < 5; n++)
						{
							sum += image_512ex2[(i - 2) + m][(j - 2) + n] * blurring_maskcase2[m][n];
						}
					}
					result = sum / 25;

					if (result > 255)
						image_512[i - 2][j - 2] = 255;
					else if (result < 0)
						image_512[i - 2][j - 2] = abs((int)result);
					else
						image_512[i - 2][j - 2] = (int)(result + 0.5);
				}

			}
		}
		fseek(out, 0, SEEK_SET);
		fwrite(xData, 1, seekSize, out);
		fwrite(image_512, 1, dataSize, out);

		free(xData);
		printf("BMP 파일 변환 성공\n  ");
	}
	fclose(in);
	fclose(out);

	return 1;
}