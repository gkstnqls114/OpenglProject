#include "pch.h"
#include "Side.h"


Side::Side()
{
}

Side::Side(const int side)
{
	if (IsOutofRange(side)) return;

	m_Side = side;
}

Side::~Side()
{
}

const bool Side::Get_IsLeft() const
{
	return (m_Side == k_LeftIndex);
}

const bool Side::Get_IsFront() const
{
	return (m_Side == k_FrontIndex);
}

const bool Side::Get_IsRight() const
{
	return (m_Side == k_RightIndex);
}

const bool Side::IsOutofRange() const
{
	return (m_Side > k_RightIndex || m_Side < k_LeftIndex);
}

const bool Side::IsOutofRange(const int & side) const
{
	return (side > k_RightIndex || side < k_LeftIndex);
}

const bool Side::IsSame(const Side & side) const
{
	return (side.Get_Side() == m_Side);
}

const Side Side::FutureMoveSide(const Side & future)
{
	int FutureMove = m_Side - future.m_Side;
	if (FutureMove == 0) {
		return Side(k_FrontIndex);
	}
	else if (FutureMove == -1) {
		return Side(k_RightIndex);
	}
	else if (FutureMove == 1){
		return Side(k_LeftIndex);
	}
	else {
		return Side();
	}
}
