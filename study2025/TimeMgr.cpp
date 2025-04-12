#include "pch.h"
#include "TimeMgr.h"

#include "Core.h"

TimeMgr::TimeMgr()
	:curCount{}
	,prevCount{}
	,frequency{}
	,dDT(0.)
	,dAcc(0.)
	,iCallCount(0)
	,iFPS(0)
{

}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::Init()
{
	QueryPerformanceCounter(&prevCount);
	QueryPerformanceFrequency(&frequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&curCount);

	// �� ������ ���� �ð� ��
	dDT = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
	prevCount = curCount;

	++iCallCount;
	dAcc += dDT;

	if (dAcc >= 1.) {
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;
	}

	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
	SetWindowText(Core::Instance()->getMainHandle(), szBuffer);
}
