// gray-scale 비트맵 영상 생성
#include <stdio.h>
#include <iostream>
using namespace std;
#include <Windows.h>
#define WIDTHBYTES(bits) (((bits) + 31) /32*4) // 4바이트의 배수여야 함
#define BYTE unsigned char
int main()
{
	
	int i, j;

	BITMAPFILEHEADER hf;	// "파일정보헤드" 변수선언
	BITMAPINFOHEADER hInfo;	// "영상정보헤드" 변수선언

	int rwsize = WIDTHBYTES(8 * 256);
	BYTE *OutImg = new BYTE[rwsize * 256];
	//	BYTE *GrayImg = new BYTE[rwsize * 256];
	BYTE bit[2][2] = { 0, 64, 192, 255 };
	

	// RGB 팔레트 세팅
	RGBQUAD hRGB[256] = { 0 };
	for (i = 0; i < 256; i++) {
		hRGB[i].rgbBlue = (BYTE) i;
		hRGB[i].rgbGreen = (BYTE) i;
		hRGB[i].rgbRed = (BYTE) i;
	}
	
	// 영상헤드 설정
	hInfo.biBitCount = 8;	// 흑백영상 = 8비트
	hInfo.biSizeImage = rwsize * 256;
	hInfo.biClrUsed = hInfo.biClrImportant = 0;
	hInfo.biSize = sizeof(BITMAPINFOHEADER);
	hInfo.biWidth = 256;
	hInfo.biHeight = 256;
	hInfo.biPlanes = 1;
	hInfo.biCompression = 0;
	hInfo.biXPelsPerMeter = 0;
	hInfo.biYPelsPerMeter = 0;

	// 파일헤드 설정
	hf.bfType = 0x4D42;
	hf.bfOffBits = sizeof(BITMAPINFOHEADER)+sizeof(BITMAPFILEHEADER)+sizeof(hRGB);
	cout << hf.bfOffBits;
	
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;

	// 비트연산자를 이용하여 gray-scale 영상 생성
	for (i = 0; i < hInfo.biHeight; i++) {
		for (j = 0; j < hInfo.biWidth; j++) {
			OutImg[i*hInfo.biWidth + j] = bit[hInfo.biHeight - i - 1 >> 7][j >> 7];
		}
	}

	

	
	/* 
	for (i = 0; i < hInfo.biHeight; i++) {
		for (j = 0; j < hInfo.biWidth; j++) {
			OutImg[i*hInfo.biWidth + j] = bit[i >> 7][j >>7];
		}
	}

	for (i = 0; i < hInfo.biHeight; i++) {
		for (j = 0; j < hInfo.biWidth; j++) {
			GrayImg[i*hInfo.biWidth + j] = OutImg[(hInfo.biHeight - i - 1) *rwsize + j];
		}
	}
	
	*/



	// 하드디스크에 영상데이터 쓰기
	FILE *outfile;
    fopen_s(&outfile, "sample_image.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	 fwrite(hRGB, sizeof(RGBQUAD), 256, outfile);
	fwrite(OutImg, sizeof(BYTE), hInfo.biSizeImage, outfile);
	fclose(outfile);
		
	delete OutImg;
	//	delete GrayImg;

	printf("The End\n");

	return 0;
}


