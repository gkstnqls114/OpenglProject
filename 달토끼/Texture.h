#pragma once


class CTexture
{
	int m_BitSize{ -1 };
	int m_InfoSize{ -1 };
	GLubyte* m_textureBit{ nullptr }; //데이터를 가리킬 포인터
	BITMAPINFO* m_textureInfo{ nullptr };


public:
	CTexture();
	~CTexture();

	void LoadDIBitmap(const char* filename);
	const GLubyte* GetTextureBit() const noexcept;
	const BITMAPINFO* GetTextureInfo() const noexcept;

	const int GetWidth() const noexcept;
	const int GetHegiht() const noexcept;

	void ShowData();
};

