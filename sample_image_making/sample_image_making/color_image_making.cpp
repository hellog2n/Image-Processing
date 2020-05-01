 // 4분할 트루컬러 raw 이미지 생성

#include <stdio.h>
#include <Windows.h>
#define BYTE unsigned char
#define WIDTHBYTES(bits) (((bits) + 31) / 32*4) // 4바이트 배수로 변환
int main()
{
	int i, j; 
	// 256*256의 트루컬러 배열 생성
	int rwsize = WIDTHBYTES(24 * 256);
		BYTE *lpOutImg = new BYTE[rwsize * 256];

		// 4분할로 컬러 생성
		for(i = 0; i<128; i++) 
		{
			for(j=0; j<128; j++)
			{
				// RED 출력
				lpOutImg[i*rwsize + 3 * j + 2] = 0; // BLUE
				lpOutImg[i*rwsize + 3 * j + 1] = 0;	// GREEN
				lpOutImg[i*rwsize + 3 * j ] = 255; // RED

				// GREEN 출력
				lpOutImg[i*rwsize + 3 * (255 - j) + 2] = 0; // BLUE
				lpOutImg[i*rwsize + 3 * (255 - j) + 1] = 255;	// GREEN
				lpOutImg[i*rwsize + 3 * (255 - j)] = 0; // RED

				// BLUE 출력
				lpOutImg[(255 - i) *rwsize + 3 * j + 2] = 255; // BLUE
				lpOutImg[(255 - i)*rwsize + 3 * j + 1] = 0;	// GREEN
				lpOutImg[(255 - i)*rwsize + 3 * j] = 0; // RED

				// BLACK 출력
				lpOutImg[(255 - i)*rwsize + 3 * (255 - j) + 2] = 0; // BLUE
				lpOutImg[(255 - i)*rwsize + 3 * (255 - j) + 1] = 0;	// GREEN
				lpOutImg[(255 - i)*rwsize + 3 * (255 - j)] = 0; // RED
			}
			
		
			
			 
		}



	// 하드디스크에 영상데이터 쓰기
	FILE *outfile;
    fopen_s(&outfile, "sample_color_image.raw", "wb");
	fwrite(lpOutImg, sizeof(unsigned char), rwsize * 256, outfile);
	fclose(outfile);

	delete[]lpOutImg;
}


