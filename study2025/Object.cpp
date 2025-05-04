#include "pch.h"
#include "Object.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

Object::Object()
	: vPos{}
	, vScale{}
{
}

Object::~Object()
{
}

void Object::Update()
{
	if (KeyMgr::Instance()->GetKetState(KEY::W) == KEY_STATE::HOLD) {
		vPos.y -= 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKetState(KEY::S) == KEY_STATE::HOLD) {
		vPos.y += 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKetState(KEY::A) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * DT;
	}
	if (KeyMgr::Instance()->GetKetState(KEY::D) == KEY_STATE::HOLD) {
		vPos.x += 200.f * DT;
	}
}

void Object::Render(HDC _hdc)
{
	Rectangle(_hdc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);
}
