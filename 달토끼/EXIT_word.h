#pragma once

class CObjModel;
class CMatrix;

class CEXIT_word
{
	CObjModel* m_model{ nullptr };

public:
	CEXIT_word();
	~CEXIT_word();

	void Render();
	void Update();
};

