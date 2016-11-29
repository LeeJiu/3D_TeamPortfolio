#include "stdafx.h"
#include "cUI_CharacterBar.h"


cUI_CharacterBar::cUI_CharacterBar()
{
}


cUI_CharacterBar::~cUI_CharacterBar()
{
}

void cUI_CharacterBar::init()
{
	m_UICharacterBar.x = WINSIZE_X / 10;
	m_UICharacterBar.y = WINSIZE_Y - 128;
	m_UICharacterBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_CharacterBar.tga");
	m_UICharacterBar.rc = RectMake(0, 0, 1024, 128);

	m_UICharacterBarBack.x = WINSIZE_X / 10;
	m_UICharacterBarBack.y = WINSIZE_Y - 128;
	m_UICharacterBarBack.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_CharacterBarBack.tga");
	m_UICharacterBarBack.rc = RectMake(0, 0, 1024, 128);

	//================== 케릭터 ===============
	playerMaxHP = 1000;
	playerCurHP = 1000;

	playerMaxMP = 1000;
	playerCurMP = 1000;


	rcMaxHP = RCMAX;
	rcCurHP = playerCurHP / playerMaxHP * rcMaxHP;
	
	rcMaxMP = RCMAX;   // 그러줄 RC최대 값.
	rcCurMP = playerCurMP / playerMaxMP * rcMaxMP;



	damage = 100;
	m_UIHPBar.x = WINSIZE_X / 2 + 57;
	m_UIHPBar.y = WINSIZE_Y - 18;
	m_UIHPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_HPBar.tga");
	m_UIHPBar.rc = RectMake(0, 0, rcCurHP, 16);


	m_UIMPBar.x = WINSIZE_X / 2 - 55;
	m_UIMPBar.y = WINSIZE_Y - 18;
	m_UIMPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_MPBar.tga");
	m_UIMPBar.rc = RectMake(-rcCurMP, 0, -rcCurMP, 16);

}
void cUI_CharacterBar::init(float userMaxHP, float userMaxMP)
{
	m_UICharacterBar.x = WINSIZE_X / 10;
	m_UICharacterBar.y = WINSIZE_Y - 128;
	m_UICharacterBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_CharacterBar.tga");
	m_UICharacterBar.rc = RectMake(0, 0, 1024, 128);

	m_UICharacterBarBack.x = WINSIZE_X / 10;
	m_UICharacterBarBack.y = WINSIZE_Y - 128;
	m_UICharacterBarBack.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_CharacterBarBack.tga");
	m_UICharacterBarBack.rc = RectMake(0, 0, 1024, 128);

	//================== 케릭터 ===============
	playerMaxHP = userMaxHP;
	playerCurHP = userMaxHP;

	playerMaxMP = userMaxMP;
	playerCurMP = userMaxMP;

	//============= rc 그려주는 위치 계산 하는 공식
	rcMaxHP = RCMAX;
	rcCurHP = playerCurHP / playerMaxHP * rcMaxHP;

	rcMaxMP = RCMAX;   // 그러줄 RC최대 값.
	rcCurMP = playerCurMP / playerMaxMP * rcMaxMP;

	m_UIHPBar.x = WINSIZE_X / 2 + 57;
	m_UIHPBar.y = WINSIZE_Y - 18;
	m_UIHPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_HPBar.tga");
	m_UIHPBar.rc = RectMake(0, 0, rcCurHP, 16);


	m_UIMPBar.x = WINSIZE_X / 2 - 55;
	m_UIMPBar.y = WINSIZE_Y - 18;
	m_UIMPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_MPBar.tga");
	m_UIMPBar.rc = RectMake(-rcCurMP, 0, -rcCurMP, 16);

}

void cUI_CharacterBar::update()
{

	m_UIHPBar.rc = RectMake(0, 0, rcCurHP, 16);
	m_UIMPBar.rc = RectMake(-rcCurMP, 0, -rcCurMP, 16);

	rcCurHP = playerCurHP / playerMaxHP * rcMaxHP;
	rcCurMP = playerCurMP / playerMaxMP * rcMaxMP;
	
	if (rcCurHP < 0)
	{
		rcCurHP = 0;
	}

	if (rcCurMP < 0)
	{
		rcCurMP = 0;
	}

	if (rcCurHP > rcMaxHP)
	{
		rcCurHP = rcMaxHP;

	}

	if (rcCurMP > rcMaxMP)
	{
		rcCurMP = rcMaxMP;
	}

}

void cUI_CharacterBar::update(float userCurrentHP, float userCurrentMP)
{
	//============= rc 그려주는 위치 계산 하는 공식

	rcCurHP = userCurrentHP / playerMaxHP * rcMaxHP;
	rcCurMP = userCurrentMP / playerMaxMP * rcMaxMP;
	// ㅇㅖ외 처리
	if (rcCurHP < 0)
	{
		rcCurHP = 0;
	}

	if (rcCurMP < 0)
	{
		rcCurMP = 0;
	}

	if (rcCurHP > rcMaxHP)
	{
		rcCurHP = rcMaxHP;

	}

	if (rcCurMP > rcMaxMP)
	{
		rcCurMP = rcMaxMP;
	}

	m_UIHPBar.rc = RectMake(0, 0, rcCurHP, 16);
	m_UIMPBar.rc = RectMake(-rcCurMP, 0, -rcCurMP, 16);
}

void cUI_CharacterBar::uiRender()
{
	SPRITE_MGR->DrawTexture(
		m_UICharacterBarBack.img,
		&m_UICharacterBarBack.rc,
		m_UICharacterBarBack.x, m_UICharacterBarBack.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_UIHPBar.img,
		&m_UIHPBar.rc,
		m_UIHPBar.x, m_UIHPBar.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_UIMPBar.img,
		&m_UIMPBar.rc,
		m_UIMPBar.x, m_UIMPBar.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_UICharacterBar.img,
		&m_UICharacterBar.rc,
		m_UICharacterBar.x, m_UICharacterBar.y,
		0xffffffff,
		NULL);



}