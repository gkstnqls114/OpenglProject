#pragma once
#include <random>

enum eSide
{
	k_LeftIndex = 0,
	k_FrontIndex,
	k_RightIndex
};

class Side
{
	int m_Side{ k_FrontIndex };

public:
	Side();
	~Side();
	
	void IsLeft() { m_Side = k_LeftIndex; }
	void IsFront() { m_Side = k_FrontIndex; }
	void IsRight() { m_Side = k_RightIndex;	}
	const int Get_Side() const { return m_Side; }


	static const int Get_randSide()
	{
		int rand[3]{ k_LeftIndex , k_FrontIndex , k_RightIndex };
		return rand[std::rand() % 3];
	}
};
