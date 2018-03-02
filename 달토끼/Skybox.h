#pragma once

class Spacestar;

class CSkybox
{
	Spacestar* m_Stars{nullptr};
	int m_StarNum{ 3000 };

public:
	CSkybox(const int& z);
	~CSkybox();

	void Render();
	void Update();
};

