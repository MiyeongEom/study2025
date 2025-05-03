#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Object.h"

Object obj;

Core::Core()    // 변수 초기화
    :handle(0)
    , ptResolution{}
    , hDC(0)
    , hBit(0)
    , mDC(0)
{
}

Core::~Core()
{
    ReleaseDC(handle, hDC);        // hDC 해제하는 부분

    DeleteDC(mDC);
    DeleteObject(hBit);
}

int Core::Init(HWND _handle, POINT _ptResolution)        // class 객체가 시작할 때 초기화해야 하는 부분
{
    handle = _handle;
    ptResolution = _ptResolution;

    RECT rt = { 0,0, ptResolution.x, ptResolution.y };

    // Manager
    TimeMgr::Instance()->Init();
    KeyMgr::Instance()->Init();

    //    실제로 그릴 수 있는 영역을 계산한다.
    //    메뉴바나 윈도우 창 주변으로 생겨있는 테두리 영역을 제외한 영역을 계산한다.
    //    1. 윈도우 크기와 위치를 지정하는 rect 구조체에 대한 포인터
    //    2. 윈도우 스타일 (모양/동작 - 테두리, 제목 표시줄, 크기 조정이 가능한지 등등)
    //    3. 메뉴바 생성 여부
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

    //    RECT 구조체를 이용해서 윈도우 크기를 조정하고 있는데, 아래의 함수는 윈도우릐 위치와 크기를 설정한다.
    //    1. hWnd : 윈도우 핸들
    //    2. hWndInsertAfter : 새로운 z순서를 설정    :    윈도우가 겹쳤을때 먼저나타낼 순서
    //    3. X : 윈도우의 X 좌표
    //    4. Y : 윈도우의 Y 좌표
    //    5. cx : 윈도우의 너비
    //    6. cy : 윈도우의 높이
    //    7. uuFlags : 윈도우의 위치와 크기를 설정하는데 사용되는 플래그
    //
    SetWindowPos(handle, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

    hDC = GetDC(handle);

    // 이중 버퍼링 용도의 비트맵과 DC를 만들어야 함.
    hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);  // 같은 해상도 크기의 비트맵을 하나 만든거야.

    // 핸들 아이디를 받아서 이 비트맵을 상대로 하는 DC를 생성한다.
    mDC = CreateCompatibleDC(hDC);

    // 새로 생성된 비트맵을 DC에 선택해서 이 비트맵에 그림을 그리도록 설정
    //  -> 이전에 선택된 비트맵을 반환하고 사용이 끝난 후에 메모리를 누수를 방지해야 해서 삭제하는 일을 진행
    HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
    DeleteObject(hOldBit);

    obj.setPos(Vec2((float)(ptResolution.x / 2), (float)(ptResolution.y / 2)));
    obj.setScale(Vec2(100, 100));

    return S_OK;    // HRESULT
}

void Core::Progress()
{
    TimeMgr::Instance()->Update();
    KeyMgr::Instance()->Update();

    Update();
    Render();
}

void Core::Update()
{
    Vec2 vPos = obj.getPos();

    if (KeyMgr::Instance()->GetKetState(KEY::LEFT)==KEY_STATE::AWAY) {
        vPos.x -= 200.f * DT;
    }
    if (KeyMgr::Instance()->GetKetState(KEY::RIGHT) == KEY_STATE::AWAY) {
        vPos.x += 200.f * DT;
    } 

    obj.setPos(vPos);
}


void Core::Render()
{
    Rectangle(hDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

    Vec2 vPos = obj.getPos();
    Vec2 vScale = obj.getScale();

    Rectangle(hDC,
        int(vPos.x - vScale.x / 2.f),
        int(vPos.y - vScale.y / 2.f),
        int(vPos.x + vScale.x / 2.f),
        int(vPos.y + vScale.y / 2.f));

    // 완성된 그림을 복사하는 코드
    BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y,   // 목적지, 복사 받을 부위
        mDC, 0, 0, SRCCOPY);   // 복사 대상

}


// Key Manager
// : 1) A와 B물체가 이동하는 게임이다. 키 매니저가 없으면 자신의 키 입력을 개별적으로 처리하게 된다. 
//      수 백번의 상황 중에 A 물체는 현재 프레임(시간)에 이동을 처리하지만, B는 다음 프레임에서 이동이 처리될 수 있다. 
// : 2) 우리가 점프를 하는 게임이야. 점프킹. 짧게 눌럿을 때랑 길게 눌렀을 때랑 날라가는 폭이 다른 게임이다. 이를 어떻게 구현??


// 우리 작업하는 구조 : 매 순간 UPDATE 확인하고 있음 -> 업데이트 끝났을 때 변경점을 반영해서 랜더(Render) 
// 우리 한 프레임 시간(DT)이 지난 후의 결과값을 볼 수 있다. 따로따로 이동하는 것을 볼 수 없지.
// 같은 프레임 내에서 A -> B (같은 DT) 볼 수 없다. (같이 움직이는걸로 보인다)
// 한 프레임에서 적용된 키는 같은 이벤트로 처리되어야 한다 (규칙)

// [역할]
// 1. 프레임 동기화 : 동일 프레임 내에 일어난 일은 같은 키에 대해 동일한 이벤트로 처리한다.
// 2. 키 입력을 여러 이벤트로 나눠 처리할 수 있다 : TAP, HOLD, AWAY, NONE



