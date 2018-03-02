#pragma once
class CObjModel;
class CMatrix;

class CGAMECLEAR_word
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

public:
	CGAMECLEAR_word(const CVector3D<>& Pos);
	virtual ~CGAMECLEAR_word();

	void Render();
	void Update();
};

