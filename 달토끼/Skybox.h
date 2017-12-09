#pragma once

class CStar;

class CSkybox
{
	CStar* m_Stars{nullptr};
	int m_StarNum{ 3000 };

public:
	CSkybox(const int& z);
	~CSkybox();

	void Render();
	void Update();
};

