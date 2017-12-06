#pragma once


class CTextureStorage
{
	int			m_BitSize		{ -1 };
	int			m_InfoSize		{ -1 };
	GLubyte*	m_textureByte	{ nullptr }; //데이터를 가리킬 포인터
	BITMAPINFO* m_textureInfo	{ nullptr };

private:
	static GLuint m_TextureID;
	std::vector<GLubyte> m_DataPoint;

public:
	CTextureStorage();
	~CTextureStorage();

	void LoadDIBitmap(const char* filename);
	const GLubyte* GetTextureBit() const noexcept;
	const BITMAPINFO* GetTextureInfo() const noexcept;

	const int GetWidth() const noexcept;
	const int GetHeight() const noexcept;

	void ShowData();
};
