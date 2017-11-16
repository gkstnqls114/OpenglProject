#pragma once

class CFootBoard;

class CRoad
{
	CFootBoard* p;
	int m_boardNum{ 100 };
	//-1 : left
	// 0 : front
	// 1 : right
	const int k_side[3] = { -1, 0, 1 };

private:
	void InitFootBoard(const int& distance);

public:
	CRoad(const int& distance);
	~CRoad();

	void Render();
	void Update();

};

