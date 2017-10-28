#pragma once

class CObjFace
{
	int m_VertexIndex[4]{ -1, -1, -1, -1 };
	int m_VertexNum{ 0 };

public:
	CObjFace();
	~CObjFace();

	void SetIndex_0(const int& num) { m_VertexIndex[0] = num; }
	void SetIndex_1(const int& num) { m_VertexIndex[1] = num; }
	void SetIndex_2(const int& num) { m_VertexIndex[2] = num; }
	void SetIndex_3(const int& num) { m_VertexIndex[3] = num; }
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
		for (int x = 0; x < 4; ++x) {
			std::cout << m_VertexIndex[x] << " ,";
		}
		std::cout << "정점인덱스 수: " << m_VertexNum << std::endl;

	}

	const int GetIndex(const int& num) { return m_VertexIndex[num]; }
	const int GetIndex_0() const { return m_VertexIndex[0]; }
	const int GetIndex_1() const { return m_VertexIndex[1]; }
	const int GetIndex_2() const { return m_VertexIndex[2]; }
	const int GetIndex_3() const { return m_VertexIndex[3]; }
	const int GetVertexNum() const { return m_VertexNum; }
};

