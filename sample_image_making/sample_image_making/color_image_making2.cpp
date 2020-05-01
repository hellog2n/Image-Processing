// (2) 4분할 가로로 쭉 color 비트맵 영상 생성 <트루컬러로>_2020
//

#include <stdio.h>
#include <Windows.h>
#define BYTE unsigned char
#define WIDTHBYTES(bits) (((bits) + 31) / 32*4) // 4바이트 배수로 변환
int main()
{
	int i, j;
	int rwsize = WIDTHBYTES(24 * 256);

	// "파일 정보헤드" 변수 선언
	BITMAPFILEHEADER hf;
	// "영상정보헤드" 변수 선언
	BITMAPINFOHEADER hInfo;

	// 256*256의 트루컬러 배열 생성
	BYTE *lpOutImg = new BYTE[rwsize * 256];

	// 영상헤드 설정
	hInfo.biBitCount = 24;
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
	hf.bfOffBits = 54;  // 팔레트가 없으므로 파일의 시작부에서 영상데이터까지의 오프셋은 고정크기임.
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;



	for (j = 0; j < 256; j++) {
		for (i = 0; i < 64; i++) {
			// RED 출력 
			lpOutImg[i*rwsize + 3 * j + 2] = 255; //  R
			lpOutImg[i*rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[i*rwsize + 3 * j] =0; //  B

			// GREEN 출력 
			lpOutImg[(i+ 64)*rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 64)*rwsize + 3 * j + 1] = 255;	//  G
			lpOutImg[(i + 64)*rwsize + 3 * j] = 0; //  B

			// BLUE 출력 
			lpOutImg[(i+128)*rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 128)*rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[(i + 128)*rwsize + 3 * j] = 255; //  B
		
			// BLACK 출력 
			lpOutImg[(i+192)*rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 192)*rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[(i + 192)*rwsize + 3 * j] = 0; //  B
		}
	}





	// 하드디스크에 영상데이터 쓰기
	FILE *outfile;
    fopen_s(&outfile, "sample_color_image2.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(lpOutImg, sizeof(BYTE), hInfo.biSizeImage, outfile);
	fclose(outfile);

	delete lpOutImg;

	printf("The End\n");

	return 0;

}


