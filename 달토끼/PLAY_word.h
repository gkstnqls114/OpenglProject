#pragma once

class CObjModel;
class CMatrix;

class CPLAY_word
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

	float NowSize{ 1.f };
	
	float BeginSize	{ 1.1f };
	float EndSize	{ 1.3f };
	float SizeTime{ 0.f };

	bool IsSelected{ false };

public:
	CPLAY_word(const CVector3D<>& Pos);
	~CPLAY_word();
	
	void Render();
	void Update();

	void Scale(const float& NowSize);
	void Selected() { IsSelected = true; }
	void NotSelected();
	const CVector3D<>& GetPos() const noexcept { return m_Position; }
};

