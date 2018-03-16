#pragma once
class CObjModel;
class RotateMatrix;

class CGAMEOVER_word
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	RotateMatrix* m_matrix{ nullptr };


public:
	CGAMEOVER_word(const CVector3D<>& Pos);
	virtual ~CGAMEOVER_word();

	void Render();
	void Update();
};

