#pragma once

class CObjFace
{
	int * m_VertexIndex{ nullptr };
	int m_VertexNum{ 0 };

public:
	CObjFace();
	~CObjFace();

	void SetIndex(const int& num, const int& val)
	{
		if (m_VertexIndex != nullptr) {
			m_VertexIndex[num] = val;
		}
	}
	void InitVertexNum()
	{
		for (int x = 0; x < 4; ++x) {
			if (m_VertexIndex[x] != -1) {
				m_VertexNum += 1;
			}
		}
	}

	void ShowData()
	{
		for (int x = 0; x < m_VertexNum; ++x) {
			std::cout << m_VertexIndex[x] << " ,";
		}
		std::cout << "정점인덱스 수: " << m_VertexNum << std::endl;

	}

	const int GetIndex(const int& num) { return m_VertexIndex[num]; }
	const int GetVertexNum() const { return m_VertexNum; }
};

