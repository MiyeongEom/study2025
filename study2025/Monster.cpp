#include "pch.h"
#include "Monster.h"

#include "TimeMgr.h"

Monster::Monster()
	:speed(100.f)
	, centerPos(Vec2(0.f, 0.f))
	, maxDis(50.f)
	, dir(1)
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 curPos = getPos(); 

	// l-value / r-value

	// 진행 방향으로 시간당 speed만큼 이동
	curPos.x += fDT * speed * dir;

	// 배회 거리 기준점을 넘어섰는지 확인
	float dist = abs(centerPos.x - curPos.x) - maxDis;

	// 넘어섰다면 방향 변경하면 됨
	if (0.f < dist) {
		dir *= -1;
		curPos.x += dist * dir;
	}

	setPos(curPos);
}

