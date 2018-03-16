#pragma 
#include "PlayerSubject.h"
#include "RoadSubject.h"

#include "Star.h"

#include "Scene.h"

class CSceneManager;
class CTextureStorage;
class PlayerSubject;
class RoadObserver;
class Road;

class CTestScene :
	public Scene
{
	PlayerSubject		m_PlayerObserver	;
	RoadSubject			m_RoadObserver		;
	CPlayer *			m_Player			{ nullptr };
	Road *				m_Road				{ nullptr };
	CCamera*			m_Camera			{ nullptr };
	
	GLint				texture_object		{ 0 };
	CTextureStorage*	m_texture			{ nullptr };


public:
	CTestScene();
	virtual ~CTestScene();

	virtual void Initialize();
	virtual void SoundStop();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};
