#pragma once

class CFootBoard;

class FootBoardManger
{
	const int k_side[3]{ k_left, k_front, k_right };

	CFootBoard*		m_pFootBoard{ nullptr };
	int				m_DisappearingBoardIndex{ 0 };
	int				m_boardNum{ 5 };
	
private:
	void Initialize();
	void InitFootBoardModel();

public:
	FootBoardManger();
	~FootBoardManger();

	void TestRender();
	void Render();
	void Update();

	/////////////////////////////////Get
	const int Get_DisappearingBoardIndex() const noexcept { return m_DisappearingBoardIndex; }
	const CVector3D<> Get_LastPos() const noexcept;
	const CVector3D<> Get_FirstPos() const noexcept;

	const bool IsOutRange_Disappearing() const;
	const bool IsOutRange(const int& boardnum) const;
	const int Get_Side(const int& boardnum) const noexcept;
	const int Get_Disappear(const int& boardnum) const noexcept;
	/////////////////////////////////Get

};