#pragma once
#include <random>

enum eSide
{
	k_LeftIndex = 0,
	k_FrontIndex,
	k_RightIndex,
	k_All
};

class Side
{
	int m_Side{ -1 };

public:
	Side();
	Side(const int side);
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
	const bool IsOutofRange(const int& side) const;
	const bool IsSame(const Side& side) const;
	const Side FutureMoveSide(const Side& future);

	static const int Get_randSide()
	{
		int rand[3]{ k_LeftIndex , k_FrontIndex , k_RightIndex };
		return rand[std::rand() % 3];
	}
};
