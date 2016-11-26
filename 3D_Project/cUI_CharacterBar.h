#pragma once

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

	int damage;
	int currecntHP;
	int maxHP;

	int usedMP;
	int currecntMP;
	int maxMP;

public:
	cUI_CharacterBar();
	~cUI_CharacterBar();

	void init();
	void update();
	void uiRender();

};

