#include "pch.h"
#include "Missile.h"

#include "TimeMgr.h"

Missile::Missile()
	:theta(PI/4.f)
	,dir(Vec2(1.f, 1.f))
{
	dir.Normalize();
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vec2 vPos = getPos();

	// vPos.x += 600.f * cosf(theta) * fDT;
	// vPos.y -= 600.f * sinf(theta) * fDT;

	vPos.x += 600.f * dir.x * fDT;
	vPos.y += 600.f * dir.y * fDT;

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
