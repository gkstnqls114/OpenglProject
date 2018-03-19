#include "pch.h"
#include "Side.h"


Side::Side()
{
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

const bool Side::Get_IsSame(const Side & side) const
{
	return (side.Get_Side() == m_Side);
}
