#pragma once
#include "Colleague.h"

class CObjModel;
class CMatrix;

class CGAMEOVER_word :
	public CColleague
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };


public:
	CGAMEOVER_word(const CVector3D<>& Pos);
	virtual ~CGAMEOVER_word();

	void Render();
	void Update();
};

