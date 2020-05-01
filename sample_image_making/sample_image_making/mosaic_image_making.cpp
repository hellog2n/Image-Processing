// Lenna 이미지를 받아와서 모자이크 출력

#include <iostream>




int main()
{
	int i, j;
	unsigned char OrgImg[256][256];
	unsigned char Mosaic[256][256];
	int temp[32][32] = { 0 };

	// 파일 오픈
	FILE *infile;
    fopen_s(&infile, "Lenna.raw", "rb");

	// 파일 에러 처리
	if (infile == NULL) {
		printf("File open error!!"); return -1;
	}
	// 파일 읽기
	fread(OrgImg, sizeof(char), 256 * 256, infile);
	fclose(infile);

	// 원본이미지의 8*8 화소 평균값 구해서 temp 배열에 삽입
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			temp[i >> 3][j >> 3] += OrgImg[i][j];
		}
	}
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 32; j++) {
			temp[i][j] /= 64;
		}
	} 

	// temp배열을 형변환 해서 모자이크 배열에 삽입
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			Mosaic[i][j] = (char)temp[i >> 3][j >> 3];
		}
	}


	// 파일이미지 출력
	FILE *outfile;
    fopen_s(&outfile, "mosaic_image.raw", "wb");
	fwrite(Mosaic, sizeof(char), 256 * 256, outfile);
	fclose(outfile);
	
}


