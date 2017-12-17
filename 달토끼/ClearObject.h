#pragma once
#include "Colleague.h"

class CObjModel;
class CMatrix;

class CClearObject :
	public CColleague
{
	CVector3D<> m_Position;

	CObjModel* m_ClearMoon{ nullptr };
	CObjModel* m_ClearRabbit{ nullptr };
	CObjModel* m_ClearRabbitEar{ nullptr };
	CObjModel* m_ClearSunglass{ nullptr };
	CObjModel* m_ClearMartini{ nullptr };

	int rotatedegree{ 0 };
	bool IsClockRotate{ false };
public:
	CClearObject();
	virtual ~CClearObject();

	void Render();
	void Update();

	const CVector3D<> GetPos() const noexcept { return m_Position; }
	void SetPos(const CVector3D<>& pos);
	void SetPos(CVector3D<>&& pos);
};

