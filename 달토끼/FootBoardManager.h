#pragma once

class CFootBoard;
class ItemManager;
class CPlayer;

class FootBoardManger
{
	CFootBoard**		m_pFootBoard{ nullptr };
	int				m_DisappearingBoardIndex{ 0 };
	int				m_Length{ -1 };
	int				m_Width{ 3 };
	
private:
	void Set_FootBoardPos(ItemManager&);
	void InitFootBoardModel();

public:
	FootBoardManger();
	FootBoardManger(const int& , ItemManager&);
	~FootBoardManger();

	void Initialize(const int&, ItemManager&);
	void TestRender();
	void Render();
	void Update();

	/////////////////////////////////Get
	const int Get_DisappearingBoardIndex() const noexcept { return m_DisappearingBoardIndex; }
	const CVector3D<> Get_LastPos() const noexcept;
	const CVector3D<> Get_FirstPos() const noexcept;
	const Side Get_Side(const int& len, const int& index) const noexcept;
	const CVector3D<> Get_Pos(const int& len, const int& index) const noexcept;
	const bool Get_Disappear(const int& len, const int& index) const noexcept;
	const bool Get_DisappearLength(const int& len) const noexcept;
	const bool Get_IsExisted(const int& len, const int& index) const noexcept;
	/////////////////////////////////Get

	const bool IsOutRange_DisappearingIndex() const;
	const bool IsOutRange_Length(const int& boardnum) const;
	const bool IsOutRange_Width(const int & index) const;
	void Add_DisappearingIndex(const CPlayer& player);
};