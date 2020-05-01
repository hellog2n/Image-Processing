
#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits) + 31) / 32*4) // 4바이트의 배수여야 함
#define BYTE unsigned char




int main()
{
	FILE *infile;
	fopen_s(&infile, "pshop256.bmp", "rb");
	if (infile == NULL) { printf("There is no file!!!\n"); }

	BITMAPFILEHEADER hf;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile); // 파일헤드를 읽음
	if (hf.bfType != 0x4D42) exit(1);

	BITMAPINFOHEADER hInfo;
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile); // 영상 헤드를 읽음

	// 256 컬러 이하의 경우는 취급하지 않음
	if (hInfo.biBitCount < 8) { printf("Bad file format!"); return -1; }

	RGBQUAD *pRGB = NULL;
	if (hInfo.biClrUsed != 0) // 팔레트가 있는 경우
	{
		pRGB = new RGBQUAD[hInfo.biClrUsed]; // 팔레트의 크기만큼 메모리를 할당함
		fread(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, infile); // 팔레트를 파일에서 읽음

	}

	// 영상데이터를 저장할 메모리 할당
	BYTE * lpImg = new BYTE[hInfo.biSizeImage];
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	// 크기계산, 메모리 할당
	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	int rwsize2 = WIDTHBYTES(24 * hInfo.biWidth);
	BYTE *lpOutImg = new BYTE[rwsize2*hInfo.biHeight];
	int index, R, G, B, i, j;

	if(hInfo.biBitCount == 24)  // 만일 입력영상이 트루(24비트) 컬러인 경우는 팔레트 없음
		for (i = 0; i < hInfo.biHeight; i++) // 역상 이미지 구하기
		{
			for(j = 0; j < hInfo.biWidth; j++)
			{ // 팔레트가 없으므로 영상데이터가 바로 컬러값
				lpOutImg[i*rwsize2 + 3 * j + 2] = 255 - lpImg[i*rwsize + 3 * j + 2];
				lpOutImg[i*rwsize2 + 3 * j + 1] = 255 - lpImg[i*rwsize + 3 * j + 1];
				lpOutImg[i*rwsize2 + 3 * j ] = 255 - lpImg[i*rwsize + 3 * j ];
			}
		}
	else// 트루 컬러가 아닌 경우는 팔레트가 있음

		for (i = 0; i < hInfo.biHeight; i++) // 역상 이미지 구하기
		{
			for (j = 0; j < hInfo.biWidth; j++)
			{
				index = lpImg[i*rwsize + j]; // 영상데이터는 팔레트의 인덱스임
				R = pRGB[index].rgbRed; //팔레트에서 실제 영상데이터를 가져옴(R)
				G = pRGB[index].rgbGreen; // G
				B = pRGB[index].rgbBlue; // B
				R = 255 - R; G = 255 - G; B = 255 - B; // 역상을 계산함.
				lpOutImg[i*rwsize2 + 3 * j + 2] = (BYTE)R;
				lpOutImg[i*rwsize2 + 3 * j + 1] = (BYTE)G;
				lpOutImg[i*rwsize2 + 3 * j ] = (BYTE)B;

			}
		}

	// 계산된 역상 이미지를 하드 디스크에 출력 (24비트인 트루컬러로 출력)
	hInfo.biBitCount = 24;
	hInfo.biSizeImage = rwsize2 * hInfo.biHeight;
	hInfo.biClrUsed = hInfo.biClrImportant = 0;
	hf.bfOffBits = 54; // 팔레트가 없으므로 파일의 시작부에서
	// 영상데이터까지의 오프셋은 고정 크기임.
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;

	FILE *outfile;
	fopen_s(&outfile, "OutImg24.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hInfo.biHeight, outfile);
	fclose(outfile);

	// 메모리 해제
	if (hInfo.biClrUsed != 0) delete[]pRGB;
	delete []lpOutImg;
	delete []lpImg;


}


