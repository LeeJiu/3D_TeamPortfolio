#pragma once
#define SKILLNUM 5
struct stUi
{
	RECT rcSize;					// ��ų ��Ʈ �簢��
	RECT rcColl;                    // �浹 �� ��Ʈ
	LPDIRECT3DTEXTURE9 skillImage;	//�̹���
	float x, y;						//ȭ�鿡 �׷��� ��ǥ. 
	
	//LPDIRECT3DTEXTURE9 emtyImage;
};

class cSkillUi
{
	stUi skillBotton[SKILLNUM];
	
	stUi emtyBotton;


	//LPDIRECT3DTEXTURE9 emtyImage;


public:
	cSkillUi();
	~cSkillUi();
	
	void init();
	void update();

	void uiRender();

};

