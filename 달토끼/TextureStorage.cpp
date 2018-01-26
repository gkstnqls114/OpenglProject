#include "pch.h"
#include "TextureStorage.h"

GLuint CTextureStorage::m_TextureID = 0;

CTextureStorage::CTextureStorage()
{

}

CTextureStorage::~CTextureStorage()
{

}

void CTextureStorage::StoreBitmap(const char * filename, GLuint& ID)
{
	//���߿� ���̵� �޴°Ŷ� �и��ϱ�
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	
	BITMAPINFO* Info;
	GLubyte * pData = LoadMyBitmap(filename, Info);
	
	if (pData == nullptr) return;

	//�ؽ��� ���� ����
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		3,
		Info->bmiHeader.biWidth,
		Info->bmiHeader.biHeight,
		0,
		GL_BGR_EXT,
		GL_UNSIGNED_BYTE, 
		pData
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	ID = CTextureStorage::m_TextureID;
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//TextureData temp;
	//temp.texturepByte = pData;
	//m_DataStorage.push_back(temp);

	CTextureStorage::m_TextureID += 1;
}


GLubyte * CTextureStorage::LoadMyBitmap(const char * filename, BITMAPINFO*& info)
{
	// filename: 
	//
	//
	FILE *fp = NULL;
	
	GLubyte * pbit;
	int BitSize = -1;
	int InfoSize = -1;
	BITMAPFILEHEADER header;

	//�̹��� ���� �ҷ����⸦ ������ ���
	if ((fp = fopen(filename, "rb")) == NULL) {
		//std::cout << "�̹��� ������ �ҷ��� �� �����ϴ�." << std::endl;
		fclose(fp);
		return nullptr;
	}
	//std::cout << filename << "�� �ҷ��Խ��ϴ�. " << std::endl;

	//��� ����� ���� �ʴ� ���
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "���� �ʴ� bmp �����Դϴ�." << std::endl;
		return nullptr;
	}

	//��Ʈ�� ������ �ƴ� ���
	//��Ʈ�� ������ �� ó���� BM���� �����Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return nullptr;
	}

	// BITMAPINFOHEADER ��ġ�� ����. 
	InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((info = new BITMAPINFO[InfoSize]) == nullptr) {
		std::cout << "�޸� �Ҵ� ����." << std::endl;
		fclose(fp);
		exit(0);
		return nullptr;
	}

	// ��Ʈ�� ���� ����� �д´�.  
	if (fread(info, 1, InfoSize, fp) < (unsigned int)InfoSize) {
		std::cout << "info header read fail." << std::endl;
		
		fclose(fp);
		return nullptr;
	}

	// ��Ʈ���� ũ�� ���� 
	if ((BitSize = info->bmiHeader.biSizeImage) == 0) {
		std::cout << "��Ʈ�� ũ�� ����." << std::endl;
		int NowSize = ((info->bmiHeader.biWidth) * (info->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs(info->bmiHeader.biHeight));
		
		BitSize = NowSize;
	}
	
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.  
	if ( (pbit = new GLubyte[BitSize] ) == NULL ) {
		std::cout << "bit �Ҵ� ����." << std::endl;
		fclose(fp);  
		return nullptr;
	} 

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if ( fread(pbit, 1, BitSize, fp) < (unsigned int)BitSize ) {
		std::cout << "������ �Է� ����." << std::endl;
		fclose(fp);  
		return nullptr;
	}

	fclose(fp);
	
	//std::cout << filename << ": �Ϸ�" << std::endl;
	
	return pbit;
}

void CTextureStorage::BindBitmap(const GLuint & ID) const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
//
//const GLubyte * CTextureStorage::GetTextureBit(const GLuint& ID) const noexcept
//{
//	//return m_DataStorage[ID].texturepByte;
//}
