#pragma once

class Object {
private:
	Vec2	vPos;
	Vec2	vScale;

public:
	Object();
	virtual ~Object();

	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vSacle) { vScale = _vSacle; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale () { return vScale; }

public:
	virtual void Update()= 0;
	virtual void Render(HDC _hdc);
};