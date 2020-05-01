// gray scale 영상 생성

#include <stdio.h>

int main()
{
	int i, j;
	unsigned char OrgImg[256][256];
	unsigned char bit[2][2] = { 0, 64, 192, 255 };

	// 비트연산자를 이용하여 gray-scale 영상 생성
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			OrgImg[i][j] = bit[i >> 7][j >> 7];
		}
	}


	// 하드디스크에 영상데이터 쓰기
	FILE *outfile;
    fopen_s(&outfile, "sample_image.raw", "wb");
	fwrite(OrgImg, sizeof(unsigned char), 256 * 256, outfile);
	fclose(outfile);

	
}

