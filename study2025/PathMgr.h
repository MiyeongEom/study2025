#pragma once

// Debug vs Release
// ����� : ���� �����ϱ� ���� ���� �ܰ迡�� ����� ������ �ְ�
// ������ : ���� ����

class PathMgr {
	SINGLE(PathMgr);
private:
	wchar_t			contentPath[255];

public:
	void			Init();
	const wchar_t*	GetContentPath() { return contentPath; }
};

