#pragma once

class CPlayer;

class CColleague
{

public:
	CColleague();
	~CColleague();

	virtual void Render() {};
	virtual void Update() {};

	virtual void Notify(const CPlayer* player) {};
};
