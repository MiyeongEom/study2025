#include "pch.h"
#include "Player.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "Scene.h"
#include "Missile.h"

void Player::Update()
{
	Vec2 vPos = getPos();

	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * DT;
	}
	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * DT;
	}
	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * DT;
	}
	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * DT;
	}
	if (KEY_HOLD(KEY::SPACE)) {
		CreateMissile();
	}

	setPos(vPos);
}

void Player::CreateMissile()
{
	Vec2 missilePos = getPos();
	missilePos.y -= getScale().y / 2.f;

	Missile* missile = new Missile;
	missile->setPos(missilePos);
	missile->setScale(Vec2(25.f, 25.f));
	missile->SetDir(true);

	// ���� ���� ����
	Scene* curScenes = SceneMgr::Instance()->GetCurScene();
	curScenes->AddObject(missile, GROUP_TYPE::DEFAULT);
}
