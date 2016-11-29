#pragma once
#include "cCamera.h"

#define TEX_WIDTH 32
#define TEX_HEIGHT 64

struct stDamage
{
	int unit;					//1���ڸ� ��
	int	tens;					//10���ڸ� �� 
	int hund;					//100���ڸ� ��
	int thou;					//1000���ڸ� ��
	RECT unit_Rc;				//1���ڸ� ��Ʈ	
	RECT tens_Rc;				//10���ڸ� ��Ʈ
	RECT hund_Rc;				//100���ڸ� ��Ʈ
	RECT thou_Rc;				//1000���ڸ� ��Ʈ
	LPDIRECT3DTEXTURE9 unit_tex;	// �̹�����
	LPDIRECT3DTEXTURE9 tens_tex;
	LPDIRECT3DTEXTURE9 hund_tex;
	LPDIRECT3DTEXTURE9 thou_tex;
	float unit_x, unit_y;						// ȭ�鿡 �׷��� ��ǥ. 
	float countTime;			//ī��Ʈ�ҽð�
	float time;					//�����ð�

	bool isDrawing;			//�׷�������?
};


class cShowDamage
{
private:
	std::vector<stDamage> v_damage;		//������ ����ü ����
	std::vector<stDamage>::iterator vi_damage;		//������ ����ü ����
	
	int num;				//������ ����
	int size; 		//���ͻ�����

	//float m_time;
	//bool  m_isDrawing;

public:
	cShowDamage();
	~cShowDamage();

	void Init();

	void SetNumber(int number, cTransform* trans);
	void Release();
	void Update(float timeDelta);
	void Render();
};

