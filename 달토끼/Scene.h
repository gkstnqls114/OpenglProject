#pragma once

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void Initialize() {}
	virtual void Render() {}
	virtual void Reshape(const int& w, const int& h){}
	virtual void Timer(const int& value) {}
	virtual void Update() {};
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y) {};
	virtual void SpecialKeys(const int& key, const int& x, const int& y) {};
};

