#pragma once


class CTextureStorage
{
public:
	struct TextureData {
		bool		IsAlpha{ false };
		GLubyte*	texturepByte{ nullptr }; //데이터를 가리킬 포인터
		
		TextureData() {

		}
		GLubyte* GetpByte() { 
			return texturepByte;
		};
	};

private:
	static GLuint m_TextureID;
	//static std::vector<TextureData> m_DataStorage;

private:
	GLubyte * LoadMyBitmap(const char* filename, BITMAPINFO*& info);

public:
	CTextureStorage();
	~CTextureStorage();

	void StoreBitmap(const char* filename, GLuint& ID);

	void BindBitmap(const GLuint& ID) const;

	const GLubyte* GetTextureBit(const GLuint& ID) const noexcept;

};
