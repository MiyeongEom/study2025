#include "pch.h"
#include "Scene_Start.h"

#include "Core.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	Object* obj = new Player;

	obj->setPos(Vec2(604.f, 348.f));
	obj->setScale(Vec2(100.f, 100.f));

	AddObject(obj, GROUP_TYPE::DEFAULT);

	// Monster
	int monCount = 5;
	float moveDist = 25.f;
	float objScale = 50.f;
	Vec2 resolution = Core::Instance()->getResolution();
	float term = (resolution.x - ((moveDist + objScale / 2.f) * 2)) / (float)(monCount - 1);

	Monster* monObj = nullptr;
	for (int i = 0; i < monCount; ++i) {
		monObj = new Monster;
		monObj->SetCenterPos(Vec2((moveDist + objScale / 2.f) + (float)i * term, 50.f));
		monObj->setPos(Vec2(monObj->GetCenterPos()));
		monObj->SetMoveDist(moveDist);
		monObj->setScale(Vec2(objScale, objScale));
		AddObject(monObj, GROUP_TYPE::DEFAULT);
	}
}

void Scene_Start::Exit()
{
}


// 다음 주 한시간은 숙제 검사
// 1) 지금까지 한 수업 + 코드관련해서 시각적으로 정리하기 (FlowChart)
// 2) 플레이어 기준으로 space바 누르면 미사일(원) 발사