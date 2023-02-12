#include "main.h"

int Filter_sharpening512(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           	rgbPal[256]; // 1바이트 4개 = 4바이트 * 256 = 1024
	BYTE				image[512][512];
	BYTE				image_ex[514][514];
	BYTE				image_final[512][512];
	double				sharping_maskcase1[3][3] = { 0,-1,0,-1,5,-1,0,-1,0 };
	double				sharping_maskcase2[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
	double				sharping_maskcase3[3][3] = { 1,-2,1,-2,5,-2,1,-2,1 };
	double				sharping_maskHPF[3][3] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
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
	info_h.biSize = sizeof(BITMAPINFOHEADER);// 구조체의 크기
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
		fread(image, 1, dataSize, in);
		sum = 0;
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
				switch (MaskType)
				{
				case 1:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase1[m][n];
						}
					}
					result = sum;
					break;
				case 2:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase2[m][n];
						}
					}
					result = sum;
					break;
				case 3:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase3[m][n];
						}
					}
					result = sum;
					break;
				case 4:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskHPF[m][n];
						}
					}
					result = sum / 9;
					break;
				case 5:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskHPF[m][n];
						}
					}
					result = sum / 9 + 128;
					break;
				default:
					break;
				}



				if (result > 255)
					image_final[i - 1][j - 1] = 255;
				else if (result < 0)
					image_final[i - 1][j - 1] = abs((int)result);
				else
					image_final[i - 1][j - 1] = (int)(result + 0.5);

			}
		}

		fseek(out, 0, SEEK_SET);
		fwrite(xData, 1, seekSize, out); //헤더 작성
		fwrite(image_final, 1, dataSize, out);
		free(xData); //pData의 용무가 끝나면 해당 메모리 영역을 해제
		printf("BMP 파일 변환 성공\n  ");
	}
	else
		printf("BMP 파일 변환 실패 코드확인하세요 \n");
	fclose(in);
	fclose(out);

	return 1;
}

int Filter_sharpening256(char* CallFileName, DWORD nWidth, DWORD nHeight, char* MakeFileName, int MaskType)
{
	BITMAPFILEHEADER  file_h;
	BITMAPINFOHEADER  info_h;
	DWORD			  dataSize = 0;
	DWORD			  seekSize = 0;
	long              i, j, m, n;
	FILE* in, * out;
	char* xData = NULL;
	RGBQUAD           rgbPal[256]; // 1바이트 4개 = 4바이트 * 256 = 1024
	BYTE				image[256][256];
	BYTE				image_ex[258][258];
	BYTE				image_final[256][256];
	double				sharping_maskcase1[3][3] = { 0,-1,0,-1,5,-1,0,-1,0 };
	double				sharping_maskcase2[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
	double				sharping_maskcase3[3][3] = { 1,-2,1,-2,5,-2,1,-2,1 };
	double				sharping_maskHPF[3][3] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
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
	info_h.biSize = sizeof(BITMAPINFOHEADER);// 구조체의 크기
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


	//fread(저장할 변수,사이즈,반복횟수,읽은 파일 포인터);
	//fwrite(쓸 문자열의 주소 , 문자열 사이즈, 반복 횟수,쓸 파일)
	//문자열 사이즈 * 반복 횟수 만큼 파일에 써진다.
	seekSize = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	xData = (char*)malloc(sizeof(char) * file_h.bfOffBits);

	if (xData)
	{
		fseek(in, 0, SEEK_SET);
		fread(xData, 1, seekSize, in);
		fseek(in, seekSize, SEEK_SET);
		fread(image, 1, dataSize, in);
		sum = 0;
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
				switch (MaskType)
				{
				case 1:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase1[m][n];
						}
					}
					result = sum;
					break;
				case 2:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase2[m][n];
						}
					}
					result = sum;
					break;
				case 3:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskcase3[m][n];
						}
					}
					result = sum;
					break;
				case 4:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskHPF[m][n];
						}
					}
					result = sum / 9;
					break;
				case 5:
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							sum += image_ex[(i - 1) + m][(j - 1) + n] * sharping_maskHPF[m][n];
						}
					}
					result = sum / 9 + 128;
					break;
				default:
					break;
				}



				if (result > 255)
					image_final[i - 1][j - 1] = 255;
				else if (result < 0)
					image_final[i - 1][j - 1] = abs((int)result);
				else
					image_final[i - 1][j - 1] = (int)(result + 0.5);

			}
		}

		fseek(out, 0, SEEK_SET);
		fwrite(xData, 1, seekSize, out); //헤더 작성
		fwrite(image_final, 1, dataSize, out);
		free(xData); //pData의 용무가 끝나면 해당 메모리 영역을 해제
		printf("BMP 파일 변환 성공\n  ");
	}
	else
		printf("BMP 파일 변환 실패 코드확인하세요 \n");
	fclose(in);
	fclose(out);

	return 1;
}
