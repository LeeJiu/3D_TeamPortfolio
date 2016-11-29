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

	float rcMaxHP;   // 그러줄 RC최대 값.
	float rcCurHP;   // RC 기준 현재 값.
	
	float rcMaxMP;   // 그러줄 RC최대 값.
	float rcCurMP;   // RC 기준 현재 값.
	
	float playerMaxHP; // 플레이어 최대 HP
	float playerCurHP; // 현재  

	float playerMaxMP; // 플레이어 최대 MP
	float playerCurMP; // 현재

	float damage; // 데미지 예시용

public:
	cUI_CharacterBar();
	~cUI_CharacterBar();
	//테스트용
	void init();
	void update();

	//HP만 쓰는용
	void init(float userMaxHP, float userMaxMP);

	//HP, MP 같이 쓰는용
	void update(float userCurrentHP,float userCurrentMP);

	void uiRender();

};

