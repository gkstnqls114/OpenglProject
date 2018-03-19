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

	void MoveLeft() { m_Side -= 1; }
	void MoveRight() { m_Side += 1; }

	const int Get_Side() const { return m_Side; }

	const bool Get_IsLeft() const;
	const bool Get_IsFront() const;
	const bool Get_IsRight() const;
	const bool IsOutofRange() const;
	const bool Get_IsSame(const Side& side) const;

	static const int Get_randSide()
	{
		int rand[3]{ k_LeftIndex , k_FrontIndex , k_RightIndex };
		return rand[std::rand() % 3];
	}
};
