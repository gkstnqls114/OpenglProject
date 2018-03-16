#pragma once

class Item
{ 
protected:
	int m_Side{ k_front };
	CVector3D<GLdouble>	m_Pos;

private:
	virtual void ModelRender() = 0;

public:
	Item();
	virtual ~Item();
	
	virtual void Update() = 0;
	virtual void Render();
	virtual void Set_Pos(const CVector3D<>& pos) = 0;
	virtual const CVector3D<> Get_Pos() const = 0;
	void StateChange_Pop() {};
	void StateChange_Float() {};
	void StateChange_Disappear() {};
};

