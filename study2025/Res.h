#pragma once

class Res {
	// 리소스가 기본적으로 가져야 되는 정보
private:
	wstring			key;					// 고유 ID
	wstring			strRelativePath;		// 리소스 상대 경로 (실행 파일 기준 변하지 않는 부분)

public:
	Res();
	~Res();

	void			SetKey(const wstring _key) { key = _key; }
	void			SetPath(const wstring& _str) { strRelativePath = _str; }

	const wstring&	GetKey() { return key; }
	const wstring&	GetPath() { return strRelativePath; }
};