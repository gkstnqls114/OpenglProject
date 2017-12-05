#pragma once
//
//class BITMAPFILEHEADER {	//비트맵 헤더 파일
//public:
//
//	WORD	bfType;			//타입
//	DWORD	bfSize;			//파일 사이즈
//	WORD	bfReserved1;	// 0
//	WORD	bfReserved2;	// 0
//	DWORD	bfOffBits;		//이미지 데이터 위치(바이트 단위)
//};
//
//class BITMAPINFOHEADER {    // 비트맵 헤더 인포 파일    
//public:
//
//	DWORD  biSize;     // BITMAPINFOHEADER 크기: 바이트 단위  
//	LONG  biWidth;    // 픽셀 단위의 이미지 폭 
//	LONG biHeight;   // 픽셀 단위의 이미지 높이   
//	WORD  biPlanes;    // 컬러 평면의 개수: 항상 1 
//	WORD  biBitCount;   // 컬러 비트의 개수 
//	DWORD  biCompression;   // 사용된 압축 방식의 종류
//	DWORD  biSizeImage;   // 바이트 단위로 나타낸 이미지 크기 
//	LONG  biXPelsPerMeter;  // 미터당 수평 픽셀 수   
//	LONG  biYPelsPerMeter;  // 미터당 수직 픽셀 수  
//	DWORD  biClrUsed;   // 사용된 컬러 수 
//	DWORD  biClrImportant;  // 중요한 컬러 수 
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
