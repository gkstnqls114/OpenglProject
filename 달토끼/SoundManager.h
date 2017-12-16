#pragma once

#include "FMOD/inc/fmod.hpp"

#include <map>
#include <queue>
#include <memory>
#include <string>
#include <filesystem>

#include <windows.h>
//#include "Vector3.h"

using namespace std;
using namespace std::experimental::filesystem::v1;



void PushPlayQueue(string Tag, CVector3D<float>& position);
pair<string, CVector3D<float>> PopPlayQueue();
size_t PlayQueueSize();



class CFMODSystem
{
public:

	~CFMODSystem();
	static std::shared_ptr<CFMODSystem> Get();
	
	unsigned int GetCurrentVersion() const { return m_fmodVersion; }
	FMOD::System* GetSystem() const { return m_System; }

	FMOD_RESULT update() const;

	//���� �߰��Ȱ�
	static FMOD_RESULT set3DSettings(float dopplerscale, float distancefactor, float rolloffecale)
	{ return Get()->GetSystem()->set3DSettings(dopplerscale, distancefactor, rolloffecale); }
	//�� �Լ��� ���� update
	static FMOD_RESULT update(float fTimeElapsed, 
		CVector3D<float> vLook, CVector3D<float> vUp, CVector3D<float> vPosition);

	float GetVolume() const { return m_fVolume; }
	void SetVolumn(float fPercent) { m_fVolume = fmin(1.f, fmax(0.f, fPercent)); }
	
	bool IsMuteBGM() const { return m_bMuteBGM; }
	bool IsMuteEffect() const { return m_bMuteEffect; }

	void SetMuteBGM(bool bMute) { m_bMuteBGM = bMute; }
	void SetMuteEffect(bool bMute) { m_bMuteEffect = bMute; }

protected:

	CFMODSystem();

	FMOD::System		*m_System			{ nullptr }	;
	unsigned int		m_fmodVersion		{ 0 }		;

	bool				m_bNotInitPosition	{ true }	;
	CVector3D<float>	m_ptLast						;
	
	float				m_fVolume			{ 1.f }		;
	bool				m_bMuteBGM			{ false }	;
	bool				m_bMuteEffect		{ false }	;
};

using FMOD_System = std::shared_ptr<CFMODSystem>;
#define FMOD_System_Instance()	CFMODSystem::Get()
#define FMOD_System_Update()	CFMODSystem::Get()->update()



enum class SoundType
{
	  Unknown
	, Stream //��� �鸮�� ��׶���
	, Effect3D
	, Effect2D
};

class CSoundManager
{
public:

	struct SoundSet
	{
		SoundType type = SoundType::Unknown;

		FMOD::Sound* Sound = nullptr;
		FMOD::Channel* Channel = nullptr;

		~SoundSet()
		{
			if (Sound) Sound->release();
		}
	};

public:

	CSoundManager();
	~CSoundManager();

	//���� ���
	//path��� Ŭ����
	bool AddSound(string key, path szPath, SoundType SoundType);
	bool AddSound(string key, path szPath, float fMinDist, float fMaxDist);
	bool Play(string key);
	bool Play(string key, FMOD_VECTOR pos);
	bool Play(string key, CVector3D<float>& pos);
	void Stop(string key);
	void Stop() const;
	void Pause(string key, bool bPause);
	void inversePause(string key);
	
	void Set3DSoundAttributes(string key, float fMinDist, float fMaxDist);

protected:

	FMOD::System*	GetSystem() const { return m_System->GetSystem(); }

	FMOD_System								m_System;

	//���� ���
	//map�̶�� �ڷᱸ���� stl�ð��� ����
	//key "bgm" ,"explosion"
	//value :bgm�� �����Ǵ� ����, ���߿� �����Ǵ� ����...
	std::map<std::string, SoundSet>			m_Sound	;

};
