#include "pch.h"
#include "SceneMgr.h"

#include "Scene_Start.h"

SceneMgr::SceneMgr()
	:arrScene{}
	,currScene(nullptr)
{

}

SceneMgr::~SceneMgr()
{

}

void SceneMgr::Init()
{
	// Scene ����
	arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// arrScene[(UINT)SCENE_TYPE::STAGE_01] = new STAGE_01;
	// arrScene[(UINT)SCENE_TYPE::STAGE_02] = new STAGE_02;

	// ���� �� ����
	currScene = arrScene[(UINT)SCENE_TYPE::START];
	currScene->Enter();
}

void SceneMgr::Update()
{
	currScene->Update();
}

void SceneMgr::Render(HDC _hdc)
{
	currScene->Render(_hdc);
}
