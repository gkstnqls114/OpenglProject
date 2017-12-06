#pragma once

class CObjModel;
class CMatrix;
class CVector3D;
class CMessageSender;
class CMediator;
class CRoad;
class CCamera;

class CPlayer
{
	static CObjModel* m_Rabit_Body		;
	static CObjModel* m_Rabit_Ear		;
	static CObjModel* m_Rabit_LeftFoot	;
	static CObjModel* m_Rabit_RightFoot	;

	static CObjModel* m_Rabits_Helmet	;

	CMatrix* m_Matrix{nullptr};

	CMediator* m_Mediator{nullptr};

	//점프변수들
	//jump property
	const float k_gravity{ 0.5f };
	const double k_PI{ 3.14152 };
	const int m_JumpDegree{ 80 };
	const float m_power{ 7.f };
	int m_FinishJumpTime{ 0 };
	GLdouble m_JumpReach{0};
	
	//아래의 점프변수를 하나로 묶을 수 있지 않을까?
	//일단 이것도 나중에 생각
	int prevSide{ 0 };
	int jumpSide{ 0 };
	bool IsJump{ false };
	bool IsRight{ false };
	bool IsLeft{ false };

	int m_JumpTime{ 0 };
	GLdouble m_vector_x{ 0 };
	GLdouble m_vector_y{ 0 };
	GLdouble m_vector_z{ 0 };
	
	bool isDead{ false };

	//현재 발판 넘버
	int m_BoardNum{ 0 };
	int m_MySide{ 0 };

	

private:
	void Process_Side(int& lhs);
	void Jump_BodyRotate();
	void Find_JumpProperty();
	void Jump();
	void Calculate_JumpVector();
	void Reset_JumpProperty();
	void Finish_Jump();

	static void InitBody();
	static void InitEar();
	static void InitLeftFoot();
	static void InitRightFoot();
	static void InitHelmet();


public:
	CPlayer(CMediator*& mediator);
	~CPlayer();
	static void InitModel();
	static void DeleteModel();

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void SpecialKeys(const int& key, const int& x, const int& y);
	void Update();
	void Render();

	float Get_VectorX() const noexcept { return m_vector_x; }
	float Get_VectorY() const noexcept { return m_vector_y; }
	float Get_VectorZ() const noexcept { return m_vector_z; }

	const float Get_JumpReach() const noexcept { return m_JumpReach; }
	const int Get_BoardNum() const noexcept { return m_BoardNum; }
	const int Get_Side() const noexcept { return m_MySide; }

	//Mediator
	virtual void Player_JumpStart();
	virtual void Player_Jumping();
	virtual void Player_JumpFinish();
	virtual void Player_Dead();
};

