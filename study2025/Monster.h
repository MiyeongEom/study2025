#pragma once
#include "Object.h"

class Monster : public Object {
private:
	float		speed;
	float		maxDis;		// �ִ� �̵��Ÿ�
	int			dir;		// ����
	Vec2		centerPos;	// �߾� ���ذ�

public:
	Monster();
	~Monster();

	virtual void Update();

	float GetSpeed() { return speed; }
	Vec2 GetCenterPos() { return centerPos; }

	void SetSpeed(float spd) { speed = spd; }
	void SetMoveDist(float dis) { maxDis = dis; }
	void SetCenterPos(Vec2 pos) { centerPos = pos; }
}; 