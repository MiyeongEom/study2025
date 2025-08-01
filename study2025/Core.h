#pragma once

class Core{
	SINGLE(Core);
private:
	HWND		handle;			// 클래스 내부에 창 핸들 변수
	POINT		ptResolution;	// 해상도를 받을 변수
	HDC			hDC;			// 그리기 위한 변수

	HBITMAP		hBit;
	HDC			mDC;

public:
	int			Init(HWND _handle, POINT _ptResolution);
	void		Progress();

	HWND		getMainHandle() { return handle; }
	POINT		getResolution() { return ptResolution; }
	HDC			GetMainDC() { return hDC; }
};	