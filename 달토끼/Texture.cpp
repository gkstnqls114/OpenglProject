#include "pch.h"
#include <bitset>
#include "Texture.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
	if (m_textureBit != nullptr) {
		delete[] m_textureBit;
	}

	if (m_textureInfo != nullptr) {
		delete[] m_textureInfo;
	}
}

void CTexture::LoadDIBitmap(const char * filename)
{
	FILE *fp;
	BITMAPFILEHEADER header;

	//이미지 파일 불러오기를 실패할 경우
	if ((fp = fopen(filename, "rb")) == NULL) {
		fclose(fp);
		std::cout << "이미지 파일을 불러올 수 없습니다." << std::endl;
		return;
	}
	std::cout << filename << "을 불러왔습니다. " << std::endl;

	//헤더 사이즈가 맞지 않는 경우
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "맞지 않는 bmp 파일입니다." << std::endl;
		return;
	}
	std::cout << "헤더 사이즈를 불러왔습니다. " << std::endl;
	std::cout << "사이즈: " <<  sizeof(BITMAPFILEHEADER) << std::endl;

	//비트맵 파일이 아닐 경우
	//비트맵 파일은 맨 처음에 BM으로 시작한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return;
	}
	// BITMAPINFOHEADER 위치로 간다. 
	m_InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((m_textureInfo = new BITMAPINFO[m_InfoSize]) == nullptr) {
		std::cout << "메모리 할당 실패." << std::endl;
		fclose(fp);
		exit(0);
		return;
	}

	// 비트맵 인포 헤더를 읽는다.  
	if (fread(m_textureInfo, 1, m_InfoSize, fp) < (unsigned int)m_InfoSize) {
		std::cout << "info header read fail." << std::endl;
		delete m_textureInfo;
		fclose(fp);
		return;
	}

	// 비트맵의 크기 설정 
	if ((m_BitSize = m_textureInfo->bmiHeader.biSizeImage) == 0) {
		std::cout << "비트맵 크기 설정." << std::endl;
		int size = ((m_textureInfo->bmiHeader.biWidth) * (m_textureInfo->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs((m_textureInfo)->bmiHeader.biHeight));
		m_BitSize = size;
	}
	
	// 비트맵의 크기만큼 메모리를 할당한다.  
	if ( (m_textureBit = new GLubyte[m_BitSize] ) == NULL ) {
		std::cout << "bit 할당 실패." << std::endl;
		delete m_textureInfo;  
		fclose(fp);  
		return;
	} 

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if ( fread(m_textureBit, 1, m_BitSize, fp) < (unsigned int)m_BitSize ) {
		std::cout << "데이터 입력 실패." << std::endl;
		delete m_textureInfo;
		delete m_textureBit;
		fclose(fp);  
		return;
	}

	std::cout << "완료" << std::endl;
	fclose(fp);
}

const GLubyte * CTexture::GetTextureBit() const noexcept
{
	if (m_textureBit == nullptr) { return 0; }

	return m_textureBit;
}

const BITMAPINFO * CTexture::GetTextureInfo() const noexcept
{
	if (m_textureInfo == nullptr) { return NULL; }

	return m_textureInfo;
}

const int CTexture::GetWidth() const noexcept
{
	if (m_textureInfo == nullptr) { return -1; }

	return m_textureInfo->bmiHeader.biWidth;
}

const int CTexture::GetHeight() const noexcept
{
	if (m_textureInfo == nullptr) { return -1; }

	return m_textureInfo->bmiHeader.biHeight;
}

void CTexture::ShowData()
{
	std::cout << "BITMAPINFOHEADER" << std::endl;
	std::cout << "너비: " << m_textureInfo->bmiHeader.biWidth << std::endl;
	std::cout << "높이: " << m_textureInfo->bmiHeader.biHeight << std::endl;
}
