#include "pch.h"
#include "KeyMgr.h"

int arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
};

KeyMgr::KeyMgr()
{

}

KeyMgr::~KeyMgr()
{

}

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		vecKey.emplace_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

void KeyMgr::Update()
{
	// ������ â�� ��Ŀ���ϳ�?
	HWND hWnd = GetFocus();

	if (nullptr != hWnd) {
		// ��� Ű�� ���ؼ�
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			// Ű�� ���ȴ���?
			if (GetAsyncKeyState(arrVK[i]) & 0x8000) {
				if (vecKey[i].prev)
					vecKey[i].state = KEY_STATE::HOLD;
				else
					vecKey[i].state = KEY_STATE::TAP;
				vecKey[i].prev = true;
			}
			else {
				if (vecKey[i].prev) {	
					vecKey[i].state = KEY_STATE::AWAY;
				}
				else {
					vecKey[i].state = KEY_STATE::NONE;
				}
				vecKey[i].prev = false;
			}
		}
	}
	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			vecKey[i].prev = false;
			if (KEY_STATE::TAP == vecKey[i].state || KEY_STATE::HOLD == vecKey[i].state)
				vecKey[i].state = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == vecKey[i].state)
				vecKey[i].state = KEY_STATE::NONE;
		}
	}
}
