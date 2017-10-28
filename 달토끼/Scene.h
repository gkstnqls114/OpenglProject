#pragma once

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void Initialize() {}
	virtual void Render() {}
	virtual void Reshape(int w, int h){}
	virtual void Timer(int value) {}
	virtual void Update() {};
	virtual void Keyboard(unsigned char key, int x, int y) {};

};

