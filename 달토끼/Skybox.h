#pragma once

class CStar;

class CSkybox
{
	CStar* m_Stars{nullptr};
	int m_StarNum{ 3000 };

public:
	CSkybox();
	~CSkybox();

	void Render();
	void Update();
};

