#pragma once

#define RCMAX 256
struct UI_CharacterBar
{
	RECT rc;
	LPDIRECT3DTEXTURE9 img;
	float x, y;

};



class cUI_CharacterBar
{
	UI_CharacterBar m_UICharacterBar;
	UI_CharacterBar m_UICharacterBarBack;

	UI_CharacterBar m_UIHPBar;
	UI_CharacterBar m_UIMPBar;

	float rcMaxHP;   // �׷��� RC�ִ� ��.
	float rcCurHP;   // RC ���� ���� ��.
	
	float rcMaxMP;   // �׷��� RC�ִ� ��.
	float rcCurMP;   // RC ���� ���� ��.
	
	float playerMaxHP; // �÷��̾� �ִ� HP
	float playerCurHP; // ����  

	float playerMaxMP; // �÷��̾� �ִ� MP
	float playerCurMP; // ����

	float damage; // ������ ���ÿ�

	char strHp[32];
	char strSp[32];

public:
	cUI_CharacterBar();
	~cUI_CharacterBar();
	//�׽�Ʈ��
	void init();
	void update();

	//HP�� ���¿�
	void init(float userMaxHP, float userMaxMP);

	//HP, MP ���� ���¿�
	void update(float userCurrentHP,float userCurrentMP);

	void uiRender();
	void fontRender();

};

