#pragma once

class Res {
	// ���ҽ��� �⺻������ ������ �Ǵ� ����
private:
	wstring			key;					// ���� ID
	wstring			strRelativePath;		// ���ҽ� ��� ��� (���� ���� ���� ������ �ʴ� �κ�)

public:
	Res();
	~Res();

	void			SetKey(const wstring _key) { key = _key; }
	void			SetPath(const wstring& _str) { strRelativePath = _str; }

	const wstring&	GetKey() { return key; }
	const wstring&	GetPath() { return strRelativePath; }
};