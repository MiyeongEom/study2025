#pragma once

class TimeMgr
{
	SINGLE(TimeMgr);
private:
	LARGE_INTEGER	curCount;
	LARGE_INTEGER	prevCount;
	LARGE_INTEGER	frequency;

	double			dDT;
	double			dAcc;
	UINT			iCallCount;
	UINT			iFPS;

public:
	void			Init();
	void			Update();

	double			getDT() { return dDT; }
	float			getfDT() { return (float)dDT; }
};

// ���� ������ �ð��� "FPS"�� ǥ���ȴ�.

// 1�ʿ� 2�������̾�. 1������ 0.5��
// 1�ʿ� 10�������̾�. 1������ 0.1��
// => �������� ���� = �� ������ �� �ɸ��� �ð�

// LAGRE_INTEGER : 64��Ʈ ����
//  1. curCount : ���� �ð�
//  2. prevCount : ���� �ð�
//  3. frequency : ���� ī���Ͱ� �ʴ� �� �� �ƴ� ? (�ֱ�)

// dDT : �� ������ ������ �ð� �� ( ���� �ð��� ���� �ð��� ���̸� ���� -> �ý��� ���� ī���� ���ļ��� ������ �� )
// dAcc : ���� ��� �ð� ( 1�ʸ� �ʰ��ϸ� FPS ����ϰ� �ʱ�ȭ )
// iCallCount : Update�Լ��� ȣ�� Ƚ�� ����
// iFPS : ������ �ӵ� ( = 1�ʴ� Update ȣ�� Ƚ�� )
