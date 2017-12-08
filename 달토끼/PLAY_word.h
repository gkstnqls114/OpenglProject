#pragma once

class CObjModel;
class CMatrix;

class CPLAY_word
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

	bool IsSelected{ false };

public:
	CPLAY_word(const CVector3D<>& Pos);
	~CPLAY_word();
	
	void Render();
	void Update();

	void Scale(const float& size);
	void Selected() { IsSelected = true; }
	void NotSelected();
	const CVector3D<>& GetPos() const noexcept { return m_Position; }
};

