#pragma once

class CFootBoard;

class FootBoardManger
{
	CFootBoard*		m_pFootBoard{ nullptr };
	int				m_DisappearingBoardIndex{ 0 };
	int				m_boardNum{ 5 };

public:
	FootBoardManger();
	~FootBoardManger();

	void Initialize();
	void Render();

	/////////////////////////////////Get
	const int Get_DisappearingBoardIndex() const noexcept { return m_DisappearingBoardIndex; }
	/////////////////////////////////Get


};