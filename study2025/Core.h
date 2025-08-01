#pragma once

class Core{
	SINGLE(Core);
private:
	HWND		handle;			// Ŭ���� ���ο� â �ڵ� ����
	POINT		ptResolution;	// �ػ󵵸� ���� ����
	HDC			hDC;			// �׸��� ���� ����

	HBITMAP		hBit;
	HDC			mDC;

public:
	int			Init(HWND _handle, POINT _ptResolution);
	void		Progress();

	HWND		getMainHandle() { return handle; }
	POINT		getResolution() { return ptResolution; }
	HDC			GetMainDC() { return hDC; }
};	