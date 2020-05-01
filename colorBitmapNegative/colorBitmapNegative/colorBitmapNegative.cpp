

#include <stdio.h>
#include <windows.h>
#define WIDTHBYTES(bits) (((bits) + 31) / 32*4) // 4����Ʈ�� ������� ��
#define BYTE unsigned char




int main()
{
	FILE* infile;
	fopen_s(&infile, "pshop256.bmp", "rb");
	if (infile == NULL) { printf("There is no file!!!\n"); }

	BITMAPFILEHEADER hf;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile); // ������带 ����
	if (hf.bfType != 0x4D42) exit(1);

	BITMAPINFOHEADER hInfo;
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile); // ���� ��带 ����

	// 256 �÷� ������ ���� ������� ����
	if (hInfo.biBitCount < 8) { printf("Bad file format!"); return -1; }

	RGBQUAD* pRGB = NULL;
	if (hInfo.biClrUsed != 0) // �ȷ�Ʈ�� �ִ� ���
	{
		pRGB = new RGBQUAD[hInfo.biClrUsed]; // �ȷ�Ʈ�� ũ�⸸ŭ �޸𸮸� �Ҵ���
		fread(pRGB, sizeof(RGBQUAD), hInfo.biClrUsed, infile); // �ȷ�Ʈ�� ���Ͽ��� ����

	}

	// �������͸� ������ �޸� �Ҵ�
	BYTE* lpImg = new BYTE[hInfo.biSizeImage];
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	// ũ����, �޸� �Ҵ�
	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	int rwsize2 = WIDTHBYTES(24 * hInfo.biWidth);
	BYTE* lpOutImg = new BYTE[rwsize2 * hInfo.biHeight];
	int index, R, G, B, i, j;

	if (hInfo.biBitCount == 24)  // ���� �Է¿����� Ʈ��(24��Ʈ) �÷��� ���� �ȷ�Ʈ ����
		for (i = 0; i < hInfo.biHeight; i++) // ���� �̹��� ���ϱ�
		{
			for (j = 0; j < hInfo.biWidth; j++)
			{ // �ȷ�Ʈ�� �����Ƿ� �������Ͱ� �ٷ� �÷���
				lpOutImg[i * rwsize2 + 3 * j + 2] = 255 - lpImg[i * rwsize + 3 * j + 2];
				lpOutImg[i * rwsize2 + 3 * j + 1] = 255 - lpImg[i * rwsize + 3 * j + 1];
				lpOutImg[i * rwsize2 + 3 * j] = 255 - lpImg[i * rwsize + 3 * j];
			}
		}
	else// Ʈ�� �÷��� �ƴ� ���� �ȷ�Ʈ�� ����

		for (i = 0; i < hInfo.biHeight; i++) // ���� �̹��� ���ϱ�
		{
			for (j = 0; j < hInfo.biWidth; j++)
			{
				index = lpImg[i * rwsize + j]; // �������ʹ� �ȷ�Ʈ�� �ε�����
				R = pRGB[index].rgbRed; //�ȷ�Ʈ���� ���� �������͸� ������(R)
				G = pRGB[index].rgbGreen; // G
				B = pRGB[index].rgbBlue; // B
				R = 255 - R; G = 255 - G; B = 255 - B; // ������ �����.
				lpOutImg[i * rwsize2 + 3 * j + 2] = (BYTE)R;
				lpOutImg[i * rwsize2 + 3 * j + 1] = (BYTE)G;
				lpOutImg[i * rwsize2 + 3 * j] = (BYTE)B;

			}
		}

	// ���� ���� �̹����� �ϵ� ��ũ�� ��� (24��Ʈ�� Ʈ���÷��� ���)
	hInfo.biBitCount = 24;
	hInfo.biSizeImage = rwsize2 * hInfo.biHeight;
	hInfo.biClrUsed = hInfo.biClrImportant = 0;
	hf.bfOffBits = 54; // �ȷ�Ʈ�� �����Ƿ� ������ ���ۺο���
	// �������ͱ����� �������� ���� ũ����.
	hf.bfSize = hf.bfOffBits + hInfo.biSizeImage;

	FILE* outfile;
		fopen_s(&outfile, "OutImg24.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), outfile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), outfile);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hInfo.biHeight, outfile);
	fclose(outfile);

	// �޸� ����
	if (hInfo.biClrUsed != 0) delete[]pRGB;
	delete[]lpOutImg;
	delete[]lpImg;


}


