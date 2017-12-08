#pragma once
#include "Colleague.h"

class CObjModel;
class CMatrix;

class CEXIT_word
	:public CColleague
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

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
	const CVector3D<>& GetPos() const noexcept { return m_Position; }


	//메인화면
	virtual void Init_MainScene();
	virtual void Cursor_PLAY() { NotSelected(); };
	virtual void Cursor_EXIT() { Selected(); };
	virtual void GameStart() {
		IsGameStart = true;
	}

};

