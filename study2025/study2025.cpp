﻿// study2025.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "study2025.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STUDY2025, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDY2025));
 
    MSG msg;

    // 기본 메시지 루프입니다:
    // GetMessage : 메세지큐에서 메세지 확인 될 때까지 대기
    // msg.message == WM_QUIT일 경우 false 반환 -> 프로그램 종료
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//  함수: MyRegisterClass()
//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDY2025));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STUDY2025);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우 창 만들기(OS 관할) -> 여러 함수와 ID 존재 -> 우리(프로그래머)는 이를 이용해서 코딩해야 한다 !
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.

struct tObjInfo {
    POINT objPos;       // 중심좌표
    POINT objScale;     // 중심좌표로부터의 크기
};

vector<tObjInfo> vecInfo;   // 사각형의 정보를 저장하는 vector

POINT ptLT;             // 마우스를 눌렀을 때의 좌표
POINT ptRB;             // 마우스를 뗐을 때의 좌표
bool act = false;       // 사각형을 무작정 그리지 않기 위해 만든 bool변수

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  // 무효화 영역이 발생해야 한다 : 다시 그려야 하는 영역이 발생할 경우 -> 출력은 무조건 여기서 처리
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HPEN hRedPen = CreatePen(BS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

            HPEN hDefPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefBrush = (HBRUSH)SelectObject(hdc, hBlackBrush);

            if (act) {
                Rectangle(hdc, ptLT.x, ptLT.y, ptRB.x, ptRB.y);
            }

            for (size_t i = 0; i < vecInfo.size(); ++i) {
                Rectangle(hdc,
                    vecInfo[i].objPos.x - vecInfo[i].objScale.x / 2,
                    vecInfo[i].objPos.y - vecInfo[i].objScale.y / 2,
                    vecInfo[i].objPos.x + vecInfo[i].objScale.x / 2,
                    vecInfo[i].objPos.y + vecInfo[i].objScale.y / 2);
            }

            SelectObject(hdc, hDefPen);
            SelectObject(hdc, hDefBrush);
            DeleteObject(hRedPen);
            DeleteObject(hDefBrush);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN: 
    {
        ptLT.x = LOWORD(lParam);
        ptLT.y = HIWORD(lParam);
        act = true;
    }
        break;

    case WM_MOUSEMOVE:
    {
        ptRB.x = LOWORD(lParam);
        ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);  // 전체 영역을 초기화 다시 그리는 애 -> 더블버퍼링 !
    }
        break;

    case WM_LBUTTONUP:
    {
        tObjInfo info {};

        info.objPos.x = (ptLT.x + ptRB.x) / 2;
        info.objPos.y = (ptLT.y + ptRB.y) / 2;

        info.objScale.x = abs(ptLT.x - ptRB.x);
        info.objScale.y = abs(ptLT.y - ptRB.y);

        vecInfo.push_back(info);
        act = false;
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    /*case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            objPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_DOWN:
            objPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            objPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            objPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'W': 
            break;
        }
    }
        break; */
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
