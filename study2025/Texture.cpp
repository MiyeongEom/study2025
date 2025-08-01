#include "pch.h"
#include "Texture.h"

#include "Core.h"

Texture::Texture()
	: hdc(0)
	, bit(0)
	, info{}
{
}

Texture::~Texture()
{
	DeleteDC(hdc);
	DeleteObject(bit);
}

void Texture::Load(const wstring& _str)
{
	bit = (HBITMAP)LoadImage(nullptr, _str.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(bit);

	// ��Ʈ���̶� ������ DC
	hdc = CreateCompatibleDC(Core::Instance()->GetMainDC());

	// ��Ʈ�� DC ����
	HBITMAP preBit = (HBITMAP)SelectObject(hdc, bit);
	DeleteObject(preBit);

	// ���� 
	GetObject(bit, sizeof(BITMAP), &info);
}
