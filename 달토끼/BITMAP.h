#pragma once
//
//class BITMAPFILEHEADER {	//��Ʈ�� ��� ����
//public:
//
//	WORD	bfType;			//Ÿ��
//	DWORD	bfSize;			//���� ������
//	WORD	bfReserved1;	// 0
//	WORD	bfReserved2;	// 0
//	DWORD	bfOffBits;		//�̹��� ������ ��ġ(����Ʈ ����)
//};
//
//class BITMAPINFOHEADER {    // ��Ʈ�� ��� ���� ����    
//public:
//
//	DWORD  biSize;     // BITMAPINFOHEADER ũ��: ����Ʈ ����  
//	LONG  biWidth;    // �ȼ� ������ �̹��� �� 
//	LONG biHeight;   // �ȼ� ������ �̹��� ����   
//	WORD  biPlanes;    // �÷� ����� ����: �׻� 1 
//	WORD  biBitCount;   // �÷� ��Ʈ�� ���� 
//	DWORD  biCompression;   // ���� ���� ����� ����
//	DWORD  biSizeImage;   // ����Ʈ ������ ��Ÿ�� �̹��� ũ�� 
//	LONG  biXPelsPerMeter;  // ���ʹ� ���� �ȼ� ��   
//	LONG  biYPelsPerMeter;  // ���ʹ� ���� �ȼ� ��  
//	DWORD  biClrUsed;   // ���� �÷� �� 
//	DWORD  biClrImportant;  // �߿��� �÷� �� 
//};
//
//class RGBQUAD {  // rgbq 
//public:
//	BYTE	rgbBlue;
//	BYTE	rgbGreen;
//	BYTE	rgbRed;
//	BYTE	rgbReserved;
//};
//
//class BITMAPINFO {  // bmi  
//public:
//	BITMAPINFOHEADER bmiHeader;
//	RGBQUAD bmiColors[1];
//};
//
//
