#pragma once
#include "Object.h"

class Missile : public Object {
private:
	float	theta;  // 방향을 각도로 받는다면? vector Normalize!!
	Vec2	dir;

public:
	Missile();
	~Missile();

	virtual void Update();
	virtual void Render(HDC _hdc);

	void SetDir(bool _th) { theta = _th; }
	void SetDir(Vec2 _dir)
	{
		dir = _dir;
		dir.Normalize();
	}
};

