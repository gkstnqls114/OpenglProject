#pragma once

class Scene
{
protected:
	void RenderAxis();

public:
	Scene();
	virtual ~Scene();

	virtual void Initialize() {}
	virtual void SoundStop() {}
	virtual void Render() {}
	virtual void Reshape(const int& w, const int& h) = 0;
	virtual void Timer(const int& value) = 0;
	virtual void Update() = 0;
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y) = 0;
	virtual void SpecialKeys(const int& key, const int& x, const int& y) = 0;
};

