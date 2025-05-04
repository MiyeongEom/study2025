#include "pch.h"
#include "Player.h"

#include "KeyMgr.h"
#include "TimeMgr.h"

void Player::Update()
{
	Vec2 vPos = getPos();

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

	setPos(vPos);
}
