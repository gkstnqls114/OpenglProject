#pragma once

class Item
{
protected:
	CVector3D<GLdouble>	m_Pos;
	int					m_BoardPosNum{ 0 };

public:
	Item();
	virtual ~Item();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Set_Pos(const CVector3D<>& pos) = 0;

	void StateChange_Pop() {};
	void StateChange_Float() {};
	void StateChange_Disappear() {};
};

