#pragma once

class CObjModel;
class RotateMatrix;

class CEXIT_word
{
	CVector3D<> m_InitPosition;
	CVector3D<> m_Position;

	CObjModel* m_model{ nullptr };
	RotateMatrix* m_matrix{ nullptr };

	float NowSize{ 1.f };

	float BeginSize{ 1.1f };
	float EndSize{ 1.3f };
	float SizeTime{ 0.f };

	bool IsSelected{ false };
	bool IsGameStart{ false };
public:
	CEXIT_word(const CVector3D<>& Pos);
	~CEXIT_word();

	void Render();
	void Update();

	void Scale(const float& NowSize);
	void Selected() { IsSelected = true; }
	void NotSelected();
	const CVector3D<> Get_Pos() const noexcept { return m_Position; }


	//����ȭ��
	virtual void Init_MainScene();
	virtual void Cursor_PLAY() { NotSelected(); };
	virtual void Cursor_EXIT() { Selected(); };
	virtual void GameStart() {
		IsGameStart = true;
	}

};

