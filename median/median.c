#include "main.h"


int Median_3by3(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image[288][352];
	BYTE				image_ex[290][354];
	BYTE				image_final[288][352];
	BYTE				image_sort[9];
	BYTE				tmp = 0;
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
	info_h.biPlanes = 1;
	info_h.biBitCount = 8;
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
		fread(image, 1, dataSize, in);

		for (i = 0; i < info_h.biHeight + 2; i++)
		{
			for (j = 0; j < info_h.biWidth + 2; j++)
			{
				image_ex[i][j] = 0;
			}
		}

		for (i = 0; i < info_h.biHeight; i++)
		{
			for (j = 0; j < info_h.biWidth; j++)
			{
				image_ex[i + 1][j + 1] = image[i][j];
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
						image_sort[m * 3 + n] = image_ex[(i - 1) + m][(j - 1) + n];
					}
				}

				for (m = 1; m < 9; m++)
				{
					for (n = 0; n < 8; n++)
					{
						if (image_sort[n] > image_sort[n + 1])
						{
							tmp = image_sort[n + 1];
							image_sort[n + 1] = image_sort[n];
							image_sort[n] = tmp;
						}
					}
				}
				image_final[i - 1][j - 1] = image_sort[4];
			}
		}

	}
	fseek(out, 0, SEEK_SET);
	fwrite(xData, 1, seekSize, out);
	fwrite(image_final, 1, dataSize, out);

	free(xData);
	printf("BMP 파일 변환 성공\n  ");
	
	fclose(in);
	fclose(out);

	return 1;

}
int Median_5by5(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image[288][352];
	BYTE				image_ex[292][356];
	BYTE				image_final[288][352];
	BYTE				image_sort[25];
	BYTE				tmp = 0;
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
	info_h.biPlanes = 1;
	info_h.biBitCount = 8;
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
		fread(image, 1, dataSize, in);

		for (i = 0; i < info_h.biHeight + 4; i++)
		{
			for (j = 0; j < info_h.biWidth + 4; j++)
			{
				image_ex[i][j] = 0;
			}
		}

		for (i = 0; i < info_h.biHeight; i++)
		{
			for (j = 0; j < info_h.biWidth; j++)
			{
				image_ex[i + 1][j + 1] = image[i][j];
			}
		}

		for (i = 1; i <= info_h.biHeight; i++)
		{
			for (j = 1; j <= info_h.biWidth; j++)
			{
				sum = 0;
				result = 0;
				for (m = 0; m < 5; m++)
				{
					for (n = 0; n < 5; n++)
					{
						image_sort[m * 5 + n] = image_ex[(i - 1) + m][(j - 1) + n];
					}
				}

				for (m = 1; m < 25; m++)
				{
					for (n = 0; n < 24; n++)
					{
						if (image_sort[n] > image_sort[n + 1])
						{
							tmp = image_sort[n + 1];
							image_sort[n + 1] = image_sort[n];
							image_sort[n] = tmp;
						}
					}
				}
				image_final[i - 1][j - 1] = image_sort[12];
			}
		}

	}
	fseek(out, 0, SEEK_SET);
	fwrite(xData, 1, seekSize, out);
	fwrite(image_final, 1, dataSize, out);

	free(xData);
	printf("BMP 파일 변환 성공\n  ");

	fclose(in);
	fclose(out);

	return 1;
}
int Gaussian_3by3_filter(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{

	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image[288][352];
	BYTE				image_ex[290][354];
	BYTE				image_final[288][352];
	BYTE				tmp = 0;
	double				Blurring_GaussianMask[3][3] = { 1,2,1,2,4,2,1,2,1 };
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
	info_h.biPlanes = 1;
	info_h.biBitCount = 8;
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
		fread(image, 1, dataSize, in);

		for (i = 0; i < info_h.biHeight + 2; i++)
		{
			for (j = 0; j < info_h.biWidth + 2; j++)
			{
				image_ex[i][j] = 0;
			}
		}
		for (i = 0; i < info_h.biHeight; i++)
		{
			for (j = 0; j < info_h.biWidth; j++)
			{
				image_ex[i + 1][j + 1] = image[i][j];
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
						sum += image_ex[(i - 1) + m][(j - 1) + n] * Blurring_GaussianMask[m][n];
					}
				}
				result = sum / 16;
				if (result > 255)
					image_final[i - 1][j - 1] = 255;
				else
					image_final[i - 1][j - 1] = (int)(result + 0.5);
			}

		}

	}

	fseek(out, 0, SEEK_SET);
	fwrite(xData, 1, seekSize, out);
	fwrite(image_final, 1, dataSize, out);

	free(xData);
	printf("BMP 파일 변환 성공\n  ");
	
	fclose(in);
	fclose(out);

	return 1;
}
int Gaussian_5by5_filter(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{

	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256];
	BYTE				image[288][352];
	BYTE				image_ex[292][356];
	BYTE				image_final[288][352];
	BYTE				tmp = 0;
	double				Blurring_GaussianMask[5][5] = { 1,4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1 };
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
	info_h.biPlanes = 1;
	info_h.biBitCount = 8;
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
		fread(image, 1, dataSize, in);

		for (i = 0; i < info_h.biHeight + 4; i++)
		{
			for (j = 0; j < info_h.biWidth + 4; j++)
			{
				image_ex[i][j] = 0;
			}
		}
		for (i = 0; i < info_h.biHeight; i++)
		{
			for (j = 0; j < info_h.biWidth; j++)
			{
				image_ex[i + 1][j + 1] = image[i][j];
			}
		}

		for (i = 1; i <= info_h.biHeight; i++)
		{
			for (j = 1; j <= info_h.biWidth; j++)
			{
				sum = 0;
				result = 0;

				for (m = 0; m < 5; m++)
				{
					for (n = 0; n < 5; n++)
					{
						sum += image_ex[(i - 1) + m][(j - 1) + n] * Blurring_GaussianMask[m][n];
					}
				}
				result = sum / 273;
				if (result > 255)
					image_final[i - 1][j - 1] = 255;
				else
					image_final[i - 1][j - 1] = (int)(result + 0.5);
			}

		}

	}

	fseek(out, 0, SEEK_SET);
	fwrite(xData, 1, seekSize, out);
	fwrite(image_final, 1, dataSize, out);

	free(xData);
	printf("BMP 파일 변환 성공\n  ");

	fclose(in);
	fclose(out);

	return 1;
}