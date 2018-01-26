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
	
	BITMAPINFO* Info;
	GLubyte * pData = LoadMyBitmap(filename, Info);
	
	if (pData == nullptr) return;

	//텍스쳐 설정 정의
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

	//이미지 파일 불러오기를 실패할 경우
	if ((fp = fopen(filename, "rb")) == NULL) {
		//std::cout << "이미지 파일을 불러올 수 없습니다." << std::endl;
		fclose(fp);
		return nullptr;
	}
	//std::cout << filename << "을 불러왔습니다. " << std::endl;

	//헤더 사이즈가 맞지 않는 경우
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		std::cout << "맞지 않는 bmp 파일입니다." << std::endl;
		return nullptr;
	}

	//비트맵 파일이 아닐 경우
	//비트맵 파일은 맨 처음에 BM으로 시작한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return nullptr;
	}

	// BITMAPINFOHEADER 위치로 간다. 
	InfoSize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((info = new BITMAPINFO[InfoSize]) == nullptr) {
		std::cout << "메모리 할당 실패." << std::endl;
		fclose(fp);
		exit(0);
		return nullptr;
	}

	// 비트맵 인포 헤더를 읽는다.  
	if (fread(info, 1, InfoSize, fp) < (unsigned int)InfoSize) {
		std::cout << "info header read fail." << std::endl;
		
		fclose(fp);
		return nullptr;
	}

	// 비트맵의 크기 설정 
	if ((BitSize = info->bmiHeader.biSizeImage) == 0) {
		std::cout << "비트맵 크기 설정." << std::endl;
		int NowSize = ((info->bmiHeader.biWidth) * (info->bmiHeader.biBitCount) + 7) 
		/ (8 *  abs(info->bmiHeader.biHeight));
		
		BitSize = NowSize;
	}
	
	// 비트맵의 크기만큼 메모리를 할당한다.  
	if ( (pbit = new GLubyte[BitSize] ) == NULL ) {
		std::cout << "bit 할당 실패." << std::endl;
		fclose(fp);  
		return nullptr;
	} 

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if ( fread(pbit, 1, BitSize, fp) < (unsigned int)BitSize ) {
		std::cout << "데이터 입력 실패." << std::endl;
		fclose(fp);  
		return nullptr;
	}

	fclose(fp);
	
	//std::cout << filename << ": 완료" << std::endl;
	
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
