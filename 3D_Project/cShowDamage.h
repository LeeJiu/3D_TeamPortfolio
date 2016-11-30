#pragma once
#include "cCamera.h"

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

struct stDamage
{
	int unit;					//1���ڸ� ��
	int	tens;					//10���ڸ� �� 
	int hund;					//100���ڸ� ��
	int thou;					//1000���ڸ� ��
	int mil;
	RECT Rc;				// ��Ʈ	
	LPDIRECT3DTEXTURE9 unit_tex;	// �̹�����
	LPDIRECT3DTEXTURE9 tens_tex;
	LPDIRECT3DTEXTURE9 hund_tex;
	LPDIRECT3DTEXTURE9 thou_tex;
	LPDIRECT3DTEXTURE9 mil_tex;
	float unit_x, unit_y;						// ȭ�鿡 �׷��� ��ǥ. 
	float countTime;			//ī��Ʈ�ҽð�
	float time;					//�����ð�

	bool isDrawing;			//�׷�������?
	bool isEnd;			//�׷�������?
};


class cShowDamage
{
private:
	std::vector<stDamage> v_damage;		//������ ����ü ����
	std::vector<stDamage>::iterator vi_damage;		//������ ����ü ����
	
	D3DXVECTOR2 pos;

	int num;				//������ ����
	int size; 				//���ͻ�����

public:
	cShowDamage();
	~cShowDamage();

	void Init();

	void SetNumber(int number, cTransform* trans, cCamera* cam);
	void Release();
	void Clean();
	void Update(float timeDelta);
	void Render();
};

