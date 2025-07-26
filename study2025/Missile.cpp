#include "pch.h"
#include "Missile.h"

#include "TimeMgr.h"

Missile::Missile()
	:dir(1.f)
{
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vec2 vPos = getPos();

	vPos.y += 600.f * fDT * (float)dir;

	setPos(vPos);
}

void Missile::Render(HDC _hdc)
{
	Vec2 vPos = getPos();
	Vec2 vScale = getScale();

	// ¿øÇü
	Ellipse(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

}
