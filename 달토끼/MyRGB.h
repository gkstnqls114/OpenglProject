#pragma once
class CMyRGB
{
	float m_r { 1.f };
	float m_g { 1.f };
	float m_b { 0.f };
	float m_a{ 1.f };

public:
	CMyRGB();
	~CMyRGB();

	void ColorSelect();
	
	//�ӽ÷� ���
	void Disappear();
};

