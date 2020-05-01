#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits)  (((bits) + 31) / 32*4)  // 영상 가로줄은 4바이트의 배수
#define BYTE unsigned char



int main()
{

	FILE* infile;
	 fopen_s(&infile, "talent.bmp", "rb");

	// 입력할 파일을 오픈
	if (infile == NULL) { printf("There is no file!! \n"); exit(1); }


	// BMP 헤드정보의 입력
	BITMAPFILEHEADER hf;

	// "파일정보헤드" 변수 선언
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile); // 파일정보헤드 읽음
	if (hf.bfType != 0x4D42) exit(1); // 파일 타입이 "BM" (0x4D42) 인지 검사

	BITMAPINFOHEADER hInfo; // "영상정보헤드" 변수 선언
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile); //영상정보헤드 읽음
	printf("Image Size: (%3dx%3d)\n", hInfo.biWidth, hInfo.biHeight);
	printf("Pallete Type: %dbit Colors\n", hInfo.biBitCount);

	// 8비트 흑백 영상만 처리
	if (hInfo.biBitCount != 8) { printf("Bad File format!!"); exit(1); }

	RGBQUAD hRGB[256];
	fread(hRGB, sizeof(RGBQUAD), 256, infile); // 팔레트를 파일에서 읽음

	// 영상데이터를 저장할 메모리 할당
	BYTE* lpImg = new BYTE[hInfo.biSizeImage];
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	// 역상의 이미지 구하기
	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	for (int i = 0; i < hInfo.biHeight; i++)
	{
		for (int j = 0; j < hInfo.biWidth; j++)
		{
			lpImg[i * rwsize + j] = 255 - lpImg[i * rwsize + j];
		}
	}
	// 영상 출력
	FILE* outfile;
	fopen_s(&outfile, "OutImg.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(hRGB, sizeof(RGBQUAD), 256, outfile);
	fwrite(lpImg, sizeof(char), hInfo.biSizeImage, outfile);
	fclose(outfile);

	// 메모리 해제
	delete[] lpImg;




}

