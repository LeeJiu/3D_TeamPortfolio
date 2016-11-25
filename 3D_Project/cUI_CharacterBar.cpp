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


	maxHP = 256;
	currecntHP = 256;
	damage = 10;
	m_UIHPBar.x = WINSIZE_X / 2 + 57;
	m_UIHPBar.y = WINSIZE_Y - 18;
	m_UIHPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_HPBar.tga");
	m_UIHPBar.rc = RectMake(0, 0, currecntHP, 16);

	maxMP = 256;
	currecntMP = 256;
	usedMP = 10;
	m_UIMPBar.x = WINSIZE_X / 2 - 55;
	m_UIMPBar.y = WINSIZE_Y - 18;
	m_UIMPBar.img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_MPBar.tga");
	m_UIMPBar.rc = RectMake(-currecntMP, 0, -currecntMP, 16);

}


void cUI_CharacterBar::update()
{

	m_UIHPBar.rc = RectMake(0, 0, currecntHP, 16);
	m_UIMPBar.rc = RectMake(-currecntMP, 0, -currecntMP, 16);

	if (currecntHP < 0)
	{
		currecntHP = 0;
	}

	if (currecntMP < 0)
	{
		currecntMP = 0;
	}

	if (currecntHP > maxHP)
	{
		currecntHP = maxHP;
	}

	if (currecntMP > maxMP)
	{
		currecntMP = maxMP;
	}


	if (KEY_MGR->IsOnceDown('K'))
	{
		currecntHP -= damage;
	}

	if (KEY_MGR->IsOnceDown('L'))
	{
		currecntHP += damage;
	}

	if (KEY_MGR->IsOnceDown('O'))
	{
		currecntMP -= usedMP;
	}

	if (KEY_MGR->IsOnceDown('P'))
	{
		currecntMP += usedMP;
	}

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