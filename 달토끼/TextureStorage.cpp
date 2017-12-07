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
	
	BITMAPINFO* info;
	TextureData pData = LoadMyBitmap(filename, info);
	
	//���� �ε��ϴµ� ������ ���
	bool LoadFail =
		pData.BitSize == -1 ||
		pData.InfoSize == -1 ||
		pData.texturepByte == nullptr ||
		pData.textureInfo == nullptr;
	if (LoadFail) {
		std::cout << filename << " �� �о���� �Ϳ� �����߽��ϴ�." << std::endl;
		return;
	}


	//�ؽ��� ���� ����
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		3,
		pData.textureInfo->bmiHeader.biWidth,
		pData.textureInfo->bmiHeader.biHeight,
		0,
		GL_BGR_EXT,
		GL_UNSIGNED_BYTE, 
		pData.texturepByte
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	ID = CTextureStorage::m_TextureID;
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	m_DataStorage.push_back(pData);

	CTextureStorage::m_TextureID += 1;
}

void CTextureStorage::DeleteData(TextureData & data)
{
	data.BitSize = -1;
	data.InfoSize = -1;

	if (data.texturepByte != nullptr) {
		delete[] data.texturepByte;
		data.texturepByte = nullptr;
	}

	if (data.textureInfo != nullptr) {
		delete[] data.textureInfo;
		data.textureInfo = nullptr;
	}
}

CTextureStorage::TextureData CTextureStorage::LoadMyBitmap(const char * filename, BITMAPINFO*& info)
{
	FILE *fp;
	
	TextureData temp;
	BITMAPFILEHEADER header;

	//�̹��� ���� �ҷ����⸦ ������ ���
	if ((fp = fopen(filename, "rb")) == NULL) {
		fclose(fp);
		std::cout << "�̹��� ������ �ҷ��� �� �����ϴ�." << std::endl;
		return temp;
	}
	std::cout << filename << "�� �ҷ��Խ��ϴ�. " << std::endl;

	//��� ����� ���� �ʴ� ���
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "���� �ʴ� bmp �����Դϴ�." << std::endl;
		return temp;
	}

	//��Ʈ�� ������ �ƴ� ���
	//��Ʈ�� ������ �� ó���� BM���� �����Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return temp;
	}

	// BITMAPINFOHEADER ��ġ�� ����. 
	temp.InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((temp.textureInfo = new BITMAPINFO[temp.InfoSize]) == nullptr) {
		std::cout << "�޸� �Ҵ� ����." << std::endl;
		DeleteData(temp);
		fclose(fp);
		exit(0);
		return temp;
	}

	// ��Ʈ�� ���� ����� �д´�.  
	if (fread(temp.textureInfo, 1, temp.InfoSize, fp) < (unsigned int)temp.InfoSize) {
		std::cout << "info header read fail." << std::endl;
		DeleteData(temp);
		fclose(fp);
		return temp;
	}

	// ��Ʈ���� ũ�� ���� 
	if ((temp.BitSize = temp.textureInfo->bmiHeader.biSizeImage) == 0) {
		std::cout << "��Ʈ�� ũ�� ����." << std::endl;
		int size = ((temp.textureInfo->bmiHeader.biWidth) * (temp.textureInfo->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs((temp.textureInfo)->bmiHeader.biHeight));
		temp.BitSize = size;
	}
	
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.  
	if ( (temp.texturepByte = new GLubyte[temp.BitSize] ) == NULL ) {
		std::cout << "bit �Ҵ� ����." << std::endl;
		DeleteData(temp);
		fclose(fp);  
		return temp;
	} 

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if ( fread(temp.texturepByte, 1, temp.BitSize, fp) < (unsigned int)temp.BitSize ) {
		std::cout << "������ �Է� ����." << std::endl;
		DeleteData(temp);
		fclose(fp);  
		return temp;
	}

	std::cout << "�Ϸ�" << std::endl;
	fclose(fp);
	
	return temp;
}

void CTextureStorage::BindBitmap(const GLuint & ID) const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

const GLubyte * CTextureStorage::GetTextureBit(const GLuint& ID) const noexcept
{
	return m_DataStorage[ID].texturepByte;
}

const BITMAPINFO * CTextureStorage::GetTextureInfo(const GLuint& ID) const noexcept
{
	return m_DataStorage[ID].textureInfo;
}

const int CTextureStorage::GetWidth(const GLuint& ID) const noexcept
{
	return m_DataStorage[ID].textureInfo->bmiHeader.biWidth;
}

const int CTextureStorage::GetHeight(const GLuint& ID) const noexcept
{
	return m_DataStorage[ID].textureInfo->bmiHeader.biHeight;
}

void CTextureStorage::ShowData(const GLuint& ID) const
{
	std::cout << "BITMAPINFOHEADER" << std::endl;
	std::cout << "�ʺ�: " << m_DataStorage[ID].textureInfo->bmiHeader.biWidth << std::endl;
	std::cout << "����: " << m_DataStorage[ID].textureInfo->bmiHeader.biHeight << std::endl;
}
