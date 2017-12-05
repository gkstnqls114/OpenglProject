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

	//�̹��� ���� �ҷ����⸦ ������ ���
	if ((fp = fopen(filename, "rb")) == NULL) {
		fclose(fp);
		std::cout << "�̹��� ������ �ҷ��� �� �����ϴ�." << std::endl;
		return;
	}
	std::cout << filename << "�� �ҷ��Խ��ϴ�. " << std::endl;

	//��� ����� ���� �ʴ� ���
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "���� �ʴ� bmp �����Դϴ�." << std::endl;
		return;
	}
	std::cout << "��� ����� �ҷ��Խ��ϴ�. " << std::endl;
	std::cout << "������: " <<  sizeof(BITMAPFILEHEADER) << std::endl;

	//��Ʈ�� ������ �ƴ� ���
	//��Ʈ�� ������ �� ó���� BM���� �����Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return;
	}
	// BITMAPINFOHEADER ��ġ�� ����. 
	m_InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((m_textureInfo = new BITMAPINFO[m_InfoSize]) == nullptr) {
		std::cout << "�޸� �Ҵ� ����." << std::endl;
		fclose(fp);
		exit(0);
		return;
	}

	// ��Ʈ�� ���� ����� �д´�.  
	if (fread(m_textureInfo, 1, m_InfoSize, fp) < (unsigned int)m_InfoSize) {
		std::cout << "info header read fail." << std::endl;
		delete m_textureInfo;
		fclose(fp);
		return;
	}

	// ��Ʈ���� ũ�� ���� 
	if ((m_BitSize = m_textureInfo->bmiHeader.biSizeImage) == 0) {
		std::cout << "��Ʈ�� ũ�� ����." << std::endl;
		int size = ((m_textureInfo->bmiHeader.biWidth) * (m_textureInfo->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs((m_textureInfo)->bmiHeader.biHeight));
		m_BitSize = size;
	}
	
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.  
	if ( (m_textureBit = new GLubyte[m_BitSize] ) == NULL ) {
		std::cout << "bit �Ҵ� ����." << std::endl;
		delete m_textureInfo;  
		fclose(fp);  
		return;
	} 

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if ( fread(m_textureBit, 1, m_BitSize, fp) < (unsigned int)m_BitSize ) {
		std::cout << "������ �Է� ����." << std::endl;
		delete m_textureInfo;
		delete m_textureBit;
		fclose(fp);  
		return;
	}

	std::cout << "�Ϸ�" << std::endl;
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
	std::cout << "�ʺ�: " << m_textureInfo->bmiHeader.biWidth << std::endl;
	std::cout << "����: " << m_textureInfo->bmiHeader.biHeight << std::endl;
}
