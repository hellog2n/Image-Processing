// (2) 4���� ���η� �� color ��Ʈ�� ���� ���� <Ʈ���÷���>
//

#include <stdio.h>
#include <Windows.h>
#define BYTE unsigned char
#define WIDTHBYTES(bits) (((bits) + 31) / 32*4) // 4����Ʈ ����� ��ȯ
int main()
{
	int i, j;
	int rwsize = WIDTHBYTES(24 * 256);

	// "���� �������" ���� ����
	BITMAPFILEHEADER hf;
	// "�����������" ���� ����
	BITMAPINFOHEADER hInfo;

	// 256*256�� Ʈ���÷� �迭 ����
	BYTE* lpOutImg = new BYTE[rwsize * 256];

	// ������� ����
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

	// ������� ����
	hf.bfType = 0x4D42;
	hf.bfOffBits = 54;  // �ȷ�Ʈ�� �����Ƿ� ������ ���ۺο��� �������ͱ����� �������� ����ũ����.
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;



	for (j = 0; j < 256; j++) {
		for (i = 0; i < 64; i++) {
			// RED ��� 
			lpOutImg[i * rwsize + 3 * j + 2] = 255; //  R
			lpOutImg[i * rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[i * rwsize + 3 * j] = 0; //  B

			// GREEN ��� 
			lpOutImg[(i + 64) * rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 64) * rwsize + 3 * j + 1] = 255;	//  G
			lpOutImg[(i + 64) * rwsize + 3 * j] = 0; //  B

			// BLUE ��� 
			lpOutImg[(i + 128) * rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 128) * rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[(i + 128) * rwsize + 3 * j] = 255; //  B

			// BLACK ��� 
			lpOutImg[(i + 192) * rwsize + 3 * j + 2] = 0; //  R
			lpOutImg[(i + 192) * rwsize + 3 * j + 1] = 0;	//  G
			lpOutImg[(i + 192) * rwsize + 3 * j] = 0; //  B
		}
	}





	// �ϵ��ũ�� �������� ����
	FILE* outfile;
	fopen_s(&outfile, "sample_color_image2.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(lpOutImg, sizeof(BYTE), hInfo.biSizeImage, outfile);
	fclose(outfile);

	delete lpOutImg;

	printf("The End\n");

	return 0;

}


