#pragma once

class CObjModel;
class CMatrix;

class CEXIT_word
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

	bool IsSelected{ false };
public:
	CEXIT_word(const CVector3D<>& Pos);
	~CEXIT_word();

	void Render();
	void Update();

	void Scale(const float& size);
	void Selected() { IsSelected = true; }
	void NotSelected() { IsSelected = false; }
	const CVector3D<>& GetPos() const noexcept { return m_Position; }
};

