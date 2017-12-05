#pragma once

class CObjFace
{
	int m_VertexNum{ 0 };
	int * m_VertexIndex{ nullptr };
	
	int m_TextureNum{ 0 };
	int * m_TextureIndex{ nullptr };

	int m_NormalNum{ 0 };
	int * m_NormalIndex{ nullptr };

public:
	CObjFace();
	~CObjFace();

	void SetVertexNum(const int& num) {
		m_VertexNum = num;
		m_VertexIndex = new int[m_VertexNum];
	}
	void SetTextureNum(const int& num) {
		m_TextureNum = num;
		m_TextureIndex = new int[m_TextureNum];
	}
	void SetNormalNum(const int& num) {
		m_NormalNum = num;
		m_NormalIndex = new int[m_NormalNum];
	}

	void Set_VertexIndex(const int& num, const int& val)
	{
		if (m_VertexIndex != nullptr) {
			m_VertexIndex[num] = val;
		}
	}
	void Set_TextureIndex(const int& num, const int& val)
	{
		if (m_TextureIndex != nullptr) {
			m_TextureIndex[num] = val;
		}
	}
	void Set_NormalIndex(const int& num, const int& val)
	{
		if (m_NormalIndex != nullptr) {
			m_NormalIndex[num] = val;
		}
	}

	void ShowData()
	{
		for (int x = 0; x < m_VertexNum; ++x) {
			std::cout << m_VertexIndex[x] << " ,";
		}
		std::cout << "정점인덱스 수: " << m_VertexNum << std::endl;

	}

	const int GetVertexIndex(const int& num) const noexcept;
	const int GetTextureIndex(const int& num) const noexcept;
	const int GetNormalIndex(const int& num) const noexcept;
	
	const int GetVertexNum() const noexcept { return m_VertexNum; }
	const int GetTextureNum() const noexcept { return m_TextureNum; }
	const int GetNormalNum() const noexcept { return m_NormalNum; }
};

