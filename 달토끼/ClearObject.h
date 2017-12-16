#pragma once
#include "Colleague.h"

class CObjModel;
class CMatrix;

class CClearObject :
	public CColleague
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };


public:
	CClearObject();
	virtual ~CClearObject();

	void Render();
	void Update();

	const CVector3D<> GetPos() const noexcept { return m_Position; }

};

