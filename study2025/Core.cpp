#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"

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

    Update();
    Render();
}

void Core::Update()
{
    Vec2 vPos = obj.getPos();

    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        vPos.x -= 200.f * DT;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
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

