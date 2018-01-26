#pragma once
#include "Observer.h"

class CObjModel;
class CMatrix;

class CGAMEOVER_word :
	public Observer
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

