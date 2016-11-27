#pragma once
#define SKILLNUM 5

struct UI_Deck
{
	RECT rc;
	LPDIRECT3DTEXTURE9 img;
	float x, y;

};

struct UI_SkillBtn
{
	RECT rc;
	RECT rcColl; //��ų �浹�뷺Ʈ
	LPDIRECT3DTEXTURE9 img;
	float x, y;
	bool isClick;

};

class cUI_SkillDeck
{
	UI_Deck m_UIDeck;  //��ų ��
	UI_Deck m_UIDeckNumFront;

	UI_Deck m_UIDeckBack; //������ �� �� ��
	UI_Deck m_UIDeckNumBack;

	UI_SkillBtn m_UISkillBtn[SKILLNUM]; //��ų��ư

	bool isClick;

	bool isMage;
	bool isBerserker;

public:
	cUI_SkillDeck();
	~cUI_SkillDeck();

	void init();
	void update();
	void uiRender();

	bool GetSkillBtnFirstClick() { return m_UISkillBtn[0].isClick; }
	bool GetSkillBtnSecondClick() { return m_UISkillBtn[1].isClick; }
	bool GetSkillBtnThirdClick() { return m_UISkillBtn[2].isClick; }
	bool GetSkillBtnForthClick() { return m_UISkillBtn[3].isClick; }
	bool GetSkillBtnFifthClick() { return m_UISkillBtn[4].isClick; }
};

