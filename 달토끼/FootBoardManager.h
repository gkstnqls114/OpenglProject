#pragma once

class CFootBoard;

class FootBoardManger
{
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

	const bool IsOutRange() const;
	const bool CheckSide(const int& side);
	/////////////////////////////////Get


};