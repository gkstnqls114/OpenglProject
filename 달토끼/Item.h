#pragma once

class Item
{ 
protected:
	int m_Side{ k_front };
	CVector3D<GLdouble>	m_Pos;

	GLfloat m_Scale_Matrix[16] =
	{
		1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

private:
	virtual void ModelRender() = 0;

public:
	Item();
	virtual ~Item();
	
	virtual void Update() = 0;
	virtual void Render();
	void Set_Pos(const CVector3D<>& pos);
	const CVector3D<> Get_Pos() const { return m_Pos; };
	
	void StateChange_Pop() {};
	void StateChange_Float() {};
	void StateChange_Disappear() {};
};

