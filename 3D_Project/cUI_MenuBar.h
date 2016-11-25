#pragma once
#define MENUBARNUM 5

struct UI_MenuBtn
{
	RECT rc;
	RECT rcColl;
	LPDIRECT3DTEXTURE9 img;
	float x, y;
	bool isClick;

};

class cUI_MenuBar
{
	UI_MenuBtn m_menuBtn[MENUBARNUM];



public:
	cUI_MenuBar();
	~cUI_MenuBar();

	void init();
	void update();
	void uiRender();

	bool GetIsOptionClick() { return m_menuBtn[0].isClick; } //옵션
	bool GetIsPlayerInfoClick() { return m_menuBtn[1].isClick; } //플레이어
	bool GetIsSkillInfoClick() { return m_menuBtn[2].isClick; } //스킬정보
	bool GetIsInventoryClick() { return m_menuBtn[3].isClick; } //인벤
	bool GetIsMapClick() { return m_menuBtn[4].isClick; } //맵
};

