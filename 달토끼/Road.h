#pragma once

class CFootBoard;

class CRoad
{
	CFootBoard* p;
	int m_boardNum{ 5 };

private:


public:
	CRoad();
	~CRoad();

	void Render();
	void Update();

};

