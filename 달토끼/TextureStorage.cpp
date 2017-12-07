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
	//나중에 아이디 받는거랑 분리하기
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	
	BITMAPINFO* info;
	TextureData pData = LoadMyBitmap(filename, info);
	
	//만약 로드하는데 실패한 경우
	bool LoadFail =
		pData.BitSize == -1 ||
		pData.InfoSize == -1 ||
		pData.texturepByte == nullptr ||
		pData.textureInfo == nullptr;
	if (LoadFail) {
		std::cout << filename << " 을 읽어오는 것에 실패했습니다." << std::endl;
		return;
	}


	//텍스쳐 설정 정의
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

	//이미지 파일 불러오기를 실패할 경우
	if ((fp = fopen(filename, "rb")) == NULL) {
		fclose(fp);
		std::cout << "이미지 파일을 불러올 수 없습니다." << std::endl;
		return temp;
	}
	std::cout << filename << "을 불러왔습니다. " << std::endl;

	//헤더 사이즈가 맞지 않는 경우
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "맞지 않는 bmp 파일입니다." << std::endl;
		return temp;
	}

	//비트맵 파일이 아닐 경우
	//비트맵 파일은 맨 처음에 BM으로 시작한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return temp;
	}

	// BITMAPINFOHEADER 위치로 간다. 
	temp.InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((temp.textureInfo = new BITMAPINFO[temp.InfoSize]) == nullptr) {
		std::cout << "메모리 할당 실패." << std::endl;
		DeleteData(temp);
		fclose(fp);
		exit(0);
		return temp;
	}

	// 비트맵 인포 헤더를 읽는다.  
	if (fread(temp.textureInfo, 1, temp.InfoSize, fp) < (unsigned int)temp.InfoSize) {
		std::cout << "info header read fail." << std::endl;
		DeleteData(temp);
		fclose(fp);
		return temp;
	}

	// 비트맵의 크기 설정 
	if ((temp.BitSize = temp.textureInfo->bmiHeader.biSizeImage) == 0) {
		std::cout << "비트맵 크기 설정." << std::endl;
		int size = ((temp.textureInfo->bmiHeader.biWidth) * (temp.textureInfo->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs((temp.textureInfo)->bmiHeader.biHeight));
		temp.BitSize = size;
	}
	
	// 비트맵의 크기만큼 메모리를 할당한다.  
	if ( (temp.texturepByte = new GLubyte[temp.BitSize] ) == NULL ) {
		std::cout << "bit 할당 실패." << std::endl;
		DeleteData(temp);
		fclose(fp);  
		return temp;
	} 

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if ( fread(temp.texturepByte, 1, temp.BitSize, fp) < (unsigned int)temp.BitSize ) {
		std::cout << "데이터 입력 실패." << std::endl;
		DeleteData(temp);
		fclose(fp);  
		return temp;
	}

	std::cout << "완료" << std::endl;
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
	std::cout << "너비: " << m_DataStorage[ID].textureInfo->bmiHeader.biWidth << std::endl;
	std::cout << "높이: " << m_DataStorage[ID].textureInfo->bmiHeader.biHeight << std::endl;
}
