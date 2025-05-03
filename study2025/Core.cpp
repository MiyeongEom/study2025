#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Object.h"

Object obj;

Core::Core()    // ���� �ʱ�ȭ
    :handle(0)
    , ptResolution{}
    , hDC(0)
    , hBit(0)
    , mDC(0)
{
}

Core::~Core()
{
    ReleaseDC(handle, hDC);        // hDC �����ϴ� �κ�

    DeleteDC(mDC);
    DeleteObject(hBit);
}

int Core::Init(HWND _handle, POINT _ptResolution)        // class ��ü�� ������ �� �ʱ�ȭ�ؾ� �ϴ� �κ�
{
    handle = _handle;
    ptResolution = _ptResolution;

    RECT rt = { 0,0, ptResolution.x, ptResolution.y };

    // Manager
    TimeMgr::Instance()->Init();
    KeyMgr::Instance()->Init();

    //    ������ �׸� �� �ִ� ������ ����Ѵ�.
    //    �޴��ٳ� ������ â �ֺ����� �����ִ� �׵θ� ������ ������ ������ ����Ѵ�.
    //    1. ������ ũ��� ��ġ�� �����ϴ� rect ����ü�� ���� ������
    //    2. ������ ��Ÿ�� (���/���� - �׵θ�, ���� ǥ����, ũ�� ������ �������� ���)
    //    3. �޴��� ���� ����
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

    //    RECT ����ü�� �̿��ؼ� ������ ũ�⸦ �����ϰ� �ִµ�, �Ʒ��� �Լ��� ������l ��ġ�� ũ�⸦ �����Ѵ�.
    //    1. hWnd : ������ �ڵ�
    //    2. hWndInsertAfter : ���ο� z������ ����    :    �����찡 �������� ������Ÿ�� ����
    //    3. X : �������� X ��ǥ
    //    4. Y : �������� Y ��ǥ
    //    5. cx : �������� �ʺ�
    //    6. cy : �������� ����
    //    7. uuFlags : �������� ��ġ�� ũ�⸦ �����ϴµ� ���Ǵ� �÷���
    //
    SetWindowPos(handle, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

    hDC = GetDC(handle);

    // ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ������ ��.
    hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);  // ���� �ػ� ũ���� ��Ʈ���� �ϳ� ����ž�.

    // �ڵ� ���̵� �޾Ƽ� �� ��Ʈ���� ���� �ϴ� DC�� �����Ѵ�.
    mDC = CreateCompatibleDC(hDC);

    // ���� ������ ��Ʈ���� DC�� �����ؼ� �� ��Ʈ�ʿ� �׸��� �׸����� ����
    //  -> ������ ���õ� ��Ʈ���� ��ȯ�ϰ� ����� ���� �Ŀ� �޸𸮸� ������ �����ؾ� �ؼ� �����ϴ� ���� ����
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

    // �ϼ��� �׸��� �����ϴ� �ڵ�
    BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y,   // ������, ���� ���� ����
        mDC, 0, 0, SRCCOPY);   // ���� ���

}


// Key Manager
// : 1) A�� B��ü�� �̵��ϴ� �����̴�. Ű �Ŵ����� ������ �ڽ��� Ű �Է��� ���������� ó���ϰ� �ȴ�. 
//      �� ����� ��Ȳ �߿� A ��ü�� ���� ������(�ð�)�� �̵��� ó��������, B�� ���� �����ӿ��� �̵��� ó���� �� �ִ�. 
// : 2) �츮�� ������ �ϴ� �����̾�. ����ŷ. ª�� ������ ���� ��� ������ ���� ���󰡴� ���� �ٸ� �����̴�. �̸� ��� ����??


// �츮 �۾��ϴ� ���� : �� ���� UPDATE Ȯ���ϰ� ���� -> ������Ʈ ������ �� �������� �ݿ��ؼ� ����(Render) 
// �츮 �� ������ �ð�(DT)�� ���� ���� ������� �� �� �ִ�. ���ε��� �̵��ϴ� ���� �� �� ����.
// ���� ������ ������ A -> B (���� DT) �� �� ����. (���� �����̴°ɷ� ���δ�)
// �� �����ӿ��� ����� Ű�� ���� �̺�Ʈ�� ó���Ǿ�� �Ѵ� (��Ģ)

// [����]
// 1. ������ ����ȭ : ���� ������ ���� �Ͼ ���� ���� Ű�� ���� ������ �̺�Ʈ�� ó���Ѵ�.
// 2. Ű �Է��� ���� �̺�Ʈ�� ���� ó���� �� �ִ� : TAP, HOLD, AWAY, NONE



