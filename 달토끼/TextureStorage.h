#pragma once


class CTextureStorage
{
public:

	struct TextureData {
		bool		IsAlpha{ false };
		int			BitSize{ -1 };
		int			InfoSize{ -1 };
		GLubyte*	texturepByte{ nullptr }; //데이터를 가리킬 포인터
		BITMAPINFO* textureInfo{ nullptr };

	};

private:
	static GLuint m_TextureID;
	std::vector<TextureData> m_DataStorage;

private:
	void DeleteData(TextureData& data);
	TextureData LoadMyBitmap(const char* filename, BITMAPINFO*& info);

public:
	CTextureStorage();
	~CTextureStorage();

	void StoreBitmap(const char* filename, GLuint& ID);

	void BindBitmap(const GLuint& ID) const;

	const GLubyte* GetTextureBit(const GLuint& ID) const noexcept;
	const BITMAPINFO* GetTextureInfo(const GLuint& ID) const noexcept;
	const int GetWidth(const GLuint& ID) const noexcept;
	const int GetHeight(const GLuint& ID) const noexcept;
	void ShowData(const GLuint& ID) const;
};
